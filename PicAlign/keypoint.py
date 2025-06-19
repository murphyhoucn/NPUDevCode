import os
import json
import cv2
import numpy as np
from glob import glob
from pathlib import Path

# ---------- 配置 ----------
BASE_JSON = 'base.json'  # 基准图像的 LabelMe 标注文件
IMG_DIR = 'NPU-Everyday_all'       # 所有待处理图像
OUT_ALIGN = 'NPU-Everyday_all_keypoints/aligned'
OUT_JSON = 'NPU-Everyday_all_keypoints/keypoints_json'
LABEL_NAME = 'Library'   # 标注名（与你的 base.json 保持一致）
MAX_POLY_POINTS = 8      # 采样点数量（与基准图相同）

# ---------- 初始化输出文件夹 ----------
os.makedirs(OUT_ALIGN, exist_ok=True)
os.makedirs(OUT_JSON, exist_ok=True)

# ---------- 工具函数 ----------

def load_polygon_from_labelme(json_path):
    with open(json_path, 'r') as f:
        data = json.load(f)
    for shape in data['shapes']:
        if shape['label'] == LABEL_NAME:
            return np.array(shape['points'], dtype=np.float32)
    raise ValueError(f"No shape with label '{LABEL_NAME}' found in {json_path}")

def detect_building_polygon(img, max_points=8):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (7, 7), 0)
    edges = cv2.Canny(blur, 30, 100)
    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if not contours:
        raise ValueError("No contours found")

    largest = max(contours, key=cv2.contourArea)
    epsilon = 0.01 * cv2.arcLength(largest, True)
    approx = cv2.approxPolyDP(largest, epsilon, True).reshape(-1, 2)

    if len(approx) < max_points:
        raise ValueError("Detected polygon has fewer points than expected.")

    # 均匀采样出 max_points 个点
    indices = np.linspace(0, len(approx) - 1, max_points).astype(int)
    return approx[indices].astype(np.float32)

def save_labelme_json(img_path, points, out_path):
    data = {
        "version": "5.8.1",
        "flags": {},
        "shapes": [{
            "label": LABEL_NAME,
            "points": points.tolist(),
            "group_id": None,
            "shape_type": "polygon",
            "flags": {}
        }],
        "imagePath": os.path.basename(img_path),
        "imageData": None
    }
    with open(out_path, 'w') as f:
        json.dump(data, f, indent=2)

# ---------- 主处理流程 ----------

# 1. 加载基准图的 polygon（8点）
ref_pts = load_polygon_from_labelme(BASE_JSON)

# 2. 遍历待处理图像
for img_path in glob(f"{IMG_DIR}/*.jpg") + glob(f"{IMG_DIR}/*.png"):
    fname = Path(img_path).name
    print(f"🌀 Processing: {fname}")
    try:
        img = cv2.imread(img_path)
        cur_pts = detect_building_polygon(img)

        # 对齐：H矩阵
        H, _ = cv2.findHomography(cur_pts, ref_pts, cv2.RANSAC)
        aligned = cv2.warpPerspective(img, H, (img.shape[1], img.shape[0]))

        # 保存图像
        out_img = os.path.join(OUT_ALIGN, fname)
        cv2.imwrite(out_img, aligned)

        # 保存关键点 JSON
        out_json = os.path.join(OUT_JSON, fname.replace('.jpg', '.json').replace('.png', '.json'))
        save_labelme_json(fname, cur_pts, out_json)

        print(f"✅ Done: {fname}")
    except Exception as e:
        print(f"❌ Failed: {fname} | Error: {e}")

print("✅ 所有图像处理完毕。")

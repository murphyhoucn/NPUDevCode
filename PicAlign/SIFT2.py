import cv2
import numpy as np
import os
from glob import glob
from skimage.exposure import match_histograms
import time

# ---------- 参数配置 ----------

IMG_DIR = '/mnt/houjinliang/MyDevProject/NPUDevCode/PicAlign/data/NPU-Everyday_all'               # 图像文件夹路径（请将原始RGB图像放在此处）
OUT_DIR = '/mnt/houjinliang/MyDevProject/NPUDevCode/PicAlign/data/NPU-Everyday_all_sift2'       # 输出文件夹路径
RATIO_TEST = 0.75                # Lowe's ratio 测试阈值
MIN_MATCH_COUNT = 10             # 最小有效匹配数量

os.makedirs(OUT_DIR, exist_ok=True)

# ---------- 功能函数 ----------
def get_current_time():
    current_time = time.strftime("%Y_%m_%d_%H_%M_%S", time.localtime())
    return current_time

def enhance_image_gray(img_gray):
    """增强灰度图像对比度（适用于夜景）"""
    clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
    return clahe.apply(img_gray)

def histogram_match(img_gray, ref_gray):
    """将图像的直方图匹配到参考图"""
    matched = match_histograms(img_gray, ref_gray, channel_axis=None)
    return matched.astype('uint8')

# ---------- 加载图像路径 ----------
image_paths = sorted(glob(os.path.join(IMG_DIR, '*.jpg')) + glob(os.path.join(IMG_DIR, '*.png')))

# ---------- 初始化 SIFT ----------
sift = cv2.SIFT_create()
bf = cv2.BFMatcher()

# ---------- 读取基准图像 ----------
ref_gray = cv2.imread(image_paths[0], cv2.IMREAD_GRAYSCALE)
ref_rgb = cv2.imread(image_paths[0], cv2.IMREAD_COLOR)
kp_ref, des_ref = sift.detectAndCompute(ref_gray, None)

# 保存基准图像
cv2.imwrite(os.path.join(OUT_DIR, f"sift2_{os.path.basename(image_paths[0])}"), ref_rgb)

# ---------- 批量处理 ----------
for path in image_paths[1:]:
    fname = os.path.basename(path)
    print(f"🔄 Processing: {fname} at {get_current_time()}")
    
    img_gray = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    img_rgb = cv2.imread(path, cv2.IMREAD_COLOR)

    # 灰度增强（夜景场景提高对比度）
    img_gray = enhance_image_gray(img_gray)
    # 可选：开启直方图匹配增强（需安装 skimage）
    img_gray = histogram_match(img_gray, ref_gray)

    kp, des = sift.detectAndCompute(img_gray, None)
    if des is None or len(kp) < 10:
        print(f"⚠️ 跳过 {fname}：关键点不足")
        continue

    matches = bf.knnMatch(des_ref, des, k=2)

    # Lowe's ratio test
    good_matches = [m for m, n in matches if m.distance < RATIO_TEST * n.distance]

    if len(good_matches) < MIN_MATCH_COUNT:
        print(f"❌ 匹配失败（仅匹配到 {len(good_matches)} 个点）: {fname}")
        continue

    pts_ref = np.float32([kp_ref[m.queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
    pts_cur = np.float32([kp[m.trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)

    # 单应性估计
    H, mask = cv2.findHomography(pts_cur, pts_ref, cv2.RANSAC)
    aligned_rgb = cv2.warpPerspective(img_rgb, H, (ref_rgb.shape[1], ref_rgb.shape[0]))

    # 保存对齐图像
    out_path = os.path.join(OUT_DIR, f"sift2_{fname}")
    cv2.imwrite(out_path, aligned_rgb)
    print(f"✅ 对齐完成: {fname}")

print("✅ 所有图像已处理完毕。")

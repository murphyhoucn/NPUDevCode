import cv2
import numpy as np
import os
from glob import glob
import time

def get_current_time():
    current_time = time.strftime("%Y_%m_%d_%H_%M_%S", time.localtime())
    return current_time

# ---------- 参数配置 ----------
IMG_DIR = '/mnt/houjinliang/MyDevProject/NPUDevCode/NPU-Everyday_all'               # 图像文件夹路径（请将原始RGB图像放在此处）
OUT_DIR = '/mnt/houjinliang/MyDevProject/NPUDevCode/NPU-Everyday_all_align'       # 输出文件夹路径
RATIO_TEST = 0.75                # Lowe's ratio 测试阈值
MIN_MATCH_COUNT = 10             # 最小有效匹配数量

# ---------- 准备输出文件夹 ----------
os.makedirs(OUT_DIR, exist_ok=True)

# ---------- 获取图像路径并排序 ----------
image_paths = sorted(glob(os.path.join(IMG_DIR, '*.jpg')))

# ---------- 初始化 SIFT 检测器 ----------
sift = cv2.SIFT_create()
bf = cv2.BFMatcher()

# ---------- 读取基准图像 ----------
ref_gray = cv2.imread(image_paths[0], cv2.IMREAD_GRAYSCALE)
ref_rgb = cv2.imread(image_paths[0], cv2.IMREAD_COLOR)
kp_ref, des_ref = sift.detectAndCompute(ref_gray, None)

# 保存基准 RGB 图像
ref_basename = os.path.basename(image_paths[0])
cv2.imwrite(os.path.join(OUT_DIR, f"ali_{ref_basename}"), ref_rgb)

# ---------- 遍历其余图像并对齐 ----------
for path in image_paths[1:]:

    print(f"{get_current_time()} : {os.path.basename(path)}")

    img_gray = cv2.imread(path, cv2.IMREAD_GRAYSCALE)   # 灰度图用于特征提取
    img_rgb = cv2.imread(path, cv2.IMREAD_COLOR)        # RGB图像用于对齐与保存
    kp, des = sift.detectAndCompute(img_gray, None)

    # 特征匹配
    matches = bf.knnMatch(des_ref, des, k=2)

    # Lowe's ratio test
    good_matches = []
    for m, n in matches:
        if m.distance < RATIO_TEST * n.distance:
            good_matches.append(m)

    if len(good_matches) >= MIN_MATCH_COUNT:
        # 获取匹配点坐标
        pts_ref = np.float32([kp_ref[m.queryIdx].pt for m in good_matches]).reshape(-1, 1, 2)
        pts_cur = np.float32([kp[m.trainIdx].pt for m in good_matches]).reshape(-1, 1, 2)

        # 估计单应性矩阵
        H, mask = cv2.findHomography(pts_cur, pts_ref, cv2.RANSAC)

        # 使用 H 对 RGB 图像进行变换
        aligned_rgb = cv2.warpPerspective(img_rgb, H, (ref_gray.shape[1], ref_gray.shape[0]))

        # 保存结果
        filename = os.path.basename(path)
        out_path = os.path.join(OUT_DIR, f"ali_{filename}")
        cv2.imwrite(out_path, aligned_rgb)
    else:
        print(f"⚠️ Not enough matches for {path} ({len(good_matches)} found)")

print("✅ 所有图像已成功对齐并保存到", OUT_DIR)


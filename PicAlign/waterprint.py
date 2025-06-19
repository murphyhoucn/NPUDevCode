import cv2
import os
from glob import glob
from datetime import datetime

# ---------- 配置 ----------
INPUT_DIR = '/mnt/houjinliang/MyDevProject/NPUDevCode/PicAlign/data/NPU-Everyday_all'
OUTPUT_DIR = '/mnt/houjinliang/MyDevProject/NPUDevCode/PicAlign/data/NPU-Everyday_all_watermark2'

os.makedirs(OUTPUT_DIR, exist_ok=True)

# ---------- 可配置参数 ----------
FONT_PATH = cv2.FONT_HERSHEY_SIMPLEX  # 也可换成 cv2.FONT_HERSHEY_COMPLEX 等
FONT_SCALE = 1.5
FONT_COLOR = (255, 255, 255)
THICKNESS = 2
ALPHA = 0.8  # 透明度，0=完全透明，1=不透明

# 水印位置选项：'top-left', 'top-right', 'bottom-left', 'bottom-right'
POSITION = 'bottom-right'

# ---------- 核心函数 ----------
def get_datetime_from_filename(filename):
    """提取时间戳，返回格式化字符串"""
    try:
        base = os.path.basename(filename)
        name, _ = os.path.splitext(base)
        # 提取时间：IMG_YYYYMMDD_HHMMSS
        parts = name.split('_')
        dt = datetime.strptime(parts[1] + parts[2], "%Y%m%d%H%M%S")
        return dt.strftime("%Y.%m.%d %H:%M:%S")
    except Exception as e:
        print(f"⚠️ 无法解析时间戳: {filename}")
        return None

def get_position_coords(text_size, img_shape, position, margin=20):
    h, w = img_shape[:2]
    tw, th = text_size

    if position == 'top-left':
        return (margin, margin + th)
    elif position == 'top-right':
        return (w - tw - margin, margin + th)
    elif position == 'bottom-left':
        return (margin, h - margin)
    elif position == 'bottom-right':
        return (w - tw - margin, h - margin)
    else:
        return (margin, h - margin)

def add_watermark(img, text, position='bottom-right'):
    overlay = img.copy()
    text_size, _ = cv2.getTextSize(text, FONT_PATH, FONT_SCALE, THICKNESS)
    pos = get_position_coords(text_size, img.shape, position)
    
    cv2.putText(overlay, text, pos, FONT_PATH, FONT_SCALE, FONT_COLOR, THICKNESS, cv2.LINE_AA)
    return cv2.addWeighted(overlay, ALPHA, img, 1 - ALPHA, 0)

# ---------- 批量处理 ----------
for path in sorted(glob(os.path.join(INPUT_DIR, '*.jpg'))):
    timestamp = get_datetime_from_filename(path)
    if not timestamp:
        continue

    watermark_text = f"Murphy | Shaanxi Xi'an | {timestamp}"
    img = cv2.imread(path)
    img_wm = add_watermark(img, watermark_text, POSITION)

    out_path = os.path.join(OUTPUT_DIR, os.path.basename(path))
    cv2.imwrite(out_path, img_wm)
    print(f"✅ 已添加水印: {os.path.basename(path)}")

print("✅ 所有图像已完成水印添加。")

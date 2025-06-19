import cv2
import torch
import numpy as np
from torchvision import transforms
from PIL import Image
import random
from glob import glob

def random_homography(img, perturb=40):
    h, w = img.shape[:2]
    src_pts = np.array([[0,0],[w,0],[w,h],[0,h]], dtype=np.float32)
    dst_pts = src_pts + np.random.uniform(-perturb, perturb, src_pts.shape).astype(np.float32)
    H = cv2.getPerspectiveTransform(src_pts, dst_pts)
    warped = cv2.warpPerspective(img, H, (w, h))
    return warped, H

def get_train_pairs(image_dir, size=(256, 256)):
    paths = glob(f"{image_dir}/*.jpg")
    transform = transforms.Compose([
        transforms.Resize(size),
        transforms.ToTensor()
    ])
    for path in paths:
        img = Image.open(path).convert('RGB')
        img_np = np.array(img)
        warped_np, H = random_homography(img_np)
        yield transform(Image.fromarray(warped_np)), transform(img), torch.tensor(H, dtype=torch.float32)

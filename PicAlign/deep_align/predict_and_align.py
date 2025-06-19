import torch
import cv2
import numpy as np
from model import AlignmentNet
from torchvision import transforms
from PIL import Image

device = 'cuda' if torch.cuda.is_available() else 'cpu'
net = AlignmentNet().to(device)
net.load_state_dict(torch.load('model.pth'))
net.eval()

transform = transforms.Compose([
    transforms.Resize((256, 256)),
    transforms.ToTensor()
])

def predict_H(img1_path, img2_path):
    img1 = Image.open(img1_path).convert('RGB')
    img2 = Image.open(img2_path).convert('RGB')
    t1 = transform(img1).unsqueeze(0).to(device)
    t2 = transform(img2).unsqueeze(0).to(device)
    with torch.no_grad():
        H_pred = net(t1, t2).cpu().squeeze().numpy()
    return H_pred

def warp_image(img_path, H):
    img = cv2.imread(img_path)
    warped = cv2.warpPerspective(img, H, (img.shape[1], img.shape[0]))
    return warped

H = predict_H("images/img_day.jpg", "images/img_base.jpg")
aligned = warp_image("images/img_day.jpg", H)
cv2.imwrite("aligned_result.jpg", aligned)

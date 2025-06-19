import torch
from torch import nn, optim
from model import AlignmentNet
from data_utils import get_train_pairs
from tqdm import tqdm

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
net = AlignmentNet().to(device)
optimizer = optim.Adam(net.parameters(), lr=1e-4)
criterion = nn.MSELoss()

EPOCHS = 10
for epoch in range(EPOCHS):
    total_loss = 0
    for img1, img2, H_gt in tqdm(get_train_pairs('NPU-Everyday_all')):
        img1, img2, H_gt = img1.to(device).unsqueeze(0), img2.to(device).unsqueeze(0), H_gt.to(device).unsqueeze(0)
        H_pred = net(img1, img2)
        loss = criterion(H_pred, H_gt)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        total_loss += loss.item()
    print(f"Epoch {epoch+1}: Loss = {total_loss:.4f}")

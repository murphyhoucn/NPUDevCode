import torch
import torch.nn as nn
import torchvision.models as models

class AlignmentNet(nn.Module):
    def __init__(self):
        super().__init__()
        resnet = models.resnet18(pretrained=True)
        self.encoder = nn.Sequential(*list(resnet.children())[:-1])  # Remove FC
        self.fc = nn.Sequential(
            nn.Linear(512 * 2, 256),
            nn.ReLU(),
            nn.Linear(256, 9)  # 输出 H 的 3x3 参数
        )

    def forward(self, img1, img2):
        f1 = self.encoder(img1).flatten(1)
        f2 = self.encoder(img2).flatten(1)
        feat = torch.cat([f1, f2], dim=1)
        H_flat = self.fc(feat)
        H = H_flat.view(-1, 3, 3)
        return H

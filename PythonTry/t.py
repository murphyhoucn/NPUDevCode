import torch
timesteps = 500
batch_size = 64

t = torch.randint(0, timesteps, (batch_size,), device="cpu").long()
print(t.shape)
print(t)

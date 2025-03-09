import numpy as np

# 假设 betas 是一个长度为 1000 的 float32 类型的 NumPy 数组
betas = np.linspace(0.0001, 0.02, 1000, dtype=np.float32)

# 计算 alphas
alphas = 1.0 - betas

# 计算 alphas 的累积乘积
alphascumprod = np.cumprod(alphas)

# 检查类型和尺寸
output = {
    "alphas 类型": alphas.dtype,
    "alphas 尺寸": alphas.shape,
    "alphascumprod 类型": alphascumprod.dtype,
    "alphascumprod 尺寸": alphascumprod.shape,
    "alphas 部分数值": alphas[:5],  # 显示前5个数值
    "alphascumprod 部分数值": alphascumprod[:5]  # 显示前5个累积乘积数值
}

print(output)

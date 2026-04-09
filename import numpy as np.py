import numpy as np

# ---------------------- 1. 基本参数定义 ----------------------
k1 = 200  # N/m
k2 = 300  # N/m
k3 = 200  # N/m
F = np.array([50, 30, 20])  # 外力向量 N

# 构建系数矩阵A
A = np.array([
    [k1 + k2, -k2, 0],
    [-k2, k2 + k3, -k3],
    [0, -k3, k3]
])

print("="*50)
print("线性方程组求解结果（LU分解法）")
print("="*50)
print(f"系数矩阵A：\n{A}")
print(f"外力向量F：{F}")

# ---------------------- 2. LU分解实现 ----------------------
def lu_decomposition(A):
    """LU分解：A = L @ U，L为单位下三角矩阵，U为上三角矩阵"""
    n = A.shape[0]
    L = np.eye(n)  # 单位下三角矩阵
    U = np.zeros_like(A)
    
    for i in range(n):
        # 计算U的第i行
        for j in range(i, n):
            U[i, j] = A[i, j] - np.dot(L[i, :i], U[:i, j])
        
        # 计算L的第i列（i>0）
        for j in range(i+1, n):
            L[j, i] = (A[j, i] - np.dot(L[j, :i], U[:i, i])) / U[i, i]
    
    return L, U

# 执行LU分解
L, U = lu_decomposition(A)
print(f"\nLU分解结果：")
print(f"下三角矩阵L：\n{L}")
print(f"上三角矩阵U：\n{U}")

# 验证分解正确性
A_recon = L @ U
print(f"\n分解验证：L@U与A的误差：{np.linalg.norm(A - A_recon):.10e}")

# ---------------------- 3. 求解线性方程组 ----------------------
def forward_substitution(L, b):
    """前向替换求解L@y = b"""
    n = L.shape[0]
    y = np.zeros_like(b)
    for i in range(n):
        y[i] = b[i] - np.dot(L[i, :i], y[:i])
    return y

def backward_substitution(U, y):
    """后向替换求解U@u = y"""
    n = U.shape[0]
    u = np.zeros_like(y)
    for i in range(n-1, -1, -1):
        u[i] = (y[i] - np.dot(U[i, i+1:], u[i+1:])) / U[i, i]
    return u

# 求解过程
y = forward_substitution(L, F)
u = backward_substitution(U, y)

print(f"\n求解结果：")
print(f"中间向量y：{y}")
print(f"位移u1 = {u[0]:.6f} m")
print(f"位移u2 = {u[1]:.6f} m")
print(f"位移u3 = {u[2]:.6f} m")

# 验证解的正确性
residual = np.linalg.norm(A @ u - F)
print(f"\n解的验证：A@u - F的范数 = {residual:.10e}（接近0表示正确）")
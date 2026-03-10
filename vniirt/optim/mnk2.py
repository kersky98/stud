import numpy as np
import matplotlib.pyplot as plt

# Пример данных
x = np.array([
    -2, -1, 0, 1, 2, 
    -2, -1, 0, 1, 2, 
    -2, -1, 0, 1, 2, 
    -2, -1, 0, 1, 2, 
    -2, -1, 0, 1, 2])
y = np.array([
    -2, -2, -2, -2, -2, 
    -1, -1, -1, -1, -1, 
     0, 0, 0, 0, 0, 
     1, 1, 1, 1, 1, 
     2, 2, 2, 2, 2])
z = np.array([
    0, 3, 2, 1, 2, 
    1, 4, 3, 1, 2,
    2, 6, 4, 3, 4,
    1, 4, 3, 1, 2,
    0, 3, 2, 1, 2])

# Построение матрицы A
A = np.column_stack([
    x**2,      # a * x^2
    y**2,      # b * y^2
    x * y,     # c * x*y
    x,         # d * x
    y,         # e * y
    np.ones_like(x)  # f
])

# Решение МНК
w, residuals, rank, s = np.linalg.lstsq(A, z, rcond=None)
a, b, c, d, e, f = w
print(f"Аппроксимация: z = {a:.3f}*x² + {b:.3f}*y² + {c:.3f}*x*y + {d:.3f}*x + {e:.3f}*y + {f:.3f}")


fig = plt.figure(figsize=(20, 10))
ax1 = fig.add_subplot(121, projection='3d')

# Исходные точки
ax1.scatter(x, y, z, color='red', label='Данные', s=50)

# 🔽 Добавляем проекции на плоскость XY (z = min(z) или z = const)
z_floor = 0  # можно использовать z=0, или чуть ниже min(z)

# Вариант 1: Просто точки-проекции
ax1.scatter(x, y, z_floor, color='red', s=30, alpha=0.5, marker='o')

# Вариант 2: Вертикальные линии от точки до пола (как "ножки")
for i in range(len(x)):
    ax1.plot([x[i], x[i]], [y[i], y[i]], [z[i], z_floor], 
             color='gray', linestyle='--', linewidth=1, alpha=0.7)

# Аппроксимирующая поверхность (параболоид)
X, Y = np.meshgrid(
    np.linspace(x.min(), x.max(), 50),
    np.linspace(y.min(), y.max(), 50)
)
Z = a*X**2 + b*Y**2 + c*X*Y + d*X + e*Y + f

ax1.plot_surface(X, Y, Z, alpha=0.5, cmap='jet', edgecolor='none')

ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_zlabel('Z')
ax1.set_title('Квадратичная аппроксимация (параболоид)')
ax1.legend()

# --- Контурный график ---
ax2 = fig.add_subplot(122)
contour = ax2.contour(X, Y, Z, levels=20, cmap='jet')
contourf = ax2.contourf(X, Y, Z, levels=20, cmap='jet', alpha=0.6)
ax2.scatter(x, y, color='red', s=30, label='Точки данных')
fig.colorbar(contourf, ax=ax2, label='Z')

ax2.set_xlabel('X')
ax2.set_ylabel('Y')
ax2.set_title('Контурная карта аппроксимации')
ax2.grid(True, alpha=0.3)
ax2.axis('equal')  # одинаковый масштаб осей
ax2.legend()

plt.tight_layout()
plt.show()
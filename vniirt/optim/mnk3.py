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


# Создадим данные с явной кубической зависимостью
# x_fine = np.linspace(-2, 2, 10)
# y_fine = np.linspace(-2, 2, 10)
# X_true, Y_true = np.meshgrid(x_fine, y_fine)
# Z_true = X_true**3 - 3*X_true*Y_true**2  # классический "седловой" кубический многочлен (форма "седла Монге")

# # Теперь превратим в векторы
# x = X_true.ravel()
# y = Y_true.ravel()
# z = Z_true.ravel()

# Построение матрицы A для полинома 3-го порядка
A = np.column_stack([
    x**3,           # a * x^3
    y**3,           # b * y^3
    x**2 * y,       # c * x²y
    x * y**2,       # d * xy²
    x**2,           # e * x²
    y**2,           # f * y²
    x * y,          # g * xy
    x,              # h * x
    y,              # i * y
    np.ones_like(x) # j
])

# Решение МНК
w, residuals, rank, s = np.linalg.lstsq(A, z, rcond=None)
a, b, c, d, e, f, g, h, i, j = w

print(f"Аппроксимация 3-го порядка:")
print(f"z = {a:.3f}*x³ + {b:.3f}*y³ + {c:.3f}*x²y + {d:.3f}*xy² + "
      f"{e:.3f}*x² + {f:.3f}*y² + {g:.3f}*xy + {h:.3f}*x + {i:.3f}*y + {j:.3f}")


fig = plt.figure(figsize=(20, 10))
ax1 = fig.add_subplot(121, projection='3d')

# Исходные точки
ax1.scatter(x, y, z, color='red', label='Данные', s=50)

# 🔽 Добавляем проекции на плоскость XY (z = min(z) или z = const)
z_floor = 0  # можно использовать z=0, или чуть ниже min(z)

# Вариант 1: Просто точки-проекции
ax1.scatter(x, y, z_floor, color='red', s=30, alpha=0.5, marker='o')

# Вариант 2: Вертикальные линии от точки до пола (как "ножки")
# for i in range(len(x)):
#     ax1.plot([x[i], x[i]], [y[i], y[i]], [z[i], z_floor], 
#              color='gray', linestyle='--', linewidth=1, alpha=0.7)

# Аппроксимирующая поверхность 3-го порядка
X, Y = np.meshgrid(
    np.linspace(x.min(), x.max(), 50),
    np.linspace(y.min(), y.max(), 50)
)

Z = (
    a*X**3 + b*Y**3 + c*X**2*Y + d*X*Y**2 +
    e*X**2 + f*Y**2 + g*X*Y + h*X + i*Y + j
)

ax1.plot_surface(X, Y, Z, alpha=0.6, cmap='jet', edgecolor='none')

# Оформление
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_zlabel('Z')
ax1.set_title('Аппроксимация поверхностью 3-го порядка')
ax1.legend(['Данные', 'Проекция', 'Поверхность 3-го порядка'])

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
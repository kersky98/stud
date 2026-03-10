import numpy as np
import matplotlib.pyplot as plt

# Пример данных
# x = np.array([
#     -3, -2, -1, 0, 1, 2, 3,
#     -3, -2, -1, 0, 1, 2, 3,
#     -3, -2, -1, 0, 1, 2, 3,
#     -3, -2, -1, 0, 1, 2, 3,
#     -3, -2, -1, 0, 1, 2, 3,
#     -3, -2, -1, 0, 1, 2, 3,
#     -3, -2, -1, 0, 1, 2, 3])
# y = np.array([
#     -3, -3, -3, -3, -3, -3, -3,
#     -2, -2, -2, -2, -2, -2, -2, 
#     -1, -1, -1, -1, -1, -1, -1,
#      0, 0, 0, 0, 0, 0, 0,
#      1, 1, 1, 1, 1, 1, 1, 
#      2, 2, 2, 2, 2, 2, 2,
#      3, 3, 3, 3, 3, 3, 3])
# z = np.array([
#     1, 2, 1, 1, 1, 2, 1,
#     1, 3, 1, 1, 1, 3, 1, 
#     2, 4, 2, 1, 2, 4, 2,
#     4, 6, 4, 3, 4, 6, 4, # max
#     2, 4, 2, 1, 2, 4, 2,
#     1, 3, 1, 1, 1, 3, 1,
#     1, 2, 1, 1, 1, 2, 1])

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

# Построение матрицы A для полинома 4-го порядка
A = np.column_stack([
    x**4,           # a0 * x^4
    y**4,           # a1 * y^4
    x**3 * y,       # a2 * x³y
    x * y**3,       # a3 * xy³
    x**2 * y**2,    # a4 * x²y²
    
    x**3,           # a5 * x³
    x**2 * y,       # a6 * x²y
    x * y**2,       # a7 * xy²
    y**3,           # a8 * y³
    
    x**2,           # a9 * x²
    x * y,          # a10 * xy
    y**2,           # a11 * y²
    
    x,              # a12 * x
    y,              # a13 * y
    np.ones_like(x) # a14 * const
])

# Решение МНК
w, residuals, rank, s = np.linalg.lstsq(A, z, rcond=None)
(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) = w

print("Аппроксимация полиномом 4-го порядка:")
print(f"z = {a0:.3f}*x⁴ + {a1:.3f}*y⁴ + {a2:.3f}*x³y + {a3:.3f}*xy³ + {a4:.3f}*x²y² +")
print(f"    {a5:.3f}*x³ + {a6:.3f}*x²y + {a7:.3f}*xy² + {a8:.3f}*y³ +")
print(f"    {a9:.3f}*x² + {a10:.3f}*xy + {a11:.3f}*y² +")
print(f"    {a12:.3f}*x + {a13:.3f}*y + {a14:.3f}")


# Создаём фигуру с двумя подграфиками
fig = plt.figure(figsize=(20, 10))
ax1 = fig.add_subplot(121, projection='3d')

# Исходные точки
ax1.scatter(x, y, z, color='red', label='Данные', s=50)

# Проекции на плоскость XY
z_floor = min(z) - 1
ax1.scatter(x, y, z_floor, color='red', s=30, alpha=0.5, marker='o')
for i in range(len(x)):
    ax1.plot([x[i], x[i]], [y[i], y[i]], [z[i], z_floor], 
             color='gray', linestyle='--', linewidth=1, alpha=0.7)

# Аппроксимирующая поверхность 3-го порядка
X, Y = np.meshgrid(
    np.linspace(x.min(), x.max(), 50),
    np.linspace(y.min(), y.max(), 50)
)

Z = (
    a0*X**4 + a1*Y**4 + a2*X**3*Y + a3*X*Y**3 + a4*X**2*Y**2 +
    a5*X**3 + a6*X**2*Y + a7*X*Y**2 + a8*Y**3 +
    a9*X**2 + a10*X*Y + a11*Y**2 +
    a12*X + a13*Y + a14
)
# cmap='plasma'
ax1.plot_surface(X, Y, Z, alpha=0.8, cmap='jet', edgecolor='none')

# Оформление
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_zlabel('Z')
ax1.set_title('Аппроксимация поверхностью 4-го порядка')
ax1.legend(['Данные', 'Проекция', 'Поверхность 4-го порядка'])

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
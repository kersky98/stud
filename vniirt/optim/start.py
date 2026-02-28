"""
Построение 3D-графика функции с двумя локальными минимумами
и поиск минимумов методом покоординатного спуска.
Вывод количества итераций в консоль и на график.
"""

import numpy as np
import matplotlib.pyplot as plt


def f1(x, y):
    """
    Целевая функция с двумя локальными минимумами около (±1.5, 0).
    """
    return -np.exp(-((x - 1.5)**2 + y**2)) - np.exp(-((x + 1.5)**2 + y**2))

def f(x0, x1):
    """
    Целевая функция с двумя локальными минимумами около (-4.777, -3.935) и (4.777, 3.935).
    """
    return -1*np.sinc( np.pi/18 * np.sqrt((5*x0-x1+20)**2 + (x0-5*x1-15)**2) )-\
      0.5*np.sinc( np.pi/18 * np.sqrt((5*x0-x1-20)**2 + (x0-5*x1+15)**2) )

def f2(x0, x1):
    """
    Целевая функция с одним локальным минимумом около (0, 0).
    """
    return -np.sinc(np.pi/60 * np.sqrt((5*x0-x1)**2 + (x0-5*x1)**2)) /\
           np.sinc(np.pi*np.sqrt(2))


def coordinate_descent(f, x0, y0, alpha=0.1, max_iter=400, tol=1e-6):
    """
    Метод покоординатного спуска с численным градиентом.

    Возвращает:
    x_history, y_history, z_history, num_iterations
    """
    x, y = x0, y0
    x_history = [x]
    y_history = [y]
    z_history = [f(x, y)]

    num_iterations = 0

    for i in range(max_iter):
        dxy = 1e-8
        # Численный градиент по x
        grad_x = (f(x + dxy, y) - f(x, y)) / dxy
        x_new = x - alpha * grad_x

        # Численный градиент по y (с обновлённым x)
        grad_y = (f(x_new, y + dxy) - f(x_new, y)) / dxy
        y_new = y - alpha * grad_y

        x_history.append(x_new)
        y_history.append(y_new)
        z_history.append(f(x_new, y_new))

        # Проверка сходимости
        if abs(grad_x) < tol and abs(grad_y) < tol:
            num_iterations = i + 1
            break
        if abs(x_new - x) < tol and abs(y_new - y) < tol:
            num_iterations = i + 1
            break

        x, y = x_new, y_new
    else:
        num_iterations = max_iter  # достигнут лимит

    return np.array(x_history), np.array(y_history), np.array(z_history), num_iterations


def main():
    # Область построения
    bounds = (-10, 10)
    x = np.linspace(bounds[0], bounds[1], 200)
    y = np.linspace(bounds[0], bounds[1], 200)
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y)

    fig = plt.figure(figsize=(20, 10))

    # 3D график поверхности
    ax1 = fig.add_subplot(121, projection='3d')
    surf = ax1.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8, edgecolor='none', linewidth=0)
    ax1.set_xlabel('X')
    ax1.set_ylabel('Y')
    ax1.set_zlabel('Z')
    ax1.set_title('Функция с N локальными минимумами')
    ax1.view_init(elev=30, azim=45)
    # Цветовая шкала для 3D-графика
    # fig.colorbar(surf, ax=ax1, shrink=0.6, aspect=20, label='Z = f(x, y)')

    # Контурный график
    ax2 = fig.add_subplot(122)
    contour = ax2.contour(X, Y, Z, levels=40, cmap='viridis')
    fig.colorbar(contour, ax=ax2, label='Z = f(x, y)')
    ax2.set_xlabel('X')
    ax2.set_ylabel('Y')
    ax2.set_title('Траектории покоординатного спуска')
    ax2.grid(True, alpha=0.3)

    # Начальные точки
    test_points = [
        (-5.0, -5.0),
        (-5.0, 5.0),
        (5.0, 5.0),
        (5.0, -5.0),
        (-2.0, -2.0),
        (-2.0, 2.0),
        (2.0, 2.0),
        (2.0, -2.0),
    ]

    cmap = plt.cm.hsv
    # colors = ['green', 'red', 'blue', 'lime', 'cyan', 'magenta', 'yellow', 'orange', 'purple', 'pink']

    found_minima = []

    # Запуск оптимизации из разных точек
    for i, (x_init, y_init) in enumerate(test_points):
        x_hist, y_hist, z_hist, iters = coordinate_descent(f, x_init, y_init, alpha=0.1)

        found_minima.append((x_hist[-1], y_hist[-1]))
        color = cmap(i/len(test_points))

        # Отображение траектории
        # label_3d = f'Траектория {i+1} (итер: {iters})'
        label_3d = f'Тр{i+1} → ({x_hist[-1]:.2f}, {y_hist[-1]:.2f}), итер: {iters}'
        ax1.plot(x_hist, y_hist, z_hist, color=color, linewidth=2,
                 marker='o', markersize=3, alpha=0.8, label=label_3d)
        ax1.scatter([x_hist[-1]], [y_hist[-1]], [z_hist[-1]], color=color,
                    s=50, edgecolor='black')

        label_2d = f'Тр{i+1} → ({x_hist[-1]:.2f}, {y_hist[-1]:.2f}), итер: {iters}'
        ax2.plot(x_hist, y_hist, color=color, linewidth=2,
                 marker='o', markersize=3, alpha=0.8, label=label_2d)
        ax2.scatter([x_hist[-1]], [y_hist[-1]], color=color,
                    s=50, edgecolor='black')

        print(f"Точка {i+1}: ({x_init}, {y_init}) → "
              f"минимум ≈ ({x_hist[-1]:.6f}, {y_hist[-1]:.6f}), "
              f"итераций: {iters}")

    # Группировка найденных минимумов
    unique_found = []
    tolerance = 0.2
    for pt in found_minima:
        if not any(np.linalg.norm(np.array(pt) - np.array(u)) < tolerance for u in unique_found):
            unique_found.append(pt)

    # Фактические минимумы
    # actual_minima = [(1.5, 0.0), (-1.5, 0.0)]
    # actual_minima = [(0.0, 0.0)]
    actual_minima = [ (-4.777, -3.947), (4.747, 3.921)]
    actual_x, actual_y = zip(*actual_minima)
    actual_z = [f(x, y) for x, y in actual_minima]
    actual_minima_num = len(actual_minima)

    # Отметка фактических минимумов (зелёные звёзды)
    ax1.scatter(actual_x, actual_y, actual_z, color='green', s=180, marker='*',
                edgecolor='black', linewidth=2, label='Фактический минимум')
    ax2.scatter(actual_x, actual_y, color='green', s=180, marker='*',
                edgecolor='black', linewidth=2, label='Фактический минимум')

    # Отметка найденных минимумов (красные круги)
    for x_min, y_min in unique_found:
        z_min = f(x_min, y_min)
        ax1.scatter([x_min], [y_min], [z_min], color='red', s=150, edgecolor='black',
                    linewidth=2, label='Найденный минимум')
        ax2.scatter([x_min], [y_min], color='red', s=150, edgecolor='black',
                    linewidth=2, label='Найденный минимум')

    # Удаление дубликатов в легенде
    def remove_duplicates(ax):
        handles, labels = ax.get_legend_handles_labels()
        by_label = dict(zip(labels, handles))
        ax.legend(by_label.values(), by_label.keys())

    remove_duplicates(ax1)
    remove_duplicates(ax2)
    
    suptitle_lbl = "Оптимизация: функция с " + str(actual_minima_num) + " локальными минимумами"
    plt.suptitle(suptitle_lbl, fontsize=16)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
"""
Поиск минимумов функции с двумя локальными минимумами
с помощью генетического алгоритма.
Визуализация: траектории в виде линий + координаты в подписи (legend).
"""

import numpy as np
import matplotlib
matplotlib.use('Qt5Agg')  # или 'TkAgg'
import matplotlib.pyplot as plt


def f1(x, y):
    """
    Целевая функция с двумя локальными минимумами около (±1.5, 0).
    """
    return -np.exp(-((x - 1.5)**2 + y**2)) - np.exp(-((x + 1.5)**2 + y**2))

def f(x0, x1):
    """
    Целевая функция с двумя локальными минимумами около (±1.5, 0).
    """
    return -1*np.sinc( np.pi/18 * np.sqrt((5*x0-x1+20)**2 + (x0-5*x1-15)**2) )-\
      0.5*np.sinc( np.pi/18 * np.sqrt((5*x0-x1-20)**2 + (x0-5*x1+15)**2) )


def genetic_algorithm(f, bounds=(-10, 10), n_population=50, n_generations=100,
                      crossover_rate=0.8, mutation_rate=0.1, sigma=0.5,
                      tol=1e-6, patience=10):
    """
    Генетический алгоритм для поиска минимума функции двух переменных.

    Возвращает:
    history (история лучшего решения), best_individual
    """
    # Начальная популяция: (x, y)
    pop = np.random.uniform(bounds[0], bounds[1], (n_population, 2))
    history = []
    best_fitness_history = []

    for gen in range(n_generations):
        # Оценка приспособленности: максимизируем -f
        fitness = -f(pop[:, 0], pop[:, 1])
        fitness = np.maximum(fitness - np.min(fitness) + 1e-8, 1e-8)  # для рулетки

        # Сохраняем лучшее решение
        best_idx = np.argmax(fitness)
        best_individual = pop[best_idx].copy()
        best_value = f(best_individual[0], best_individual[1])
        history.append(best_individual)
        best_fitness_history.append(-fitness[best_idx])  # значение функции
        
        # Проверка сходимости по значению функции
        if len(best_fitness_history) >= patience:
            recent_values = best_fitness_history[-patience:]
            if np.std(recent_values) < tol:  # мало меняется
                # print(f"Сходимость достигнута на итерации {gen+1}")
                break

        # Проверка сходимости по координатам
        if len(history) >= patience:
            recent_points = np.array(history[-patience:])
            spread = np.mean(np.std(recent_points, axis=0))  # средний разброс по x и y
            if spread < tol:
                # print(f"Популяция сошлась к точке на итерации {gen+1}")
                break

        # Новая популяция
        new_pop = []
        for _ in range(n_population // 2):
            idx1, idx2 = np.random.choice(len(pop), size=2, p=fitness / fitness.sum())
            parent1, parent2 = pop[idx1], pop[idx2]

            # Кроссовер
            if np.random.rand() < crossover_rate:
                alpha = np.random.rand()
                child1 = alpha * parent1 + (1 - alpha) * parent2
                child2 = (1 - alpha) * parent1 + alpha * parent2
            else:
                child1, child2 = parent1.copy(), parent2.copy()

            # Мутация
            if np.random.rand() < mutation_rate:
                child1 += np.random.normal(0, sigma, size=2)
            if np.random.rand() < mutation_rate:
                child2 += np.random.normal(0, sigma, size=2)

            # Ограничение границ
            child1 = np.clip(child1, bounds[0], bounds[1])
            child2 = np.clip(child2, bounds[0], bounds[1])

            new_pop.extend([child1, child2])

        # Обновляем популяцию
        pop = np.array(new_pop)

        # Элитизм
        if len(pop) > 0:
            pop[np.random.randint(len(pop))] = best_individual

    return np.array(history), history[-1], gen+1


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
    ax1.plot_surface(X, Y, Z, cmap='viridis', alpha=0.8, edgecolor='none', linewidth=0)
    ax1.set_xlabel('X')
    ax1.set_ylabel('Y')
    ax1.set_zlabel('Z')
    ax1.set_title('Функция с N локальными минимумами')
    ax1.view_init(elev=30, azim=45)

    # Контурный график
    ax2 = fig.add_subplot(122)
    contour = ax2.contour(X, Y, Z, levels=40, cmap='viridis')
    fig.colorbar(contour, ax=ax2, label='Z = f(x, y)')
    ax2.set_xlabel('X')
    ax2.set_ylabel('Y')
    ax2.set_title('Траектории генетического алгоритма')
    ax2.grid(True, alpha=0.3)

    # Начальные точки
    num_iterations = 8

    cmap = plt.cm.hsv

    found_minima = []

    # Параметры ГА
    N_GENERATIONS = 80
    N_POPULATION = 50

    # Запуск ГА из разных начальных точек
    for i in range(num_iterations):
        # Запуск генетического алгоритма
        history, best, gen = genetic_algorithm(
            f,
            bounds=bounds,
            n_population=N_POPULATION,
            n_generations=N_GENERATIONS,
            mutation_rate=0.2,
            sigma=0.3
        )

        found_minima.append(best)
        color = cmap(i/num_iterations)

        # Извлечение истории
        x_hist = history[:, 0]
        y_hist = history[:, 1]
        z_hist = f(x_hist, y_hist)

        # Отображение ТРАЕКТОРИИ в 3D — подпись с координатами в legend
        label_3d = f'ГА {i+1} → ({best[0]:.2f}, {best[1]:.2f}), итер: {gen}'
        ax1.plot(x_hist, y_hist, z_hist, color=color, linewidth=2.0, 
                 marker='o', markersize=3, alpha=0.8, label=label_3d)
        ax1.scatter([best[0]], [best[1]], [f(best[0], best[1])],
                    color=color, s=60, edgecolor='black', depthshade=False)

        # На контурном графике — тоже линии
        label_2d = f'ГА{i+1} → ({best[0]:.2f}, {best[1]:.2f}), итер: {gen}'
        ax2.plot(x_hist, y_hist, color=color, linewidth=2.0,
                 marker='o', markersize=3, alpha=0.8, label=label_2d)
        ax2.scatter([best[0]], [best[1]], color=color, s=60, edgecolor='black')

        # Вывод в консоль
        print(f"ГА {i+1}: старт на интервале = ({bounds[0]}, {bounds[1]})")
        print(f"       → минимум ≈ ({best[0]:.6f}, {best[1]:.6f})")
        print(f"       → итераций: {gen}")

    # Фактические минимумы
    # actual_minima = [(1.5, 0.0), (-1.5, 0.0)]
    # actual_minima = [(0.0, 0.0)]
    actual_minima = [ (-4.777, -3.947), (4.747, 3.921)]
    actual_x, actual_y = zip(*actual_minima)
    actual_z = [f(x, y) for x, y in actual_minima]
    actual_minima_num = len(actual_minima)

    # Отметка фактических минимумов
    ax1.scatter(actual_x, actual_y, actual_z, color='green', s=180, marker='*',
                edgecolor='black', linewidth=2, label='Фактический минимум')
    ax2.scatter(actual_x, actual_y, color='green', s=180, marker='*',
                edgecolor='black', linewidth=2, label='Фактический минимум')

    # Группировка найденных минимумов
    unique_found = []
    tolerance = 0.2
    for pt in found_minima:
        if not any(np.linalg.norm(np.array(pt) - np.array(u)) < tolerance for u in unique_found):
            unique_found.append(pt)

    # Отметка найденных минимумов
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

    suptitle_lbl = "Оптимизация: генетический алгоритм, функция с " + str(actual_minima_num) + " локальными минимумами"
    plt.suptitle(suptitle_lbl, fontsize=16)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
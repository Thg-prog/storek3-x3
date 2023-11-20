import numpy as np
import matplotlib.pyplot as plt

# Создаем данные для графика сердца
t = np.linspace(0, 2 * np.pi, 1000)
x_heart = 16 * np.sin(t)**3
y_heart = 13 * np.cos(t) - 5 * np.cos(2*t) - 2 * np.cos(3*t) - np.cos(4*t)

# Создаем квадрат
square_x = [-20, 20, 20, -20, -20]
square_y = [-20, -20, 20, 20, -20]

# Генерируем случайные точки
num_points = 1000
x_random = np.random.uniform(-30, 30, num_points)
y_random = np.random.uniform(-30, 30, num_points)

# Определяем функцию активации (пороговую функцию)
def activation_function(x, y):
    heart_condition = (16 * (x**2 + y**2 - 256)**3 - 13 * x**2 * (x**2 + y**2 - 256) - y**2 * (x**2 + y**2 - 256)) <= 0
    square_condition = (-20 <= x <= 20) and (-20 <= y <= 20)

    if heart_condition:
        return 'heart'
    elif square_condition:
        return 'square'
    else:
        return 'outside'




# Настраиваем график
plt.figure(figsize=(6, 6))
plt.plot(x_heart, y_heart, 'r')
plt.plot(square_x, square_y, 'g')

for i in range(num_points):
    point_type = activation_function(x_random[i], y_random[i])
    if point_type == 'square':
        plt.scatter(x_random[i], y_random[i], c='g', marker='.')
    elif point_type == 'heart':
        plt.scatter(x_random[i], y_random[i], c='r', marker='.')
    else:
        plt.scatter(x_random[i], y_random[i], c='k', marker='.')

plt.xlabel('X')
plt.ylabel('Y')
plt.title('График сердца внутри квадрата с разноцветными точками')
plt.legend()

# Ограничиваем график для отображения внутри квадрата
plt.xlim(-30, 30)
plt.ylim(-30, 30)

# Отображаем график
plt.grid(True)
plt.show()

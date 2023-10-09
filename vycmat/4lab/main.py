import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

def z_func(x, y):
    return 3*x**2 + 4*y**3

def dz_dx(x, y):
    return 6*x

def dz_dy(x, y):
    return 12*y**2

def gradient_descent(x_start, y_start, learning_rate):
    x_list = [x_start]
    y_list = [y_start]
    z_list = [z_func(x_start, y_start)]

    while True:
        new_x = x_list[-1] - learning_rate*dz_dx(x_list[-1], y_list[-1])
        new_y = y_list[-1] - learning_rate*dz_dy(x_list[-1], y_list[-1])

        x_list.append(new_x)
        y_list.append(new_y)
        z_list.append(z_func(new_x, new_y))

        if ((x_list[-2] - x_list[-1])**2 + (y_list[-2] - y_list[-1])**2)**0.5 < 0.000001:
            break
        
    return x_list, y_list, z_list

x_start = 2
y_start = 2
learning_rate = 0.01

x_list, y_list, z_list = gradient_descent(x_start, y_start, learning_rate)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

point, = ax.plot([], [], [], 'ro')

def update(i):
    point.set_data(x_list[i], y_list[i])
    point.set_3d_properties(z_list[i])
    return point,

ani = FuncAnimation(fig, update, frames=len(x_list), interval=10)

ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_zlim(0, 50)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.plot_surface(np.arange(-5, 5, 0.1), np.arange(-5, 5, 0.1)[:,np.newaxis], z_func(np.arange(-5, 5, 0.1)[:,np.newaxis], np.arange(-5, 5, 0.1)[np.newaxis,:]), alpha=0.5)
plt.title('Gradient Descent')
plt.show()
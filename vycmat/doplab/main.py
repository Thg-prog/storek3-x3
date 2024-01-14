import random
import matplotlib.pyplot as plt
import numpy as np

def f(x, a, b, c, d):
    return a*x**3 + b*x**2 + c*x + d

n = 100
start_x = np.array([random.randrange(i * 50, i * 50 + 50) for i in range(n)])
start_y = np.array([np.random.uniform(low=-0.1, high=0.1) for _ in range(n)])

h = np.array([0] + [start_x[i] - start_x[i-1] for i in range(1, n)])
l = np.array([0] + [(start_y[i] - start_y[i-1]) / h[i] for i in range(1, n)])

delta = [0, -h[2]/(2*(h[1]+ h[2]))]
lmd = [0, 1.5*(l[2] - l[1])/(h[1] + h[2])]
for i in range(3, n):
    delta.append(-h[i]/(2*h[i-1] + 2*h[i] + h[i-1]*delta[i-2]))
    lmd.append((3*l[i] - 3*l[i-1] - h[i-1]*lmd[i-2])/(2*h[i-1] + 2*h[i] + h[i-1]*delta[i-2]))

b = [0 for _ in range(n)]
for i in range(n-1, 0, -1):
    b[i-1] = delta[i-1]*b[i] + lmd[i-1]

a = np.array([0] + [(b[i] - b[i-1]) / (3*h[i]) for i in range(1, n)])
c = np.array([0] + [l[i] + (2 * b[i] + b[i-1]) * h[i] / 3 for i in range(1, n)])

y = []
for i in range(start_x[0], start_x[-1]+1):
    for j in range(1, n):
        if i >= start_x[j-1] and i <= start_x[j]:
            y.append(f(i - start_x[j], a[j], b[j], c[j], start_y[j]))
            break
y = np.array(y)
x = np.linspace(start_x[0], start_x[-1], len(y))

plt.figure(figsize=(40,20))
plt.plot(x, y)
plt.scatter(start_x, start_y, c='red')
plt.grid(True) 
plt.show()
import numpy as np
import matplotlib.pyplot as plt

N = 120
x1 = np.random.random(N)
x2 = np.random.random(N)
x3 = [1] * N

def activation(x):
    return 1 if x > 0 else 0

def forward_hidden(xs, weights):
    s = np.dot(weights, xs)
    out = []
    for value in s:
        local_ar = []
        for val in value:
            local_ar.append(activation(val))
        out.append(local_ar)
    return out

def forward_out(xs, weights):
    s = np.dot(weights, xs)
    return [activation(value) for value in s]

def hidden_layers():
    weights = np.array([[0, 1, -0.2], [0, 1, -0.8], [-1.5, -1, 0.65], [1.5, 1, -1.85], [-1.5, 1, -0.35], [1.5, -1, -0.85]])
    x_in = np.array([x1, x2, x3])
    return forward_hidden(x_in, weights)

def main_layer(results):
    weights = np.array([1, -1, -1, -1, -1, -1])
    return forward_out(results, weights)

def graph(result):
    x = [0.3, 0.7, 0.9, 0.7, 0.3, 0.1, 0.3]
    y = [0.2, 0.2, 0.5, 0.8, 0.8, 0.5, 0.2]
    for i in range(N):
        if result[i] == 1:
            plt.scatter(x1[i], x2[i], c='green')
        else:
            plt.scatter(x1[i], x2[i], c='red')

    plt.plot(x, y)
    plt.show()

def main():
    result = hidden_layers()
    result = main_layer(result)
    graph(result)


if __name__ == "__main__":
    main()
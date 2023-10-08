import numpy as np
import matplotlib.pyplot as plt

N = 50
x1 = np.random.random(N)
x2 = np.random.random(N)
x3 = [1] * N

def activation(x):
    return 1 if x > 0 else 0

def forward(xs, weights):
    s = np.dot(weights, xs)
    out = [activation(value) for value in s]
    return out

def hidden_layers():
    W1 = np.array([-1, -1, 1.5])
    W2 = np.array([-1, -1, 0.5])
    W3 = np.array([-1, 1, -0.5])
    W4 = np.array([1, -1, -0.5])

    X = np.array([x1, x2, x3])
    result1 = forward(X, W1)
    result2 = forward(X, W2)
    result3 = forward(X, W3)
    result4 = forward(X, W4)

    return result1, result2, result3, result4

def main_layer(results):
    X = np.array([results[i] for i in range(len(results))])
    W = np.array([1, -1, -1, -1])
    result = forward(X, W)
    return result

def graph(result):
    A = [0, 0.5]
    B = [0.5, 0]
    C = [1, 0.5]
    D = [0.5, 1]
    E = [0.5, 0]
    F = [1, 0.5]
    G = [1, 0.5]
    H = [0.5, 0]
    for i in range(N):
        if result[i] == 1:
            plt.scatter(x1[i], x2[i], c='green')
        else:
            plt.scatter(x1[i], x2[i], c='red')

    plt.plot(A, B, C, D, E, F, G, H)
    plt.show()

def main():
    result = hidden_layers()
    result = main_layer(result)
    graph(result)


if __name__ == "__main__":
    main()
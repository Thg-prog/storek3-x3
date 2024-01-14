import numpy as np
from keras.datasets import mnist


(train_images, train_labels), (test_images, test_labels) = mnist.load_data()
test = test_labels
train_labels = train_labels[:2000]
test_lbls = test_labels
test_labels = np.zeros((len(test_lbls),10))
for i, j in enumerate(test_lbls):
    test_labels[i][j] = 1
train_images, train_labels = (train_images[0:2000].reshape(2000, 784) / 255, train_labels[0:2000])
one_hot_labels = np.zeros((len(train_labels),10))
for i, j in enumerate(train_labels):
    one_hot_labels[i][j] = 1
labels = one_hot_labels
test_images = test_images.reshape(len(test_images), 28*28) / 255
test_labels = np.zeros((len(test_labels), 10))
for i, j in enumerate(test):
    test_labels[i][j] = 1



def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return np.where(x <= 0, 0, 1)


input_size = 784
hidden_size = 130
output_size = 10
learning_rate = 0.003
epochs = 100

weights_input_hidden = np.random.uniform(-0.1, 0.1, (input_size, hidden_size))
weights_hidden_output = np.random.uniform(-0.1, 0.1, (hidden_size, output_size))
for j in range(epochs):
    for i in range(len(train_images)-1):
        start_layer = train_images[i:i+1]
        hidden_layer = relu(np.dot(start_layer, weights_input_hidden))
        end_layer = np.dot(hidden_layer, weights_hidden_output)
        end_layer_delta = labels[i:i+1] - end_layer
        hidden_layer_delta = end_layer_delta.dot(weights_hidden_output.T) * relu_derivative(hidden_layer)
        weights_hidden_output += learning_rate * hidden_layer.T.dot(end_layer_delta)
        weights_input_hidden += learning_rate * start_layer.T.dot(hidden_layer_delta)
        
for i in range(20, 30):
    start_layer = test_images[i:i+1]
    hidden_layer = relu(np.dot(start_layer, weights_input_hidden))
    end_layer = np.dot(hidden_layer, weights_hidden_output)
    prediction = end_layer
    predicted_label = np.argmax(prediction)
    true_label = np.argmax(test_labels[i:i+1])
    print(f'Предсказанная цифра: {predicted_label}, Правильная цифра: {true_label}')

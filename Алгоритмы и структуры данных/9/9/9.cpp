#include <iostream>
#include <vector>

class Graph {
    int** ar;
    int n;
    bool* visited;
    int getLocalDistance(int& sum, int fromNumber, int toNumber);
public:
    Graph();
    Graph(int** _ar, int _n);
    Graph(const Graph& gr);
    Graph(Graph&& gr) noexcept;
    void set(int** _ar, int _n);
    void printDistance(int number);
    ~Graph();
};

Graph::Graph() {
    n = 1;
    ar = new int* [n];
    for (int i = 0; i < n; i++) ar[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ar[i][j] = 0;
    visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = false;
}

Graph::Graph(int** _ar, int _n) {
    n = _n;
    ar = new int* [n];
    for (int i = 0; i < n; i++) {
        ar[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ar[i][j] = _ar[i][j];
        }
    }
    visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = false;
}

Graph::Graph(const Graph& gr) {
    n = gr.n;
    ar = new int* [n];
    for (int i = 0; i < n; i++) {
        ar[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ar[i][j] = gr.ar[i][j];
        }
    }
    visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = gr.visited[i];
}

Graph::Graph(Graph&& gr) noexcept {
    n = gr.n;
    ar = new int* [n];
    for (int i = 0; i < n; i++) {
        ar[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ar[i][j] = gr.ar[i][j];
        }
    }
    visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = gr.visited[i];
    for (int i = 0; i < n; i++) delete[] gr.ar[i];
    delete[] ar;
    delete[] visited;
}

void Graph::set(int** _ar, int _n) {
    for (int i = 0; i < n; i++)
        delete[] ar[i];
    delete[] ar;
    n = _n;
    ar = new int* [n];
    for (int i = 0; i < n; i++) {
        ar[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ar[i][j] = _ar[i][j];
        }
    }
    visited = new bool[n];
    for (int i = 0; i < n; i++) visited[i] = false;
}

int Graph::getLocalDistance(int& sum, int fromNumber, int toNumber) {
    if (fromNumber == toNumber) return sum;
    visited[fromNumber] = true;
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        if (ar[fromNumber][i] > 0 && !visited[i]) {
            sum += ar[fromNumber][i];
            int val = sum;
            int num = getLocalDistance(val, i, toNumber);
            visited[i] = false;
            if (num != 0)
                v.push_back(num);
            sum -= ar[fromNumber][i];
        }
    }
    int min = 0;
    if (v.size() > 0) {
        min = v[0];
        for (int i = 1; i < v.size(); i++) {
            if (v[i] < min) min = v[i];
        }
    }
    return min;
}

void Graph::printDistance(int number) {
    int sum = 0;
    std::cout << "Answer: ";
    for (int i = 0; i < n; i++) {
        if (i != number) {
            std::cout << getLocalDistance(sum, number, i) << " ";
            for (int j = 0; j < n; j++) visited[j] = false;
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < n; i++) 
        delete[] ar[i];
    delete[] ar;
    delete[] visited;
}

int main()
{
    std::cout << "0-to exit; 1-to set graph; 2-to find the shortest way";
    int value = 0;
    Graph gr;
    while (true) {
        std::cout << std::endl;
        std::cout << "Enter the value: ";
        std::cin >> value;
        if (value == 0) break;
        else if (value == 1) {
            std::cout << "Enter the size of matrix: ";
            int n;
            std::cin >> n;
            std::cout << "Fill in the matrix with the values" << std::endl;
            int** ar = new int* [n];
            for (int i = 0; i < n; i++) ar[i] = new int[n];
            std::cout << "  ";
            for (int i = 0; i < n; i++) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            for (int i = 0; i < n; i++) {
                std::cout << i << ":";
                for (int j = 0; j < n; j++) {
                    std::cin >> ar[i][j];
                }
            }
            gr.set(ar, n);
            for (int i = 0; i < n; i++) delete[] ar[i];
            delete[] ar;
        }
        else if (value == 2) {
            std::cout << "Enter the number from where you want to find the shortest distance: ";
            int num;
            std::cin >> num;
            gr.printDistance(num);
        }
    }
}

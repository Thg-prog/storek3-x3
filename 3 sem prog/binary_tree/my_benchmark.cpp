#include <iostream>
#include "binary_tree.hpp"
#include <benchmark/benchmark.h>
#include <thread>


static void BM_ThreadsafeBinaryTreeInsert(benchmark::State& state) {
    ThreadTree<int> tree;
    for (auto _ : state) {
        for (int i = 0; i < state.iterations(); ++i) {
            tree.add(i);
        }
    }
}

static void BM_ThreadsafeBinaryTreeFind(benchmark::State& state) {
    ThreadTree<int> tree;
    for (int i = 0; i < state.iterations(); ++i) {
        tree.add(i);
    }
    std::vector<std::thread> threads;
    for (int i = 0; i < state.threads(); ++i) {
        threads.emplace_back([&tree, &state]() {
            for (auto _ : state) {
                for (int i = 0; i < state.iterations(); ++i) {
                    benchmark::DoNotOptimize(tree.find(i));
                }
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

BENCHMARK(BM_ThreadsafeBinaryTreeInsert)->Iterations(1000000);
BENCHMARK(BM_ThreadsafeBinaryTreeFind)->Iterations(10000)->Threads(4);

BENCHMARK_MAIN();
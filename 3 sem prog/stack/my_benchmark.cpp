#include <iostream>
#include "stack.hpp"
#include <benchmark/benchmark.h>
#include <stack>


static void CustomStackBenchmark(benchmark::State& state) {
    Stack<int> custom_stack;
    for (auto _: state) {
    	for (int i = 0; i < state.iterations(); i++)
            custom_stack.push(rand());
    }
}

static void StackBenchmark(benchmark::State& state) {
    std::stack<int> std_stack;
    for (auto _: state) {
    	for (int i = 0; i < state.iterations(); i++)
            std_stack.push(rand());
    }
}

BENCHMARK(CustomStackBenchmark)->Iterations(10000000);
BENCHMARK(StackBenchmark)->Iterations(10000000);

BENCHMARK_MAIN();

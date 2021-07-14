#include <benchmark/benchmark.h>

#include <vector>
#include <random>
#include <iostream>

class ISystemTest {
public:
    virtual int OnTest(int a) = 0;
};

class SystemTestInheritance : public ISystemTest {
public:
	int OnTest(int a) override {
        return ++a;
	}
};

class SystemTest  {
public:
    int OnTest(int a) {
        return ++a;
    }
};

class __declspec(novtable) ISystemTestNoVtable {
public:
    virtual int OnTest(int a);
};

class SystemTestNoVtable: public ISystemTestNoVtable {
public:
    int OnTest(int a) override {
        return ++a;
    }
};

static void BM_SystemInheritance(benchmark::State& state)
{
    std::vector<SystemTestInheritance> systems(state.range(0));
    
    for (auto _ : state)
    {
        for (auto s : systems)
        {
           benchmark::DoNotOptimize(s.OnTest(10));
        }
    }
}


static void BM_SystemTest(benchmark::State& state)
{
    std::vector<SystemTest> systems(state.range(0));

    for (auto _ : state)
    {
        for (auto s : systems)
        {
            benchmark::DoNotOptimize(s.OnTest(10));
        }
    }
}

static void BM_SystemTestHineritanceNoVtable(benchmark::State& state)
{
    std::vector<SystemTestNoVtable> systems(state.range(0));

    for (auto _ : state)
    {
        for (auto s : systems)
        {
            benchmark::DoNotOptimize(s.OnTest(10));
        }
    }
}

BENCHMARK(BM_SystemTest)->Range(1, 1 << 16);
BENCHMARK(BM_SystemInheritance)->Range(1, 1 << 16);
BENCHMARK(BM_SystemTestHineritanceNoVtable)->Range(1, 1 << 16);

/*
 * Conclusion:
 * - Faster to use no inheritance (up to 20% time faster)
 */

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
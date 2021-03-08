#include <benchmark/benchmark.h>

#include <vector>
#include <random>
#include <iostream>

#include <system.h>

class ISystemTest {
public:
    virtual int OnTest(int a) = 0;
};

class SystemTestInheritance : public alloy::ecs::System, public ISystemTest {
public:
	int OnTest(int a) override {
        return ++a;
	}
};

class SystemTest : public alloy::ecs::System {
public:
    int OnTest(int a) {
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

BENCHMARK(BM_SystemInheritance)->Range(1, 1 << 12);

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

BENCHMARK(BM_SystemTest)->Range(1, 1 << 12);
BENCHMARK(BM_SystemInheritance)->Range(1, 1 << 12);

/*
 * Conclusion:
 * - Faster to use no inheritance (up to 20% time faster)
 */

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
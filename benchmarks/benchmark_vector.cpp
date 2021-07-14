#include <benchmark/benchmark.h>

#include <vector>
#include <random>
#include <iostream>

#include <vector.h>

const long fromRange = 8;
const long toRange = 1 << 15;
const float maxNmb = 100.0f;

void RandomFill(std::vector<math::fvec2>& numbers, float start = -maxNmb, float end = maxNmb)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> dist{start, end};
    std::generate(numbers.begin(), numbers.end(), [&g, &dist]() { return math::fvec2(dist(g), dist(g)); });
}

void RandomFill(std::vector<math::fvec3>& numbers, float start = -maxNmb, float end = maxNmb)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> dist{ start, end };
    std::generate(numbers.begin(), numbers.end(), [&g, &dist]() { return math::fvec3(dist(g), dist(g), dist(g)); });
}

static void BM_Vec2Magnitude(benchmark::State& state)
{

    std::vector<math::fvec2> local_numbers(state.range(0));
    RandomFill(local_numbers, 0.0f, maxNmb);
    for (auto _ : state)
    {
        for (auto v : local_numbers)
        {
            float f = v.Magnitude();
            benchmark::DoNotOptimize(f);
        }
    }
}

BENCHMARK(BM_Vec2Magnitude)->Range(fromRange, toRange);

static void BM_Vec3Magnitude(benchmark::State& state)
{

    std::vector<math::fvec3> local_numbers(state.range(0));
    RandomFill(local_numbers, 0.0f, maxNmb);
    for (auto _ : state)
    {
        for (auto v : local_numbers)
        {
            float f = v.Magnitude();
            benchmark::DoNotOptimize(f);
        }
    }
}

BENCHMARK(BM_Vec3Magnitude)->Range(fromRange, toRange);

/*
 * Conclusion of previous tests
 * - Vector2 => Using copy or ref is equivalent in time
 * - Vector3 => Using ref is faster than copy for dot //TODO test for every function to make sure
 */

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
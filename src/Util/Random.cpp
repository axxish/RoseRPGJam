#include <random>

int random(int min, int max)
{
    static std::mt19937 rng(std::random_device{}()); // Seed the RNG once
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}
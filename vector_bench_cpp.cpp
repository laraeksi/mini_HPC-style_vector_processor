#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>  // for std::inner_product

// Templated vector addition: works for float, double, etc.
template <typename T>
void vector_add(const std::vector<T>& a,
                const std::vector<T>& b,
                std::vector<T>& out) {
    std::size_t n = a.size();
    for (std::size_t i = 0; i < n; ++i) {
        out[i] = a[i] + b[i];
    }
}

// Templated dot product using std::inner_product
template <typename T>
T dot_product(const std::vector<T>& a,
              const std::vector<T>& b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), static_cast<T>(0));
}

int main() {
    using T = float;                    // change to double if you like
    const std::size_t n = 10'000'000;   // 10 million elements

    std::cout << "VectorBench++ (C++17)\n";
    std::cout << "Vector length: " << n << "\n";

    // Allocate vectors on the heap (handled automatically by std::vector)
    std::vector<T> a(n);
    std::vector<T> b(n);
    std::vector<T> out(n);

    // Random number generation in [0, 1)
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<T> dist(0.0f, 1.0f);

    for (std::size_t i = 0; i < n; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    // Time the vector addition using high-resolution clock
    auto start = std::chrono::high_resolution_clock::now();
    vector_add(a, b, out);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double seconds = elapsed.count();

    // Compute dot product as another numerical operation
    T dp = dot_product(a, b);

    std::cout << "Time for vector add: " << seconds << " seconds\n";

    // Throughput in million additions per second
    double ops  = static_cast<double>(n);          // one add per element
    double mops = ops / 1e6 / seconds;

    std::cout << "Throughput: " << mops
              << " million additions per second\n";
    std::cout << "Dot product a.b = " << dp << "\n";

    return 0;
}

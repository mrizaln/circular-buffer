#include <boost/circular_buffer.hpp>
#include <circbuf/circbuf.hpp>

#include <chrono>
#include <iostream>
#include <random>
#include <ratio>

namespace chr = std::chrono;

using Ms    = chr::duration<double, std::milli>;
using Clock = chr::steady_clock;

Ms to_ms(Clock::duration d)
{
    return chr::duration_cast<Ms>(d);
}

template <template <typename T> typename Tmpl>
Ms push(std::size_t capacity, std::size_t iter)
{
    auto start  = Clock::now();
    auto buffer = Tmpl<double>{ capacity };

    static auto rng  = std::mt19937{ std::random_device{}() };
    static auto dist = std::uniform_real_distribution<double>{ 0.0, 1.0 };

    for (std::size_t i = 0; i < iter; ++i) {
        buffer.push_back(dist(rng));
    }

    return to_ms(Clock::now() - start);
}

template <template <typename T> typename Tmpl>
Ms push_then_pop(std::size_t capacity, std::size_t iter)
{
    auto start  = Clock::now();
    auto buffer = Tmpl<double>{ capacity };

    static auto rng  = std::mt19937{ std::random_device{}() };
    static auto dist = std::uniform_real_distribution<double>{ 0.0, 1.0 };

    auto vector = std::vector<double>{};
    vector.reserve(capacity * 2);

    for (std::size_t i = 0; i < iter; ++i) {
        buffer.push_back(dist(rng));
        if (i % (capacity * 2) == 0) {
            vector.clear();

            for (std::size_t i = 0; i < buffer.size(); ++i) {
                vector.push_back(buffer.front());
                buffer.pop_front();
            }
        }
    }

    return to_ms(Clock::now() - start);
}

Ms repeat(std::invocable auto fn, std::size_t count)
{
    auto total = Ms{ 0 };
    for (std::size_t i = 0; i < count; ++i) {
        total += fn();
    }
    return total / count;
}

int main()
{
    constexpr auto capacity = 1024;
    constexpr auto iter     = 1'000'000;

    // auto boost_push   = push<boost::circular_buffer>(capacity, iter);
    // auto circbuf_push = push<circbuf::CircBuf>(capacity, iter);

    auto boost_push   = repeat([&] { return push<boost::circular_buffer>(capacity, iter); }, 10);
    auto circbuf_push = repeat([&] { return push<circbuf::CircBuf>(capacity, iter); }, 10);

    std::cout << "Boost: " << boost_push.count() << "ms\n";
    std::cout << "CircBuf: " << circbuf_push.count() << "ms\n";

    // auto boost_push_pop   = push_then_pop<boost::circular_buffer>(capacity, iter);
    // auto circbuf_push_pop = push_then_pop<circbuf::CircBuf>(capacity, iter);

    auto boost_push_pop   = repeat([&] { return push_then_pop<boost::circular_buffer>(capacity, iter); }, 10);
    auto circbuf_push_pop = repeat([&] { return push_then_pop<circbuf::CircBuf>(capacity, iter); }, 10);

    std::cout << "Boost: " << boost_push_pop.count() << "ms\n";
    std::cout << "CircBuf: " << circbuf_push_pop.count() << "ms\n";
}

#include <takewhile.hpp>

#include <vector>
#include <array>
#include <string>
#include <utility>

#include "helpers.hpp"
#include "catch.hpp"

using iter::takewhile;
using Vec = const std::vector<int>;


namespace {
    bool under_ten(int i) {
        return i < 10;
    }

    struct UnderTen {
        bool operator()(int i) {
            return i < 10;
        }
    };
}

TEST_CASE("takewhile: works with lambda, callable, and function pointer",
        "[takewhile]") {
    Vec ns = {1, 3, 5, 20, 2, 4, 6, 8};
    SECTION("function pointer") {
        auto tw = takewhile(under_ten, ns);
        Vec v(std::begin(tw), std::end(tw));
        Vec vc = {1, 3, 5};
        REQUIRE( v == vc );
    }

    SECTION("callable object") {
        auto tw = takewhile(UnderTen{}, ns);
        Vec v(std::begin(tw), std::end(tw));
        Vec vc = {1, 3, 5};
        REQUIRE( v == vc );
    }

    SECTION("lambda") {
        auto tw = takewhile([](int i){ return i < 10; }, ns);
        Vec v(std::begin(tw), std::end(tw));
        Vec vc = {1, 3, 5};
        REQUIRE( v == vc );
    }
}

TEST_CASE("takewhile: empty iterable is empty", "[takewhile]") {
    Vec ns{};
    auto tw = takewhile(under_ten, ns);
    REQUIRE( std::begin(tw) == std::end(tw) );
}
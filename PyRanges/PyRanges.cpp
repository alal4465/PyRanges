#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include "range.h"
#include "PipeFunc.h"
#include "enumerate.h"
#include "zip.h"
#include <tuple>
#include <utility>

int main() {
    for (auto&& [i, n] : PyRanges::range(3, 5) | PyRanges::enumerate) {
        std::cout << '[' << i << ", " << n << "]\n";
    }

    for (auto&& [a, b] :PyRanges::zip(std::vector{ "a", "b" }, std::vector{ 1, 2, 3 })) {
        std::cout << '[' << a << ", " << b << "]\n";
    }
}


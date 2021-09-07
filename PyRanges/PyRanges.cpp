#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include "Range.h"
#include "PipeFunc.h"
#include "enumerate.h"

int main() {
    for (auto&& [i, n] : PyRanges::range(3, 5) | PyRanges::enumerate) {
        std::cout << '[' << i << ", " << n << "]\n";
    }
}


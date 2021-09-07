#include <iostream>
#include <ranges>
#include <algorithm>
#include "Range.h"
#include <vector>
#include "pipes.h"
#include "enumerate.h"
#include "zip.h"

int main() {
    for (auto&& [i, n] : PyRanges::Range(3, 5) | PyRanges::enumerate) {
        std::cout << '[' << i << ", " << n << "]\n";
    }
}


# PyRanges
Me wasting time with writing some itertools esque functionality in C++ 20's ranges style.   

Stuff like:
```cpp
for (auto&& [i, n] : PyRanges::range(3, 5) | PyRanges::enumerate) {
  std::cout << '[' << i << ", " << n << "]\n";
}
/*
[0, 3]
[1, 4]
*/
```

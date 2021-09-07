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

**Edit:** I just found out this is basically just a worst version of [cppitertools](https://github.com/ryanhaining/cppitertools).   

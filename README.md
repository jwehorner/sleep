# Sleep

## Contents

* [About](#about)
* [Prerequisites](#prerequisites)
* [Testing](#testing)
* [Contact](#contact)

## About

This library provides functions for achieving high resolution sleep durations across multiple platforms. On UNIX systems this is done using ```nanosleep```, however on Windows machines a combination of techniques is used to achieve a tradeoff between resolution and performance. See the docs for more details.

## Prerequisites

* CMake
* A C++ compiler (at least C++17)

## Testing

1. Create a build directory using:
```bash
mkdir build && cd build
```

2. Configure CMake with the BUILD_SLEEP_TESTS option on:
```bash
cmake .. -DBUILD_SLEEP_TESTS=ON
```

3. Build the unit test target using:
```bash
cmake --build .
```

4. Go the to executable directory:
* On Windows:
```bash
cd test/unit_tests/Debug
```
* On other platforms:
```bash
cd test/unit_tests
```

5. Run the unit test executable (```sleep_unit_tests```) with any of the additional options:
	* ```[test]``` runs all the unit tests (which write their results to the test/results folder).
	* ```[benchmark]``` runs all the benchmarks which print the results to the console.
	* ```[short]``` runs the short duration unit tests (which are most pertinent to high resolution operation).
	* ```[short]``` runs the long duration unit tests.

## Contact

James Horner - jwehorner@gmail.com or James.Horner@nrc-cnrc.gc.ca

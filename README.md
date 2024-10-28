# Triangle Intersection

## About

Checks intersection of triangles in 3 dimentional space.

### Key Features

- **Spacial hashing** - to optimize intersetion
- **Thomas Möller's Triangle-Triangle Intersection test algorithm**


## Getting Started

1) Install Dependencies

	- Create a virtual environment and install Conan:
	```
	python3 -m venv .venv && source .venv/bin/activate && pip3 install conan
	```

	- Install project dependencies with Conan:a
	```
	conan install . --output-folder=third_party --build=missing
	```

2) Build the project:
	```
	cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./third_party/conan_toolchain.cmake
	cmake --build build
	```

## Usage

### Integrate in Your Project

Simply include `t_inter.h` in your code

### Try the Example Main Program

1) `mkdir build`

2) `cd build`

3) `cmake ..`

4) `make`

5) `./intersect.x`

### Running Tests

1) `cmake ..`
2) `make`
3) `ctest`

#### CMake Configuration Options

Customize the build with the following CMake options:

- **Big Data Tests**: For testing with large datasets, enable big data tests:
```
cmake .. -DENABLE_BD_TESTS=ON DENABLE_PERFECT_BD_TESTS=ON
```

- **Logging**: Enable logging for debugging purposes:
```
cmake .. -DENABLE_LOGGING
```

- **Debug Build**: Compile in Debug mode for additional diagnostic:
```
cmake .. -DCMAKE_BUILD_TYPE=Debug
```






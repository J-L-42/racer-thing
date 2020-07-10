# Simple racing game using Simple and Fast Multimedia Library (SFML)

## Usage

Navigate to the location of the binary and run:
```bash
$ ./Main
```

## Compiling

Requires SFML - https://www.sfml-dev.org/

This project uses CMake. To compile, create a `bin` directory at the root of the project and run:
```bash
$ cd bin
$ cmake ../src
$ cmake --build .
```
Currently the project only supports Linux, although it shouldn't be too hard to get it running on
Windows/MacOS.

Sound effects have been removed for licensing reasons, however the game compiles and runs without
them.

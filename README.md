# Shooter

[![Build Status](https://travis-ci.org/simplay/shooter.svg?branch=master)](https://travis-ci.org/simplay/shooter)

## Dependencies

+ `cmake >= 3.1.3`
+ `gcc`
+ `libsdl2`

### Ubuntu

`sudo apt install cmake libsdl2-dev g++`

### Max OS X

`brew install sdl2`

## Setup

1. Clone this repository: `git@github.com:simplay/shooter.git`
2. Fetch and update all external dependencies: `git submodule update --init --recursive`

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target:

``` bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Usage

Inside `build/`, execute `./main.x`

## Help

Inside `build/`, execute `./main.x --help`

## Running the tests

Inside `build/`, execute `./unit_tests.x`

## Contributing

1. Fork this repository
2. Create your feature branch `git checkout -b my-new-feature`
3. Commit your changes `git commit -am "Add some feature"`
4. Push to the branch `git push origin my-new-feature`
5. Create new Pull Request (in your forked repository)

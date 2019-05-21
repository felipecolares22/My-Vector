# My Vector
In this project our objective is to build our version or the std::vector, the sc::vector.

### Dependencies
*`cmake`
*`make`
*`g++`
*`google tests`
*`Doxygen (to gerenate code documentation)`

### Usage
To use the library, you will need to import the `vector.h` file located on the `include` folder to your project.Look the documentation for a more detailed explanation of each sc::vector method.

### Generate Documentation
Go to your project directory and type

```bash
doxygen config
```

Then, open in your browser the `index.html` file, located on the `docs/html` folder.

### Run Tests

#### Compile
To test the `sc::vector` library, go to the project directory and type

```bash
mkdir build
cd build
cmake ../
make
```

#### Run
Type `./vector_tests` and see the results.

## Authorship
Program developed by [Matheus de Andrade](https://github.com/matheusmas132) and [Felipe Colares](https://github.com/felipecolares22), 2019.1


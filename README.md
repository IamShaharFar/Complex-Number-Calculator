
# Complex Number Calculator

## Overview

This project is a command-line application for performing operations on complex numbers. It supports various functionalities like addition, subtraction, multiplication, and absolute value calculations for complex numbers. The application is built in ANSI C and adheres to best practices for portable, efficient C programming.

This project is one of many programming assignments in the Computer Science course at the Open University, part of my Computer Science degree.

## Features

- Read and define up to 6 complex variables.
- Perform arithmetic operations:
  - Addition
  - Subtraction
  - Multiplication by real or imaginary numbers
  - Multiplication between complex numbers
- Calculate the absolute value of a complex number.
- User-friendly command input interface.
- Supports interactive and file-based input/output.

## Requirements

- A C compiler that supports ANSI C standards (e.g., GCC).
- A Unix-like shell or Windows command prompt for running the application.

## How to Compile

1. Ensure you have a compatible C compiler installed (e.g., GCC).
2. Use the provided `Makefile` for easy compilation.

Run the following command in the terminal:

```bash
make
```

This will produce an executable file named `mycomp`.

## How to Run

There are three ways to run the program:

### Interactive Mode
Run the program directly and input commands interactively:
```bash
./mycomp
```

### Input File Mode
Provide an input file for batch processing:
```bash
./mycomp < input.txt
```

### Input and Output File Mode
Provide an input file and redirect output to a file:
```bash
./mycomp < input.txt > output.txt
```

## Commands

The application supports the following commands:

- `read_comp <variable>, <real>, <imaginary>`: Reads a complex number into a variable (A-F).
- `print_comp <variable>`: Prints the value of a complex number.
- `add_comp <var1>, <var2>`: Adds two complex numbers.
- `sub_comp <var1>, <var2>`: Subtracts the second complex number from the first.
- `mult_comp_real <variable>, <real>`: Multiplies a complex number by a real number.
- `mult_comp_img <variable>, <imaginary>`: Multiplies a complex number by an imaginary number.
- `mult_comp_comp <var1>, <var2>`: Multiplies two complex numbers.
- `abs_comp <variable>`: Calculates and prints the absolute value of a complex number.
- `stop`: Ends the program.

## Example Usage

### Input
```text
read_comp A, 3.5, -2.1
print_comp A
add_comp A, B
stop
```

### Output
```text
3.50 + (-2.10)i
Error: Undefined complex variable
```

## Error Handling

The program detects and reports errors such as:
- Invalid variable names.
- Missing or extra parameters.
- Improper command syntax.
- Undefined variables.

Refer to the `input2errors.txt` file for examples of erroneous commands.

## Cleaning Up

To clean the project files, run:
```bash
make clean
```

This will remove all object files and the compiled executable.

## Author

This project was designed to demonstrate advanced ANSI C programming skills and effective use of modular code design.

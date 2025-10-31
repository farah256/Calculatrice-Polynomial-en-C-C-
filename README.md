# Calculatrice-Polynomial-en-C-C-
A comprehensive C program for performing various operations on polynomials with fraction coefficients.
## 📋 Features

- **Basic Operations**: Addition, subtraction, multiplication of polynomials
- **Advanced Operations**: Power, derivative, integral calculations
- **Fraction Support**: Handles coefficients as fractions (e.g., 7/2, 3/4)
- **Memory Efficient**: Uses linked lists for polynomial representation
- **User-Friendly**: Interactive menu-driven interface

## 🚀 Operations Supported

1. Input polynomials P and Q
2. Display polynomials
3. Update polynomials
4. P + Q - Polynomial addition
5. P - Q - Polynomial subtraction
6. P × Q - Polynomial multiplication
7. Pⁿ - Polynomial power (raise to exponent n)
8. P → Q - Assign polynomial P to Q
9. dP/dx - Derivative of polynomial P
10. ∫P dx - Integral of polynomial P
11. P(x) - Evaluate polynomial at given x value

## 📁 Project Structure
polynomial_calculator/
├── main.c # Program entry point
├── polynomial.h # Header file with structures and declarations
├── polynomial.c # Core polynomial operations implementation
├── menu.c # User interface and menu handling
└── Makefile # Build configuration

text

## 🔧 Compilation

### Using Makefile (Recommended):
```bash
make                    # Build the program
make run               # Build and run
make clean             # Clean build files
```
### Manual Compilation:
```bash
clang -Wall -Wextra -std=c99 -g main.c polynomial.c menu.c -o polynomial_calculator -lm
```
### Usage
Run the program:
```
bash
./polynomial_calculator
```
Follow the menu prompts to perform operations

Input polynomial format examples:

X^3 + 2X + 1

3X^2 - 7/2X + 5

X^4 + 2/3X^2 - 1/4


Academic Year 2023-2024


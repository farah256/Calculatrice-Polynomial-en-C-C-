#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT 30

// Structure for fraction representation
typedef struct {
    int numerator;
    int denominator;
} Fraction;

// Structure for monomial
typedef struct Monome {
    Fraction coefficient;
    int exponent;
    struct Monome* next;
} Monome;

// Structure for polynomial (linked list)
typedef struct Polynome {
    Monome* head;
} Polynome;

// Function declarations
int searchChar(char c, char* str);
void addMonomial(Monome* monome, Polynome* P);
Polynome INPUT_POLYNOMIAL(void);
void UPDATE_POLYNOMIAL(Polynome* P);
void DISPLAY_POLYNOMIAL(Polynome P);
Polynome ADD_POLYNOMIALS(Polynome P, Polynome Q);
Polynome SUBTRACT_POLYNOMIALS(Polynome P, Polynome Q);
Polynome MULTIPLY_POLYNOMIALS(Polynome P, Polynome Q);
Polynome POWER_POLYNOMIAL(Polynome P, int n);
void ASSIGN_POLYNOMIAL(Polynome* dest, Polynome src);
Polynome DERIVATIVE(Polynome P);
Polynome INTEGRAL(Polynome P);
double EVALUATE_POLYNOMIAL(Polynome P, double x);
void FREE_POLYNOMIAL(Polynome* P);

// Menu function declaration
void runMenu(void);

#endif
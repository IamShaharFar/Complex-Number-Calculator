/* complex.c */
#include <stdio.h>
#include <math.h>
#include "complex.h"

void init_comp(Complex *c) {
    if (c != NULL) {
        c->real = 0.0;
        c->imag = 0.0;
    }
}

/* sets the values of a complex number */
void read_comp(Complex *c, double real, double imag) {
    if (c != NULL) {
        c->real = real;
        c->imag = imag;
    }
}

/* prints a complex number in the format: a + (bi) */
void print_comp(Complex c) {
    printf("%.2f + (%.2f)i\n", c.real, c.imag);
}

/* adds two complex numbers and prints the result */
void add_comp(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    print_comp(result);
}

/* subtracts two complex numbers and prints the result */
void sub_comp(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    print_comp(result);
}

/* multiplies a complex number by a real number and prints the result */
void mult_comp_real(Complex c, double real) {
    Complex result;
    result.real = c.real * real;
    result.imag = c.imag * real;
    print_comp(result);
}

/* multiplies a complex number by an imaginary number and prints the result */
void mult_comp_img(Complex c, double img) {
    Complex result;
    result.real = -c.imag * img;
    result.imag = c.real * img;
    print_comp(result);
}

/* multiplies two complex numbers and prints the result */
void mult_comp_comp(Complex a, Complex b) {
    Complex result;
    result.real = (a.real * b.real) - (a.imag * b.imag);
    result.imag = (a.real * b.imag) + (a.imag * b.real);
    print_comp(result);
}

/* calculates and prints the absolute value of a complex number */
void abs_comp(Complex c) {
    double result = sqrt(c.real * c.real + c.imag * c.imag);
    printf("%.2f\n", result);
}

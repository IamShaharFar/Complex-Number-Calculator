#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double imag;
} Complex;

void init_comp(Complex *c);
void read_comp(Complex *c, double real, double imag);
void print_comp(Complex c);
void add_comp(Complex a, Complex b);
void sub_comp(Complex a, Complex b);
void mult_comp_real(Complex c, double real);
void mult_comp_img(Complex c, double img);
void mult_comp_comp(Complex a, Complex b);
void abs_comp(Complex c);

#endif
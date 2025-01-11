/* commands.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"

#define MAX_INPUT 100

/* helper function declarations */
static void print_error(const char *error);
static int is_valid_var_name(char c);
static int parse_double(char *str, double *result);
static void skip_spaces(char **str);
static int check_consecutive_commas(const char *str);
static int has_illegal_leading_comma(const char *str);
static int check_and_print_mult_comma_error(char *ptr);
static int check_and_print_var_name_error(char var_name);
static int check_end_of_command(char *ptr);
static int check_missing_parameter(char *ptr);
static int check_missing_comma(char **ptr);

/* command handler function declarations */
static int handle_read_comp(char *ptr, Complex vars[]);
static int handle_print_comp(char *ptr, Complex vars[]);
static int handle_add_comp(char *ptr, Complex vars[]);
static int handle_sub_comp(char *ptr, Complex vars[]);
static int handle_mult_comp_real(char *ptr, Complex vars[]);
static int handle_mult_comp_img(char *ptr, Complex vars[]);
static int handle_mult_comp_comp(char *ptr, Complex vars[]);
static int handle_abs_comp(char *ptr, Complex vars[]);
static int handle_stop(char *ptr);

/* helper function implementations */

static void print_error(const char *error)
{
    printf("Error: %s\n", error);
}

/* checks if variable name is between A-F */
static int is_valid_var_name(char var_name)
{
    return var_name >= 'A' && var_name <= 'F';
}

/* moves pointer past whitespace characters */
static void skip_spaces(char **str)
{
    while (isspace(**str))
    {
        (*str)++;
    }
}

/* converts string to double if possible 
* parameters: str - pointer to the string, result - pointer to the double */
static int parse_double(char *str, double *result)
{
    char *endptr;
    *result = strtod(str, &endptr);
    return endptr != str;
}

/* checks if string has two commas in a rows */
static int check_consecutive_commas(const char *str)
{
    char *ptr = (char *)str;

    /* find first comma */
    while (*ptr && *ptr != ',')
    {
        ptr++;
    }

    /* if no comma found or end of string */
    if (!*ptr || !*(ptr + 1))
    {
        return 0;
    }

    /* move past comma and check for next comma after spaces */
    ptr++;
    skip_spaces(&ptr);
    return *ptr == ',';
}

/* checks if string starts with comma after spaces */
static int has_illegal_leading_comma(const char *str)
{
    while (isspace(*str))
        str++;
    return *str == ',';
}

/* checks for consecutive commas and prints error if found */
static int check_and_print_mult_comma_error(char *ptr)
{
    if (check_consecutive_commas(ptr))
    {
        print_error("Multiple consecutive commas");
        return 1; /* error found */
    }
    return 0; /* no error */
}

/* checks if variable name is valid (A-F) and prints error if not */
static int check_and_print_var_name_error(char var_name) {
    if (!is_valid_var_name(var_name)) {
        print_error("Undefined complex variable");
        return 1;  /* error found */
    }
    return 0;  /* no error */
}

/* checks if command ended properly or has extra text */
static int check_end_of_command(char *ptr) {
    if (*ptr != '\0') {
        print_error("Extraneous text after end of command");
        return 1;  /* error found */
    }
    return 0;  /* no error */
}

/* checks if there's a missing parameter in the command */
static int check_missing_parameter(char *ptr) {
    if (*ptr == '\0') {
        print_error("Missing parameter");
        return 1;  /* error found */
    }
    return 0;  /* no error */
}

/* checks if expected comma is present and advances pointer */
static int check_missing_comma(char **ptr) {
    if (**ptr != ',') {
        print_error("Missing comma");
        return 1;  /* error found */
    }
    (*ptr)++;  /* advance pointer past comma */
    return 0;  /* no error */
}

/* implementation of command processing 
* parameters: line - pointer to the string, vars - array of complex numbers */
int process_command(char *line, Complex vars[])
{
    char cmd[MAX_INPUT];
    char *ptr = line;

    /* skip leading whitespace */
    skip_spaces(&ptr);

    /* get command name */
    if (sscanf(ptr, "%s", cmd) != 1)
    {
        return 0; /* empty line */
    }

    ptr += strlen(cmd);

    if (has_illegal_leading_comma(ptr))
    {
        print_error("Illegal comma");
        return 0;
    }

    /* check which command to run */
    if (strcmp(cmd, "stop") == 0)
    {
        return handle_stop(ptr);
    }
    if (strcmp(cmd, "read_comp") == 0)
    {
        return handle_read_comp(ptr, vars);
    }
    if (strcmp(cmd, "print_comp") == 0)
    {
        return handle_print_comp(ptr, vars);
    }
    if (strcmp(cmd, "add_comp") == 0)
    {
        return handle_add_comp(ptr, vars);
    }
    if (strcmp(cmd, "sub_comp") == 0)
    {
        return handle_sub_comp(ptr, vars);
    }
    if (strcmp(cmd, "mult_comp_real") == 0)
    {
        return handle_mult_comp_real(ptr, vars);
    }
    if (strcmp(cmd, "mult_comp_img") == 0)
    {
        return handle_mult_comp_img(ptr, vars);
    }
    if (strcmp(cmd, "mult_comp_comp") == 0)
    {
        return handle_mult_comp_comp(ptr, vars);
    }
    if (strcmp(cmd, "abs_comp") == 0)
    {
        return handle_abs_comp(ptr, vars);
    }

    print_error("Undefined command name");
    return 0;
}

/* command handler implementations */

/* handles program exit command */
/*parameters: ptr - pointer to the string*/
static int handle_stop(char *ptr)
{
    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;
    return -1;
}

/* reads new complex number from user input */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_read_comp(char *ptr, Complex vars[])
{
    char var_name;
    double real, imag;
    char *endptr;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name = *ptr++;
    if (check_and_print_var_name_error(var_name)) return 0;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (!parse_double(ptr, &real))
    {
        print_error("Invalid parameter - not a number");
        return 0;
    }

    /* Move past first number */
    strtod(ptr, &endptr);
    ptr = endptr;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (!parse_double(ptr, &imag))
    {
        print_error("Invalid parameter - not a number");
        return 0;
    }

    /* Move past second number */
    strtod(ptr, &endptr);
    ptr = endptr;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    read_comp(&vars[var_name - 'A'], real, imag);
    return 0;
}

/* prints a complex number to screen */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_print_comp(char *ptr, Complex vars[])
{
    char var_name;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    /* get variable name */
    var_name = *ptr++;
    if (check_and_print_var_name_error(var_name)) return 0;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    print_comp(vars[var_name - 'A']);
    return 0;
}

/* adds two complex numbers and prints the result */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_add_comp(char *ptr, Complex vars[])
{
    char var_name1, var_name2;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name1 = *ptr++;
    if (check_and_print_var_name_error(var_name1)) return 0;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;
    var_name2 = *ptr++;
    if (check_and_print_var_name_error(var_name2)) return 0;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    add_comp(vars[var_name1 - 'A'], vars[var_name2 - 'A']);
    return 0;
}

/* subtracts two complex numbers and prints the result */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_sub_comp(char *ptr, Complex vars[])
{
    char var_name1, var_name2;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name1 = *ptr++;
    if (check_and_print_var_name_error(var_name1)) return 0;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name2 = *ptr++;
    if (check_and_print_var_name_error(var_name2)) return 0;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    sub_comp(vars[var_name1 - 'A'], vars[var_name2 - 'A']);
    return 0;
}

/* multiplies a complex number by a real number and prints the result */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_mult_comp_real(char *ptr, Complex vars[])
{
    char var_name;
    double real;
    char *endptr;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name = *ptr++;
    if (check_and_print_var_name_error(var_name)) return 0;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (!parse_double(ptr, &real))
    {
        print_error("Invalid parameter - not a number");
        return 0;
    }

    /* Move pointer past the number */
    strtod(ptr, &endptr);
    ptr = endptr;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    mult_comp_real(vars[var_name - 'A'], real);
    return 0;
}

/* multiplies a complex number by an imaginary number and prints the result */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_mult_comp_img(char *ptr, Complex vars[])
{
    char var_name;
    double imag;
    char *endptr;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name = *ptr++;
    if (check_and_print_var_name_error(var_name)) return 0;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (!parse_double(ptr, &imag))
    {
        print_error("Invalid parameter - not a number");
        return 0;
    }

    /* Move pointer past the number */
    strtod(ptr, &endptr);
    ptr = endptr;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    mult_comp_img(vars[var_name - 'A'], imag);
    return 0;
}

/* multiplies two complex numbers and prints the result */
/*parameters: ptr - pointer to the string, vars - array of complex numbers*/
static int handle_mult_comp_comp(char *ptr, Complex vars[])
{
    char var_name1, var_name2;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name1 = *ptr++;
    if (check_and_print_var_name_error(var_name1)) return 0;

    skip_spaces(&ptr);
    if (check_missing_comma(&ptr)) return 0;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name2 = *ptr++;
    if (check_and_print_var_name_error(var_name2)) return 0;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    mult_comp_comp(vars[var_name1 - 'A'], vars[var_name2 - 'A']);
    return 0;
}

/* calculates the absolute value of a complex number and prints the result */
/*parameters: ptr - pointer to the command string, vars - array of complex numbers*/
static int handle_abs_comp(char *ptr, Complex vars[])
{
    char var_name;

    if (check_and_print_mult_comma_error(ptr)) return 0;

    skip_spaces(&ptr);
    if (check_missing_parameter(ptr)) return 0;

    var_name = *ptr++;
    if (check_and_print_var_name_error(var_name)) return 0;

    skip_spaces(&ptr);
    if (check_end_of_command(ptr)) return 0;

    abs_comp(vars[var_name - 'A']);
    return 0;
}
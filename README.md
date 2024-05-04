# Cramer's Rule Solver

## Description
This program solves systems of linear equations using Cramer's Rule. It takes equations in the form of `ax + by = c` and calculates the values of variables `x`, `y`, etc., to satisfy the equations.

## Features
- Supports systems of linear equations with any number of variables.
- Handles equations in the form `ax + by = c`.
- Outputs the unique solution set for the system of equations.

## Usage
1. Compile the program using a C++ compiler.
2. Run the compiled executable.
3. Enter the size of the coefficient matrix (number of equations).
4. Enter each equation in the specified format (`ax + by = c`) with spaces after each variable.
5. The program will output the unique solution set for the system of equations.

## Example 
```cpp
=========================Cramer's Rule Calculator=========================

Enter Equations in the following form: i.e. 2x + 3y + 4z = 5
(Make Sure to Include Spaces After each Variable)

Enter Size of nxn Matrix: 3
Enter Equation 1: 2x + 3y + 2z = 2
Enter Equation 2: 3x - 3y + 5z = 6
Enter Equation 3: 4x + y - 2z = -3

x = -0.118182
y = -0.0727273
z = 1.22727

Coefficient matrix:
2 3 2
3 -3 5
4 1 -2

Solution vector:
2
6
-3

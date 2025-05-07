#Shell Arithmetic
#!/bin/bash

# Function Definitions
add() {
    echo "Addition: $1 + $2 = $(($1 + $2))"
}

subtract() {
    echo "Subtraction: $1 - $2 = $(($1 - $2))"
}

multiply() {
    echo "Multiplication: $1 * $2 = $(($1 * $2))"
}

divide() {
    if [ $2 -eq 0 ]; then
        echo "Division: Error - Division by zero"
    else
        echo "Division: $1 / $2 = $(($1 / $2))"
    fi
}

modulus() {
    if [ $2 -eq 0 ]; then
        echo "Modulus: Error - Modulus by zero"
    else
        echo "Modulus: $1 % $2 = $(($1 % $2))"
    fi
}

# Input Section
echo "Enter first number:"
read num1

echo "Enter second number:"
read num2

# Perform All Operations
echo "Performing all arithmetic operations:"
add $num1 $num2
subtract $num1 $num2
multiply $num1 $num2
divide $num1 $num2
modulus $num1 $num2


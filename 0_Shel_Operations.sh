# Shell operations prime, fibonacci
#!/bin/bash

# ---------- Function: Palindrome Check ----------
check_palindrome() {
    temp=$num
    rev=0
    while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        rev=$((rev * 10 + digit))
        temp=$((temp / 10))
    done
    if [ $rev -eq $num ]; then
        echo "$num is a Palindrome."
    else
        echo "$num is NOT a Palindrome."
    fi
}

# ---------- Function: Prime Check ----------
check_prime() {
    is_prime=1
    if [ $num -le 1 ]; then
        is_prime=0
    else
        for ((i=2; i*i<=num; i++)); do
            if [ $((num % i)) -eq 0 ]; then
                is_prime=0
                break
            fi
        done
    fi
    if [ $is_prime -eq 1 ]; then
        echo "$num is a Prime number."
    else
        echo "$num is NOT a Prime number."
    fi
}

# ---------- Function: Fibonacci Series ----------
generate_fibonacci() {
    echo "Fibonacci series up to $num terms:"
    a=0
    b=1
    for ((i=0; i<num; i++)); do
        echo -n "$a "
        fn=$((a + b))
        a=$b
        b=$fn
    done
    echo
}

# ---------- Function: Armstrong Check ----------
check_armstrong() {
    sum=0
    temp=$num
    n=${#num}  # number of digits

    while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        power=$((digit ** n))
        sum=$((sum + power))
        temp=$((temp / 10))
    done

    if [ $sum -eq $num ]; then
        echo "$num is an Armstrong number."
    else
        echo "$num is NOT an Armstrong number."
    fi
}

# ----------- Main Script -----------
echo "Enter a number:"
read num

check_palindrome
check_prime
generate_fibonacci
check_armstrong

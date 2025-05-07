#Shell String Operations
#!/bin/bash

echo "Enter a string:"
read str

# Length of string
echo "Length: ${#str}"

# Reverse the string
rev_str=$(echo "$str" | rev)
echo "Reversed: $rev_str"

# Convert to uppercase
upper=$(echo "$str" | tr 'a-z' 'A-Z')
echo "Uppercase: $upper"

# Convert to lowercase
lower=$(echo "$str" | tr 'A-Z' 'a-z')
echo "Lowercase: $lower"

# Check if string is palindrome
if [ "$str" == "$rev_str" ]; then
    echo "The string is a palindrome."
else
    echo "The string is not a palindrome."
fi

# First 3 characters
sub=${str:0:3}
echo "First 3 characters: $sub"

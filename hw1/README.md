##CS104 - HW 1
##### by Matthew Fala
_________

# Homework 1 consists of several sections:

> 1) Quiz on CS104 policy
> 2) Quiz on Git
> 3) Review of Valgrind and dynamic memory
> 4) Bug fix practice
> 4) Application of memory management: Manager similar to the c++ stack driver
> 5) Application of memory management: Flexible character manager that allows for memory allocation and memory releases

_________


# Instructions:

## HW1Q5
##### Make sure hw1q5.txt is in working directory
```
# Compile
g++ -g -Wall -std=c++11 hw1q5.cpp -o hw1q5

# Run
./hw1q5 hw1q5.txt
```

## Palindrome
```
# Compile
$ g++ -g -Wall -std=c++11 palindrome.cpp -o palindrome

# Run
./palindrome <any word>
```

## First Memory Test
```
# Compile
$ g++ -g -Wall -std=c++11 flexCharManager.cpp simpleCharManager.cpp first_memtest.cpp -o first_memtest

# Run
$ ./first_memtest
```

## Second Memory Test
```
# Compile
Compile second_memtest.cpp
$ g++ -g -Wall -std=c++11 flexCharManager.cpp simpleCharManager.cpp second_memtest.cpp -o second_memtest

# Run
$ ./second_memtest
```


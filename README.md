# C Language Course - IJC

## Implementation of Eratosthenes Sieve and Message Decoder from PPM Image File
Evaluation: 15/15 points

## Assignment
[Assignment link](https://github.com/kezniklm/IJC_project1/blob/8e5b2fa101763383f9cbb40bb6bed6b9c7cd7715/IJC_%20DU1.pdf)

## Eratosthenes Sieve
The Eratosthenes Sieve algorithm is an ancient Greek method for finding all prime numbers up to a given limit. It works by iteratively marking the multiples of each prime number, starting from 2, as composite (not prime). The algorithm stops when the square of the current prime exceeds the given limit. The remaining unmarked numbers are prime.

### Features
* Prints last prime numbers up to a given limit using the Eratosthenes Sieve algorithm.
* Efficiently marks and filters out multiples of primes.

## Message Decoder from PPM Image File
The program utilizes the Eratosthenes Sieve algorithm to determine the selected bytes for encoding the message. Starting from the prime number 29, the program identifies prime numbers and assigns corresponding bytes for message embedding.

### Features
* Steganography technique using prime numbers for message encoding.
* Efficient utilization of LSBs in selected bytes representing color channels.
* Decoding terminates upon reaching the '\0' character.

## Compilation
To compile the program, use the following command:
```bash
$ make
```

## Usage - Eratosthenes Sieve
To run the program that is using MACROS:
```bash
$ ./primes
```
To run the program that is using inline functions:
```bash
$ ./primes-i
```

## Usage - Message Decoder from PPM Image File
```bash
$ ./steg-decode <image_file>
```

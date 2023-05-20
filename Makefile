#Makefile
#Riesenie IJC-DU1 - priklad A,B 
#Datum odovzdania: 22.3.2022
#Autor: Matej Keznikl
#Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
#Prelozene: GCC 7.5.0
#Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
#Popis: Makefile pre IJC projekt_1

CC = gcc

CFLAGS = -g -std=c11 -pedantic -Wall -Wextra 

LC_ALL = cs_CZ.utf8

CFLAGS += -O2 #zapnutie optimalizacii

all: primes primes-i steg-decode

bitset.o: bitset.c
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

bitset-i.o: bitset.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

eratosthenes.o: eratosthenes.c
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o 

error.o: error.h error.c 
	$(CC) $(CFLAGS) -c error.c -o error.o

ppm.o: ppm.h ppm.c
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o

primes-i.o: primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

steg-decode.o: steg-decode.c  
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o 

primes: bitset.o eratosthenes.o error.o primes.o
	$(CC) $(CFLAGS) bitset.o eratosthenes.o error.o primes.o -o primes -lm

primes-i: bitset-i.o eratosthenes-i.o error.o primes-i.o 
	$(CC) $(CFLAGS) bitset-i.o eratosthenes-i.o error.o primes-i.o -o primes-i -lm

steg-decode: bitset.o eratosthenes.o error.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) bitset.o eratosthenes.o error.o ppm.o steg-decode.o -o steg-decode -lm


run: primes primes-i steg-decode
	ulimit -s 40000 && ./primes
	ulimit -s 40000 && ./primes-i

zip:
	zip xkezni01.zip *.c *.h Makefile

.PHONY: run clean
clean:
	rm -f *.o 
	rm -f primes 
	rm -f primes-i 
	rm -f steg-decode
	
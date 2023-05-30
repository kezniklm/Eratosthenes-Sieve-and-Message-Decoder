// primes.h
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavičkový súbor pre modul primes.c, ktorý vypisuje prvocisla ulozene v bitovom poli

#include <stdio.h>
#include <time.h>

#include "eratosthenes.h"
#include "bitset.h"

#define N 300000000
#define PRIMES 10

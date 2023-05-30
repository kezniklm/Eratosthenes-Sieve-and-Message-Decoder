// primes.c
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul pre vypis prvocisel ulozenych v bitovom poli

#include "primes.h"

int main()
{
    // zaciatok pocitania casu
    clock_t start = clock();

    // vytvorenie bitoveho pola
    bitset_create(bitarray, N);

    // volanie funkcie Eratosthenes
    Eratosthenes(bitarray);

    // vytvorenie vynulovaneho pola pre prvocisla
    unsigned long primes[10] = {
        0,
    };
    int position = 0;

    for (unsigned long i = N; i > 0; i--)
    {
        // pokial najdeme v bitovom poli na indexe i bit s hodnotou 0, tak ukladame prvocisla
        if (!bitset_getbit(bitarray, i))
        {
            if (position != PRIMES)
            {
                // ukladanie prvocisel do pola primes
                primes[position++] = i;
            }
            // pokial mame pole naplnene, to znamena, ze mame prvocisla na indexoch 0-9, program vyskoci z cyklu
            else
                break;
        }
    }

    for (unsigned long i = 0; i < PRIMES; i++)
    {
        // vypisovanie prvocisel vzostupne - od najmensieho po najvacsie
        fprintf(stdout, "%lu\n", primes[position - i - 1]);
    }

    // vypis casu potrebneho na vypocet poslednych 10 prvocisel
    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
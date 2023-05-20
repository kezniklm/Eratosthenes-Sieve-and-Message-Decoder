// eratosthenes.c
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul obsahujuci funkciu void Eratosthenes(bitset_t bitarray)

#include <math.h>

#include "eratosthenes.h"

void Eratosthenes(bitset_t bitarray)
{
    bitset_setbit(bitarray, 1, 1);

    // nastavenie vsetkych parnych cisel na 1
    for (unsigned long i = 0; i <= bitset_size(bitarray); i += 2)
    {
        bitset_setbit(bitarray, i, 1);
    }

    // vyfiltrovanie prvocisel - nastavovanie nasobkov na 1, prvocisla maju hodnotu 0
    for (unsigned long i = 3; i < sqrt(bitset_size(bitarray)); i += 2)
    {
        if (bitset_getbit(bitarray, i) == 0)
        {
            for (unsigned long j = i * i; j <= bitset_size(bitarray); j += 2 * i)
            {
                bitset_setbit(bitarray, j, 1);
            }
        }
    }
}
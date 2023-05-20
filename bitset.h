// bitset.h
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavickovy subor pre strukturu bitoveho pola

#ifndef BITSET_H
#define BITSET_H

#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define NUMBER_OF_BITS (sizeof(unsigned long) * CHAR_BIT) // makro, ktoré vypočíta počet bitov dátoveho typu unsigned long
#define SIZE_RESERVED 1                                   // konstanta v hodnote 1 - reprezentuje bitarray_name[0]
#define LEFTOVER_RESERVED 1                               // konstanta v hodnote 1 - reprezentuje jeden bit naviac - v prípade delenia so zvyskom

// vytvori staticke/automatické/lokálne pole bitov,pričom uloží velkosť pola na prvý index pola bitov
#define bitset_create(bitarray_name, bitarray_size)                                                           \
    static_assert((bitarray_size > 0), "Pole nesmie mat hodnotu mensiu ako 0");                               \
    static_assert((bitarray_size < ULONG_MAX), "Velkost pola bitov nemoze byt vacsia ako maximalna hodnota"); \
    unsigned long bitarray_name[(bitarray_size) / NUMBER_OF_BITS + SIZE_RESERVED + LEFTOVER_RESERVED] = {     \
        0,                                                                                                    \
    };                                                                                                        \
    bitarray_name[0] = (bitarray_size)

// alokuje pole bitov(alokovaná pamäť musí byť po skončení používania uvoľnená), pričom uloží velkosť pola na prvý index pola bitov
#define bitset_alloc(bitarray_name, bitarray_size)                                                                                \
    assert((bitarray_size) <= ULONG_MAX);                                                                                         \
    assert((bitarray_size) > 0);                                                                                                  \
    bitset_t bitarray_name = calloc((bitarray_size) / NUMBER_OF_BITS + SIZE_RESERVED + LEFTOVER_RESERVED, sizeof(unsigned long)); \
    if (bitarray_name == NULL)                                                                                                    \
        error_exit("bitset_alloc: Nastala chyba pri alokacii pamati\n");                                                          \
    bitarray_name[0] = (bitarray_size)

// pokial nie je zadaný symbol USE_INLINE, tak sa definujú nasledujúce makrá
#ifndef USE_INLINE

// uvolnuje dynamicky alokovanu pamat pre pole bitov
#define bitset_free(bitarray_name) free(bitarray_name)

// vrátí deklarovanú velkost poľa v bitoch (uloženú v poli na prvom indexe)
#define bitset_size(bitarray_name) bitarray_name[0]

// nastaví bit na zadanom indexe na hodnotu zadanú výrazom - 0 alebo 1
#define bitset_setbit(bitarray_name, bitarray_index, bitarray_expression)                                                                               \
    do                                                                                                                                                  \
    {                                                                                                                                                   \
        if ((bitarray_index) > bitset_size(bitarray_name))                                                                                              \
            error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n", (unsigned long)bitarray_index, (unsigned long)(bitset_size(bitarray_name))); \
        if (bitarray_expression)                                                                                                                        \
            bitarray_name[(bitarray_index) / NUMBER_OF_BITS + SIZE_RESERVED] |= 1UL << ((bitarray_index) % NUMBER_OF_BITS);                             \
        else                                                                                                                                            \
            bitarray_name[(bitarray_index) / NUMBER_OF_BITS + SIZE_RESERVED] &= ~(1UL << ((bitarray_index) % NUMBER_OF_BITS));                          \
    } while (0)

// získa hodnotu bitu na zadanom indexe, vracia hodnotu 0 alebo 1
#define bitset_getbit(bitarray_name, bitarray_index) \
    (((bitarray_index) > bitset_size(bitarray_name)) ? (error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n", (unsigned long)bitarray_index, (unsigned long)(bitset_size(bitarray_name))), 0) : bitarray_name[(bitarray_index) / NUMBER_OF_BITS + SIZE_RESERVED] & (1UL << ((bitarray_index) % NUMBER_OF_BITS)))

#else  // pokial je zadaný symbol USE_INLINE, tak sa definujú nasledujúce INLINE funkcie

// uvolnuje dynamicky alokovanu pamat pre pole bitov
inline void bitset_free(const bitset_t bitarray_name)
{
    free(bitarray_name);
}

// vrátí deklarovanú velkost poľa v bitoch (uloženú v poli na prvom indexe)
inline unsigned long bitset_size(const bitset_t bitarray_name)
{
    return bitarray_name[0];
}

// nastaví bit na zadanom indexe na hodnotu zadanú výrazom - 0 alebo 1
inline void bitset_setbit(bitset_t bitarray_name, const bitset_index_t bitarray_index, const int bitarray_expression)
{
    if (bitarray_index > bitset_size(bitarray_name)) // kontrola na medze pola, v pripade chyby vola program funkciu error_exit
    {
        error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n", (unsigned long)bitarray_index, (unsigned long)(bitset_size(bitarray_name)));
    }
    if (bitarray_expression != 0)
    {
        bitarray_name[(bitarray_index) / NUMBER_OF_BITS + SIZE_RESERVED] |= (1UL << ((bitarray_index) % NUMBER_OF_BITS));
    }
    else
        bitarray_name[(bitarray_index) / NUMBER_OF_BITS + SIZE_RESERVED] &= ~(1UL << ((bitarray_index) % NUMBER_OF_BITS));
}

// získa hodnotu bitu na zadanom indexe, vracia hodnotu 0 alebo 1
inline unsigned long bitset_getbit(const bitset_t bitarray_name, const bitset_index_t bitarray_index)
{
    if (bitarray_index > bitset_size(bitarray_name)) // kontrola na medze pola, v pripade chyby vola program funkciu error_exit
    {
        error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n", (unsigned long)bitarray_index, (unsigned long)(bitset_size(bitarray_name)));
    }
    return bitarray_name[(bitarray_index) / NUMBER_OF_BITS + SIZE_RESERVED] & (1UL << ((bitarray_index) % NUMBER_OF_BITS));
}
#endif // koniec casti kodu s inline funkciami
#endif // koniec bitset.h
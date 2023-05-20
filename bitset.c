// bitset.c
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Externá deklarácia inline funkcií

#include "bitset.h"

#ifdef USE_INLINE

extern void bitset_free(const bitset_t bitarray_name);                                                                 // uvolnuje dynamicky alokovanu pamat pre pole bitov
extern unsigned long bitset_size(const bitset_t bitarray_name);                                                        // vrátí deklarovanú velkost poľa v bitoch (uloženú v poli na prvom indexe)
extern void bitset_setbit(bitset_t bitarray_name, const bitset_index_t bitarray_index, const int bitarray_expression); // nastaví bit na zadanom indexe na hodnotu zadanú výrazom - 0 alebo 1
extern unsigned long bitset_getbit(const bitset_t bitarray_name, const bitset_index_t bitarray_index);                 // získa hodnotu bitu na zadanom indexe, vracia hodnotu 0 alebo 1

#endif
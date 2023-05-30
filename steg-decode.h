// steg-decode.h
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavičkový súbor modul steg-decode.c pre dekódovanie ukrytej správy z obrázku formátu PPM

#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"
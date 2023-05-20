// steg-decode.c
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul pre dekódovanie ukrytej správy z obrázku formátu PPM

#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"

int main(int argc, char *argv[])
{
    // kontrola parametru argc - musi mat hodnotu 2(napriklad ./steg-decode du1-obrazek)
    if (argc != 2)
    {
        error_exit("steg-decode:Nezadali ste spravny pocet argumentov (2)\n");
    }

    // alokovanie ppm_image
    struct ppm *ppm_image = ppm_read(argv[1]);

    // pokial alokacia neprebeha spravne, program sa ukonci
    if (ppm_image == NULL)
    {
        error_exit("steg-decode:Alokacia ppm_image neprebehla uspesne\n");
    }

    unsigned long image_size = ppm_image->xsize * ppm_image->ysize * 3;

    bitset_alloc(ppm_decoder, image_size); // alokovanie pola bitov o velkosti image_size
    Eratosthenes(ppm_decoder);             // vypocitanie prvocisel v poli bitov - ppm_decoder

    int character = 0;
    unsigned long bit_shift = 0;
    char password[1000000] = {
        0,
    };
    int character_count = 0;

    // cyklus, ktory dekoduje skrytu spravu podla bitov urcenych prvocislami
    for (unsigned long i = 29; i < bitset_size(ppm_decoder); i++)
    {
        // pokial je bit 0 - nachadza sa na nom prvocislo
        if (!bitset_getbit(ppm_decoder, i))
        {
            // postupné doplnanie bitov do charu(sizeof(CHAR)= 1 bajt = 8 bitov) - mozno si odsledovat ak odkomentujete zakomentovanu funkciu printf, ale je nutne citat bity od zadu
            int value = 1 & ppm_image->data[i];
            character |= value << bit_shift++;

            // v pripade, ze sme uz doplnili 8 bitov, tak vypiseme znak
            if (bit_shift == CHAR_BIT)
            {
                // pokial narazime na koniec spravy, tak vyskocime z cyklu
                if (character == '\0')
                {
                    password[character_count++] = character;
                    bitset_free(ppm_decoder);
                    ppm_free(ppm_image);
                    break;
                }
                // pokial sme este nenarazili na koniec spravy, tak vypiseme znak
                else
                {
                    password[character_count++] = character;
                    bit_shift = 0;
                    character = 0;
                }
            }
        }
    }

    // Retazec musi byt ukonceny \0
    if (character != '\0')
    {
        bitset_free(ppm_decoder);
        ppm_free(ppm_image);
        error_exit("steg-decode: Retazec nebol ukonceny ukoncovacim znakom \\0\n");
    }
    else
    {
        int i = character_count;
        while (character_count)
        {
            if (password[i - character_count] != '\0')
            {
                putchar(password[i - character_count]);
            }
            character_count--;
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}

// ppm.c
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul pre manipuláciu s PPM formátom

#include "ppm.h"
#include "error.h"

#define PPM_MAX_IMAGE_SIZE 8000 * 8000 * 3
#define MAX_COLOR_VALUE 255

struct ppm *ppm_read(const char *filename)
{
    FILE *file_pointer;
    file_pointer = fopen(filename, "r");
    char file_format[3];
    unsigned int image_x_size, image_y_size, color_value;

    // kontrola, ci sa funkcii fopen podarilo subor otvorit
    if (file_pointer == NULL)
    {
        warning_msg("ppm_read: Subor %s nebolo mozne otvorit\n", filename);
        return NULL;
    }

    // kontrola parametrov formatu PPM
    int format_info = fscanf(file_pointer, "%s %u %u %u\n", file_format, &image_x_size, &image_y_size, &color_value);
    if (format_info != 4)
    {
        warning_msg("ppm_read: Subor %s nema spravne specifikovane parametre\n", filename);
        fclose(file_pointer);
        return NULL;
    }

    // kontrola ci je subor formatu P6
    if (strcmp("P6", file_format))
    {
        warning_msg("ppm_read: Subor %s nie je formatu P6\n", filename);
        fclose(file_pointer);
        return NULL;
    }

    // kontrola ci velkost obrazka nie je vacsia ako maximalna mozna
    if ((image_x_size * image_y_size * 3) > PPM_MAX_IMAGE_SIZE)
    {
        warning_msg("ppm_read: Subor %s ma vacsiu velkost ako je maximalna povolena\n", filename);
        fclose(file_pointer);
        return NULL;
    }

    // kontrola ci farby v obrazku su v rozsahu 0 - 255
    if (color_value > MAX_COLOR_VALUE)
    {
        warning_msg("ppm_read: Farby v subore %s nie su v rozsahu 0-255\n", filename);
        fclose(file_pointer);
        return NULL;
    }

    // alokovanie miesta v pamati pre obrazok formatu ppm
    struct ppm *ppm_image = calloc(1, sizeof(struct ppm) + (3 * image_x_size * image_y_size));
    if (ppm_image == NULL)
    {
        warning_msg("ppm_read: Struktura o velkosti %lu nebola alokovaná\n", (3 * image_x_size * image_y_size));
        fclose(file_pointer);
        return NULL;
    }

    // nahranie Xovej suradnice do ppm_image->xsize
    ppm_image->xsize = image_x_size;

    // nahranie Yovej suradnice do ppm_image->ysize
    ppm_image->ysize = image_y_size;

    int c;
    long i = 0;

    // nahranie obsahu suboru do ppm_image->data[]
    while ((c = getc(file_pointer)) != EOF && i < 3 * ppm_image->xsize * ppm_image->ysize)
    {
        ppm_image->data[i++] = c;
    }

    fclose(file_pointer);

    return ppm_image;
}

// uvolnenie dynamicky alokovanej pamati v ppm_read
void ppm_free(struct ppm *p)
{
    free(p);
}
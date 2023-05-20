// error.c
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul obsahujuci funkcie void warning_msg(const char *fmt, ...) a void error_exit(const char *fmt, ...)

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "error.h"

void warning_msg(const char *fmt, ...)
{
    va_list arguments;

    va_start(arguments, fmt);
    fprintf(stderr, "CHYBA:\n");
    vfprintf(stderr, fmt, arguments);
    va_end(arguments);
}
void error_exit(const char *fmt, ...)
{
    va_list arguments;

    va_start(arguments, fmt);
    fprintf(stderr, "CHYBA:\n");
    vfprintf(stderr, fmt, arguments);
    va_end(arguments);
    exit(EXIT_FAILURE);
}
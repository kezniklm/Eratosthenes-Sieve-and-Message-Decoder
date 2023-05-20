// error.h
// Riesenie IJC-DU1 - priklad A,B
// Datum odovzdania: 22.3.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavickovy subor obsahujuci prototypy funkcíí z error.c

#ifndef ERROR_H
#define ERROR_H

// funkcia vypise text "CHYBA:..."
void warning_msg(const char *fmt, ...);

// funkcia vypise text "CHYBA:..." a ukonci program s chybovou hlaskou 1
void error_exit(const char *fmt, ...);

#endif
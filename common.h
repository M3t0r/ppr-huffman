/**
 * @file
 * Dieser Header definiert allgemeine Typen und haeufig verwendete
 * Makros fuer das Projekt.
 * 
 * File:   common.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 2. Februar 2012, 15:24
 */
#ifndef _COMMON_H
#define _COMMON_H

/*****************************************************************************
 * Typdefinitionen
 *****************************************************************************/
/**
 * Definiert den Typ BOOL, um Wahrheitswerte zu speichern.
 */
typedef enum {
    FALSE,
    TRUE
} BOOL;

/**
 * Definiert einen Typ BYTE.
 */
typedef unsigned char BYTE;


/*****************************************************************************
 * Makros
 *****************************************************************************/
/**
 * Definiert das Makro ASSERT_ALLOC um zu pruefen, ob die Anfoerderung eines
 * Speicherbereichs erfoglreich war.
 */
#ifndef ASSERT_ALLOC
    #include <stdlib.h>
    #include <stdio.h>
    #define ASSERT_ALLOC(ptr)\
       if (ptr == NULL) {\
           printf("Could not allocate memory block in %s:%i\nAborting\n", __FILE__, __LINE__);\
           exit(EXIT_FAILURE);\
       }
#endif

/**
 * Definiert ein Makro zur Debugausgabe.
 */
#ifdef DEBUG
    #define DPRINT(E)		printf(E)
    #define DPRINT_E(E, T)	printf(#E " = %" #T "\n", E)
#else
    #define DPRINT(E)
    #define DPRINT_E(E, T)
#endif

#endif

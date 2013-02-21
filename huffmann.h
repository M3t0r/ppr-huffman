/**
 * @file
 * Dieses Modul komprimiert und dekomprimiert Dateien mit dem Huffmann-
 * Algorithmus.
 * 
 * File:   huffmann.h
 * Author: Simon Lutz Brüggen, Jan-Hendrik Frintrop, Tim Ziegler
 *
 * Created on 11. Februar 2013, 15:27
 */

#ifndef HUFFMANN_H
#define	HUFFMANN_H


/*****************************************************************************
 * Funktionsprototypen
 *****************************************************************************/
/**
 * Komprimiert eine Datei mit Hilfe des Huffmann-Algorithmus.
 * @param in_filename Name der zu komprimierenden Datei.
 * @param out_filename Name der zu erzeugenden Ausgabedatei. Falls diese bereits
 *                     existiert, so wird sie ueberschrieben. 
 */
void compress(char *in_filename, char *out_filename);

/**
 * Dekomprimiert eine Datei wieder.
 * @param in_filename Name der zu dekomprimierenden Datei.
 * @param out_filename Name der dekomprimierten Datei. Falls diese bereits 
 *                     existiert, so wird sie ueberschrieben.
 */
void decompress(char *in_filename, char *out_filename);


#endif	/* HUFFMANN_H */


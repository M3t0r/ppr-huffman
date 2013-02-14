/**
 * @file
 * 
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
 * 
 * @param in_filename
 * @param out_filename
 */
void compress(char *in_filename, char *out_filename);

/**
 * 
 * @param in_filename
 * @param out_filename
 */
void decompress(char *in_filename, char *out_filename);



#endif	/* HUFFMANN_H */


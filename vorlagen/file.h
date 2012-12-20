/* 
 * File:   file.h
 * Author: simon
 *
 * Created on 22. November 2012, 19:38
 */

#ifndef FILE_H
#define	FILE_H

#include <stdio.h>

/**
 * reads one line from input.
 * @param pass-by-reference pointer to the line.
 * @return size of the allocated memory for line.
 */
int readline(char **line, FILE *src);

/**
 * Removes the trailing newline from str if it has one.
 * @param str the string tha may or may not have a trailing \n.
 */
void remove_trailing_newline(char *str);

#endif	/* FILE_H */


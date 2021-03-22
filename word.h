/* [mmn 14 : word.h]:
in this file: The defenition of a word - a memory cell sized 12 bits. 

author: Uri K.H,   Lihi Haim       Date  : 21.3.2021 
ID: 215105321,     313544165       Tutor: Danny Calfon */
#ifndef WORD_H
#define WORD_H
#include <math.h>
#define MIN_WORD_VAL (int)(-pow(2, 11))
#define MAX_WORD_VAL (int)(pow(2, 11) - 1)

/* word: the structure of every memory cell in the program*/
typedef struct{
     int wrd:12;
     char ARE;
} word;
#endif
/* [mmn 14 : ]:
in this file: 

author: Uri K.H,   Lihi Haim       Date: 21.3.2021 
ID: 215105321,     313544165       Tutor: Danny Calfon */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "word.h"
#include "label.h"
#include "privateDataFuncs.h"

#define MAX_DEC_LEN 5

static int DC;
static word *dataImage[1];

static word *scanDataParams(char *, int *, char *, int);

/* pushData(): the function get as parameters the current line we're reading,
the pointer to the current character, the line's length and the type of the current word.
and pushes the relevent words to memory image */
boolean pushData(char *line, int *lInd, char *type, int lineCnt){
    boolean error = FALSE;

    jumpSpaces(line, lInd);
    while(line[*lInd] != '\0'){
        if(DC == 0) /* pushing the data to the data image */ 
            *dataImage = calloc(1, sizeof(word));
        else
            *dataImage = realloc(*dataImage, DC * sizeof(word));
        if(!isAlloc(*dataImage))
            return ERROR;
        if(!(dataImage[DC] = scanDataParams(line, lInd, type, lineCnt))) /* scanning data from the line */
            error = TRUE;
        DC++;
        if(!isThereComma(line, lInd, lineCnt))
            return FALSE;
        if(error == TRUE)
            continue;
    }
    return TRUE;
    /*int size = 1, i = 0, j;
    word *params = calloc(size, sizeof(word));
    boolean error = FALSE;

    if(!isAlloc(params))
        return ERROR;

    while(line[*lInd] != '\0'){
        word *scaned;
        params = realloc(params, (++size) * sizeof(paramType));

        if(!isAlloc(params))
            return ERROR; 
        if(!isThereComma(line, lInd, lineCnt))
            return FALSE;
        if(!(scaned = scanDataParams(line, lInd)))  scanning data from the line 
            error = TRUE;
        if(error == TRUE)
            continue;

        j = 0;
        while(scaned[j] != NULL){
            if(DC == OS_MEM) pushing the data to the data image *
                dataImage = calloc(1, sizeof(word));
            else
                dataImage = realloc(dataImage, (DC - OS_MEM) * sizeof(word));
            if(!isAlloc(params))
                return ERROR;
            dataImage[DC - OS_MEM] = newData;
            DC++;
            j++;
        }
    }
    return TRUE;*/
}

/* pushData(): the function get as parameters the current line we're reading,
the pointer to the current word, the line's length and the type of the current word.
and reads the parameters from the line and returns an array of words with the parameters*/

static word *scanDataParams(char *line, int *lInd, char *type, int lineCnt){
     int size = 1, i = 1, decimal;
     char curr, currentWrd[MAX_DEC_LEN + 1];
     word *dataForPush = calloc(size, sizeof(word));
     
     if(!isAlloc(dataForPush)){
          free(dataForPush);
          return NULL;
     }
     jumpSpaces(line, lInd);

     /*There must be parameters after .data or .stirng in Directive*/
     if (line[*lInd] == '\0'){
          printf("error [line %d]: There must be parameters after the directives \".data\" or \".stirng\"\n", lineCnt);
          free(dataForPush);
          return NULL;
     }
     /*if it's a string case:*/
     if (strcmp(type, "string")){
          if(line[*lInd] != '"'){
               printf("error [line %d]: the operand of the directive \".string\" must start with a \"\n", lineCnt);
               free(dataForPush);
               return NULL;
          }
          (*lInd)++; /* the beginning of the string */
          size = 2;
          while((curr = line[*lInd]) != '\0' || curr != '"'){
               if (curr == '\\' && line[*lInd+1] == '\"'){
                    dataForPush = realloc(dataForPush, ++size * sizeof(word));
                    if(!isAlloc(dataForPush))
                         return NULL;
                    dataForPush[size - 3].wrd = '\"';
                    (*lInd) += 2;
                    continue;
               }
               dataForPush = realloc(dataForPush, ++size * sizeof(word));
               if(!isAlloc(dataForPush))
                    return NULL;
               dataForPush[size - 3].wrd = curr;
               dataForPush[size - 3].ARE = 'A';
               (*lInd)++;
          }
          if (curr == '\0'){ /* string ended unaturaly at the end of the array and not by: " */
               printf("error [line %d]: There must be \" at the end of a string\n", lineCnt);
               free(dataForPush);
               return NULL;
          }
          (*lInd)++;
          if(!isBlank(line, *lInd)){
               free(dataForPush);
               return NULL;
          }
          dataForPush[size-2].wrd = '\0';
          dataForPush[size-2].ARE = 'A';
          dataForPush[size-1].ARE = '\0';
          return dataForPush;
     }

     if(!strcmp(type, "data")){
          free(dataForPush);
          return NULL;
     }
     while ((curr = line[*lInd]) != '\0'){
          if(curr != '#'){
               printf("error [line %d]: the operand of the directive \".data\" must start with a \'#\'\n", lineCnt);
               free(dataForPush);
               return NULL;
          }
          (*lInd)++;
          if(((curr = line[*lInd]) == '+' || curr == '-') && isdigit(curr))
               currentWrd[i] = curr;
          else{
               printf("error [line %d]: the decimal number of \".data\" operand must start with a sign (+/-) or a digit\n", lineCnt);
               free(dataForPush);
               return NULL;
          }
          (*lInd)++;
          for(i = 2; i < MAX_DEC_LEN && !isdigit((curr = line[*lInd])) && !isspace(curr); i++, (*lInd)++)
               currentWrd[i] = curr;
          if(!isdigit(curr) && !isspace(curr) && curr != '\0'){
               printf("error [line %d]: the decimal number of the \".data\" directive operand must include only digits (and optional sign in the start +/-)\n", lineCnt);
               free(dataForPush);
               return NULL;
          }
          currentWrd[i] = '\0';
          if(isdigit(line[*lInd + 1]) || (decimal = atoi(currentWrd)) < MIN_WORD_VAL || decimal > MAX_WORD_VAL){ 
               printf("error [line %d]: the decimal number of the \".data\" directive operand is too %s\n", lineCnt, (decimal > MAX_WORD_VAL || isdigit(line[*lInd + 1])? "big" : "small"));
               free(dataForPush);
               return NULL;
          }
          dataForPush = realloc(dataForPush, ++size * sizeof(word));
          if(!isAlloc(dataForPush))
               return NULL;
          dataForPush[size-2].wrd = decimal;
          dataForPush[size-2].ARE = 'A';

          if (!isThereComma(line, lInd, lineCnt)){
               free(dataForPush);
               return NULL;
          }
     }
     dataForPush[size-1].ARE = '\0';
     return dataForPush;
}

/* cleanDC(): the function get as a parameter the boolean flag that indicates
 whether to free all DATA from datacounter and if it's TRUE releases all DATA
 and sets DC counter to ZERO*/

void cleanDC(boolean terminate){
     int i = 0;
    while(1){
        if(i < DC)
            free(dataImage[i]);
        i++;
    }
    DC = 0;
    if(terminate){
        free(dataImage);
        return;
    }
    *dataImage = NULL;
    return;
}

/* getDC(): the fuction fetches the value of the DATA counter*/

int getDC(){
    return DC;
}

/* pushDataToFile(): the function get as a parameter the file we want to write to
and writes everything from DATA's  array*/

void pushDataToFile(FILE *fd){
    int i;
    for(i = 0; i < DC; i++)
        fprintf(fd, "%04d %x %c\n", getIC()+i+1, (*dataImage)[i].wrd, (*dataImage)[i].ARE);
    return;
}


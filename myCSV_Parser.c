/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#include "myCSV_Parser.h"


/**
* Read in char pointer to a line of a csv file
* and integer lineIndex which is the index in line 
* for the function start to split.
* returns char pointer to the first item from lineIndex
*
*/
char *splitOneToken(char *line, int * lineIndex){
    int isInsideQuote = (line[*lineIndex]==CHAR_QUOTE), destIndex = 0;
    char * dest = (char*)malloc((MAX_LINE_LEN) * sizeof(char));
    
    for (int i=*lineIndex + isInsideQuote;i<strlen(line);i++){
    
        // If inside a quoted string, just keep storing the char 
        // until meets the end of the line
        if(isInsideQuote){
            if (
                (line[i]!=CHAR_QUOTE || line[i+1]!=CHAR_SEPERATOR) && 
                !(line[i+1]==CHAR_NEWLINE || line[i+1]==CHAR_NULLCHAR)
                ){
                
                // If not at the beginning of the line and previous char 
                // and current char are both quote, then not store it
                if(
                    (destIndex>=1 && 
                    (dest[destIndex-1]!=CHAR_QUOTE || line[i]!=CHAR_QUOTE))
                    ||(destIndex==0)
                ){
                    dest[destIndex++] = line[i];
                }
            // At the end of a quoted string, return the token
            }else{
                dest[destIndex] = CHAR_NULLCHAR;
                *lineIndex = i + 2;
                return dest;
            }
        }else{
            // Not inside quote and then check if it is at the begin or end
            if (
                line[i]!=CHAR_SEPERATOR && 
                !(line[i+1]==CHAR_NEWLINE || line[i+1]==CHAR_NULLCHAR)
            ){
                if(
                    (destIndex>=1 && 
                    (dest[destIndex-1]!=CHAR_QUOTE || line[i]!=CHAR_QUOTE))
                    ||(destIndex==0)
                ){
                    dest[destIndex++] = line[i];
                }
            // Reach the end of a quoted string, return the token
            }else{
                dest[destIndex] = CHAR_NULLCHAR;
                *lineIndex = i + 1;
                return dest;
            }
        }
    }
    printf("ERROR! lineIndex outside the line!");
    return NULL;
}
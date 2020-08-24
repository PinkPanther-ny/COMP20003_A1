/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#include "myCLUE.h"
#include "myLinkedList.h"
#include "myCSV_Parser.h"

int
main(int argc, char *argv[]) {
    assert(argc==3);
    char *dataFile = argv[1], *outputFile = argv[2];
    
    List_t * list = creatLinkedList();
    readFileToList(list, dataFile);
    
    /* Clear file content if not empty */
    FILE * fp;
    fp = fopen(outputFile, "w");
    fp=freopen(NULL,"w",fp);
    assert(fp!=NULL);
    
    int foundNum;
    char keyWord[MAX_FIELD_LEN];
    List_t * result;
    
    char log[MAX_LOG_LEN];
    printf("\nEnter Trading Name to search(^D return results):\n");
    /* Read a line because keyword could contains space */
    while(scanf("%[^\n]%*c", keyWord)!=EOF){
    
        result = creatLinkedList();
        foundNum = linearSearch(keyWord, list, result);
        if(!foundNum){
            putClueInfo(NULL, fp, keyWord);
            
            memset(log, 0, sizeof(log));
            strcat(log, NOT_FOUND);
            printf("%28s\t%s\n",log, keyWord);
        }else{
            putLinkedList(result, fp);
            
            char tmp[5];
            sprintf(tmp, "%d", foundNum);
            memset(log, 0, sizeof(log));
            strcat(log, FOUND1);
            strcat(log, tmp);
            strcat(log, FOUND2);
            printf("%28s\t%s\n", log, keyWord);
        }
        freeLinkedList(result);
    }
    fclose(fp);
    
    /* Free the linked list that stores whole data */
    freeLinkedList(list);
    printf("\n\n");
    
    return 0;
}


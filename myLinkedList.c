/** ***********************
* Program written by Alvin Chen (nuoyanc@student.unimelb.edu.au) 8/21/2020
* 2020s2 UNIMELB COMP20003 assignment 1
*/

#include "myLinkedList.h"

/* Constructor for Node_t */
void 
Node(Node_t *this, Clue_t *data, Node_t *next){
    
    assert(this != NULL);
    this -> data = data;
    this -> next = next;
}


List_t *
creatLinkedList(){
    List_t * list = (List_t *)malloc(sizeof(List_t));
    assert(list != NULL);
    list -> head = NULL;
    list -> foot = NULL;
    return list;
}

void
freeLinkedList(List_t *list) {
    assert(list!=NULL);
    Node_t *cur, *pre;
    
    cur = list->head;
    while (cur) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
    free(list);
    
}

void 
putLinkedList(List_t *src, FILE * fp){
    Node_t * ptr = src->head;
    while(ptr != NULL){
        putClueInfo(ptr->data, fp, NULL);
        ptr = ptr->next;
        
    }
}



/* Push an CLUE item to the head of the list */
List_t *
push(List_t *list, Clue_t *data){
    Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));
    assert(newNode != NULL);
    
    // The first item
    if(list->head == NULL){
        Node(newNode, data, NULL);
        list -> foot = newNode;
    }else{
        Node(newNode, data, list -> head);
    }
    
    list -> head = newNode;
    return list;
    
}


void 
readFileToList(List_t *dest, char *filename){
    int lineCount = 0;
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);
    char fields[FIELD_NUM][MAX_FIELD_LEN];
    
    char *line = (char*)malloc((MAX_LINE_LEN) * sizeof(char));
    // Remove header line of CSV
    fgets(line, MAX_LINE_LEN, fp);
    int lineIndex;
    printf("\n----------Start readCSV-------------\n");
    // Iterate over each lines of the csv file
    while(fgets(line, MAX_LINE_LEN, fp)!=NULL){
        lineCount++;
        lineIndex=0;
        
        for(int i=0;i<FIELD_NUM;i++){
            strcpy(fields[i], splitOneToken(line, &lineIndex));
        }
        push(dest, storeFields(fields));
    }
    fclose(fp);
    printf("There are %d lines.\n", lineCount);
    printf("\n-----------END readCSV--------------\n");
}

int 
linearSearch(char *keyWord, List_t *src, List_t *result){
    int found = 0;
    Node_t * ptr = src->head;
    while(ptr != NULL){
        if (strcmp(ptr->data->tradingName, keyWord)==0){
            push(result, ptr->data);
            found++;
        }
        ptr = ptr->next;
    }
    return found;
    
}

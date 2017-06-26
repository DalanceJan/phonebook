#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "phonebook_opt.h"

HASH_ENTRY HASH_TABLE[FIRST_LAYER_HASH_SIZE];
bool bInitHash = false;
/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    return FIND_FROM_HASH_TABLE(lastname);
}

entry *append(char lastName[], entry *e)
{
    if(!bInitHash){
        bInitHash = true;
        INIT_HASH_TABLE();
    }
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    UPDATE_HASH_TABLE(e);

    return e;
}

int HASH_FUNCTION_TO_INT(char* str)
{
    unsigned sum =0;

    for(int i=0;;i++){
        char curr = str[i];
        if(curr =='\0')
            break;
        sum += (curr -'a') * i;
    }
    return sum & 0xFF;
}


int HASH_FUNCTION_FROM_STR_TO_INT(char* str)
{
    unsigned sum =0;

    for(int i=0;;i++){
        char curr = str[i];
        if(i==2 || curr =='\0')
            break;
        sum = sum * 26 + curr - 'a';

    }

    return sum & 0x3FF;
}

int find_next_avilable_before(int nLast)
{
    for(int i=0;i< nLast;i++)
        if(HASH_TABLE[i].refCount < HASH_LIMIT )
            return i;
    return nLast;
}

int GET_HASH_REF_TO(nFirstLayer){
    return HASH_TABLE[nFirstLayer].ref_to;
}

void SET_HASH_REF_TO(int nIdx){
    HASH_TABLE[nIdx].ref_to  = find_next_avilable_before(nIdx);
}

entry* FIND_FROM_HASH_TABLE(char *str)
{
    int nFirstLayer = HASH_FUNCTION_FROM_STR_TO_INT(str);
    HASH_ENTRY FindEntry= HASH_TABLE[nFirstLayer];
    struct __HASH_ENTRY *pNext = FindEntry.pNext;
    while(pNext != NULL)
    {
        // printf("yeah null1 L:(\n");
        if (strcmp(pNext->Name, str) == 0)
        {
            // printf("find that\n!!");
            return pNext->pAddr;
        }
        pNext = pNext->pNext;
    }
    int nRef_to = HASH_TABLE[nFirstLayer].ref_to;
    pNext = HASH_TABLE[nRef_to].pNext;

    while(pNext != NULL)
    {
        // printf("yeah null2 L:(\n");
        if (strcmp(pNext->Name, str) == 0)
            return pNext->pAddr;
        pNext = pNext->pNext;
    }
    // printf("yeah null L:(\n");
    entry* p  = NULL;
    return p;
}

void UPDATE_HASH_TABLE(entry* pEntry)
{
    int nFirstLayer = HASH_FUNCTION_FROM_STR_TO_INT(pEntry->lastName);

    if(HASH_TABLE[nFirstLayer].pNext ==NULL){
        HASH_TABLE[nFirstLayer].pNext = (HASH_ENTRY *) malloc(sizeof(HASH_ENTRY));
        HASH_ENTRY* new_entry = HASH_TABLE[nFirstLayer].pNext;

        new_entry->pNext = NULL;
        strcpy(new_entry->Name, pEntry->lastName);
        HASH_TABLE[nFirstLayer].refCount++;
        new_entry->pAddr = pEntry;
    }
    else{
        int nTargetLayer = nFirstLayer;
        if(HASH_TABLE[nFirstLayer].refCount > HASH_LIMIT){
            if(HASH_TABLE[nFirstLayer].ref_to == -1){
                SET_HASH_REF_TO(nFirstLayer);
            }
            nTargetLayer = GET_HASH_REF_TO(nFirstLayer);
        }
        HASH_ENTRY *new_entry = (HASH_ENTRY *) malloc(sizeof(HASH_ENTRY));
        new_entry->pNext = HASH_TABLE[nTargetLayer].pNext;
        strcpy(new_entry->Name, pEntry->lastName);
        HASH_TABLE[nTargetLayer].pNext = new_entry;
        HASH_TABLE[nTargetLayer].refCount++;
        new_entry->pAddr = pEntry;
    }
}



void show_hash_table()
{
    int nDif = 0;
    int zero_count = 0;
    int more_count = 0;
    for(int i=0;i<FIRST_LAYER_HASH_SIZE;i++){
        // printf(":%d \n", HASH_TABLE[i].refCount);
        int thisDif = HASH_AVG - HASH_TABLE[i].refCount;
        if (HASH_TABLE[i].refCount == 0)
            zero_count++;
        if (HASH_TABLE[i].refCount > HASH_LIMIT)
            more_count++;
        if (thisDif > 0)
            nDif += thisDif;
        else
            nDif -= thisDif;
    }
    float f = nDif / 4095;
    // printf("ndif:%d %f \n", nDif, f);
    // printf("zero count;%d \n", zero_count);
    // printf("more count;%d \n", more_count);
}

void INIT_HASH_TABLE()
{
    memset(&HASH_TABLE, 0, FIRST_LAYER_HASH_SIZE * sizeof(HASH_ENTRY));
    for(int i=0;i<FIRST_LAYER_HASH_SIZE;i++){
        HASH_TABLE[i].ref_to = -1;
    }
}
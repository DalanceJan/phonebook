// #include <stdlib.h>
// #include <stdio.h>
// #include <memory.h>
// #include "hash_game.h"
// #define FIRST_LAYER_HASH_SIZE 676
// #define LINE_COUNT 349900
// #define HASH_AVG 85
// #define DICT_FILE "./dictionary/words.txt"
// #define MAX_LAST_NAME_SIZE 16
// #define HASH_LIMIT 128

// HASH_ENTRY HASH_TABLE[FIRST_LAYER_HASH_SIZE];

// int HASH_FUNCTION_TO_INT(char* str)
// {
// 	unsigned sum =0;

// 	for(int i=0;;i++){
// 		char curr = str[i];
// 		if(curr =='\0')
// 			break;
// 		sum += (curr -'a') * i;
// 	}
// 	return sum & 0xFF;
// }


// int HASH_FUNCTION_FROM_STR_TO_INT(char* str)
// {
// 	unsigned sum =0;

// 	for(int i=0;;i++){
// 		char curr = str[i];
// 		if(i==2 || curr =='\0')
// 			break;
// 		sum = sum * 26 + curr - 'a';

// 	}

// 	return sum & 0x3FF;
// }

// int find_next_avilable_before(int nLast)
// {
// 	for(int i=0;i< nLast;i++)
// 		if(HASH_TABLE[i].refCount < HASH_LIMIT )
// 			return i;
// 	return nLast;
// }

// void UPDATE_HASH_TABLE(char *str)
// {
// 	int nFirstLayer = HASH_FUNCTION_FROM_STR_TO_INT(str);

// 	if(HASH_TABLE[nFirstLayer].pNext ==NULL){
// 		HASH_TABLE[nFirstLayer].pNext = (HASH_ENTRY *) malloc(sizeof(HASH_ENTRY));
// 		HASH_TABLE[nFirstLayer].refCount++;
// 		HASH_TABLE[nFirstLayer].pNext->pNext = NULL;
// 	}

// 	else{
// 		int nTargetLayer = nFirstLayer;
// 		if(HASH_TABLE[nFirstLayer].refCount > HASH_LIMIT){

// 			if(HASH_TABLE[nFirstLayer].ref_to == -1){
// 				printf("%d update from %d ", nFirstLayer, HASH_TABLE[nFirstLayer].ref_to);
// 				HASH_TABLE[nFirstLayer].ref_to = find_next_avilable_before(nFirstLayer);
// 				printf("to %d %s \n", HASH_TABLE[nFirstLayer].ref_to, str);
// 			}

// 			nTargetLayer = HASH_TABLE[nFirstLayer].ref_to;

// 			HASH_ENTRY *new_node = (HASH_ENTRY *) malloc(sizeof(HASH_ENTRY));
// 			new_node->pNext = HASH_TABLE[nTargetLayer].pNext;
// 			HASH_TABLE[nTargetLayer].pNext = new_node;
// 			HASH_TABLE[nTargetLayer].refCount++;
// 		}
// 		else{

// 			HASH_ENTRY *new_node = (HASH_ENTRY *) malloc(sizeof(HASH_ENTRY));
// 			new_node->pNext = HASH_TABLE[nTargetLayer].pNext;
// 			HASH_TABLE[nTargetLayer].pNext = new_node;
// 			HASH_TABLE[nTargetLayer].refCount++;
// 		}
// 	}
// }


// void show_hash_table()
// {
// 	int nDif = 0;
// 	int zero_count = 0;
// 	int more_count = 0;
// 	for(int i=0;i<FIRST_LAYER_HASH_SIZE;i++){
// 		// printf(":%d \n", HASH_TABLE[i].refCount);
// 		int thisDif = HASH_AVG - HASH_TABLE[i].refCount;
// 		if (HASH_TABLE[i].refCount == 0)
// 			zero_count++;
// 		if (HASH_TABLE[i].refCount > HASH_LIMIT)
// 			more_count++;
// 		if (thisDif > 0)
// 			nDif += thisDif;
// 		else
// 			nDif -= thisDif;
// 	}
// 	float f = nDif / 4095;
// 	printf("ndif:%d %f \n", nDif, f);
// 	printf("zero count;%d \n", zero_count);
// 	printf("more count;%d \n", more_count);
// }

// void INIT_HASH_TABLE()
// {
// 	memset(&HASH_TABLE, 0, FIRST_LAYER_HASH_SIZE * sizeof(HASH_ENTRY));
// 	for(int i=0;i<FIRST_LAYER_HASH_SIZE;i++){
// 		HASH_TABLE[i].ref_to = -1;
// 	}
// }

// void test(char* str)
// {
// 	unsigned nhash_word = HASH_FUNCTION_FROM_STR_TO_INT(str);
// 	unsigned nhash = HASH_FUNCTION_TO_INT(str);
// 	printf("str:%s hash:%d word:%d\n", str, nhash, nhash_word);
// }


// void test_ht(char* str)
// {
// 	unsigned nhash_word = HASH_FUNCTION_FROM_STR_TO_INT(str);
// 	unsigned nhash = HASH_FUNCTION_TO_INT(str);
// 	printf("str:%s hash:%d word:%d\n", str, nhash, nhash_word);
// }

// void foo()
// {
// 	FILE *fp;
//     int i = 0;
//     char line[MAX_LAST_NAME_SIZE];
//     struct timespec start, end;
//     double cpu_time1, cpu_time2;

//     /* check file opening */
//     fp = fopen(DICT_FILE, "r");
//     if (fp == NULL) {
//         printf("cannot open the file\n");
//         return ;
//     }

//     while (fgets(line, sizeof(line), fp)) {
//         while (line[i] != '\0')
//             i++;
//         line[i - 1] = '\0';
//         i = 0;
//         UPDATE_HASH_TABLE(line);
//     }
// }

// int main(){
// 	INIT_HASH_TABLE();
// 	foo();
// 	show_hash_table();
// 	return 0;
// }

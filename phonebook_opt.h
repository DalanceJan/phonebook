#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

#define FIRST_LAYER_HASH_SIZE 676
#define LINE_COUNT 349900
#define HASH_AVG 85
#define DICT_FILE "./dictionary/words.txt"
#define MAX_LAST_NAME_SIZE 16
#define HASH_LIMIT 128


/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
// #define OPT 1
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);


typedef struct __HASH_ENTRY {
    char Name[MAX_LAST_NAME_SIZE];
    unsigned short refCount;
    short ref_to;
    struct __HASH_ENTRY *pNext;
    struct __HASH_ENTRY *pAddr;
} HASH_ENTRY;



int HASH_FUNCTION_TO_INT(char* str);
int HASH_FUNCTION_FROM_STR_TO_INT(char* str);
int find_next_avilable_before(int nLast);
void UPDATE_HASH_TABLE(char *str);
void show_hash_table();
void INIT_HASH_TABLE();



// void test(char* str)
// {
//     unsigned nhash_word = HASH_FUNCTION_FROM_STR_TO_INT(str);
//     unsigned nhash = HASH_FUNCTION_TO_INT(str);
//     printf("str:%s hash:%d word:%d\n", str, nhash, nhash_word);
// }


// void test_ht(char* str)
// {
//     unsigned nhash_word = HASH_FUNCTION_FROM_STR_TO_INT(str);
//     unsigned nhash = HASH_FUNCTION_TO_INT(str);
//     printf("str:%s hash:%d word:%d\n", str, nhash, nhash_word);
// }

// void foo()
// {
//     FILE *fp;
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

#endif

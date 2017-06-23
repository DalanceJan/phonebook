#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
typedef struct __HASH_ENTRY {
    char Name[16];
	unsigned short refCount;
	 short ref_to;
    struct __HASH_ENTRY *pNext;
    struct __HASH_ENTRY *pAddr;
} HASH_ENTRY;
#endif

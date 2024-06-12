#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "contact.h"

#define ALPHABET_SIZE 26

typedef struct HashTable {
    Contact* table[ALPHABET_SIZE];
} HashTable;

void initializeHashTable(HashTable* hashTable);
int getHashIndex(const char* name);
void addContact(HashTable* hashTable, const char* name, const char* phone);
int searchContacts(HashTable* hashTable, const char* name);
void removeContact(HashTable* hashTable, const char* name);
void editContact(HashTable* hashTable, const char* name);
void displayContacts(HashTable* hashTable);
void freeContacts(HashTable* hashTable);

#endif // HASH_TABLE_H

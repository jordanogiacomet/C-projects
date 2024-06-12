#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "hash_table.h"

#define FILENAME "contacts.txt"

void loadContacts(HashTable* hashTable, const char* filename);
void saveContacts(HashTable* hashTable, const char* filename);
void backupContacts(HashTable* hashTable, const char* backupFilename);
void restoreContacts(HashTable* hashTable, const char* backupFilename);

#endif // FILE_OPERATIONS_H

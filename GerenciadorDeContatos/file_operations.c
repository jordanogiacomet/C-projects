#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"

void loadContacts(HashTable* hashTable, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error creating file");
            return;
        }
        fclose(file);
        return;
    }
    char name[50];
    char phone[20];
    while (fscanf(file, "%49s %19s", name, phone) != EOF) {
        addContact(hashTable, name, phone);
    }
    fclose(file);
}

void saveContacts(HashTable* hashTable, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        Contact* temp = hashTable->table[i];
        while (temp != NULL) {
            fprintf(file, "%s %s\n", temp->name, temp->phone);
            temp = temp->next;
        }
    }
    fclose(file);
}

void backupContacts(HashTable* hashTable, const char* backupFilename) {
    FILE* file = fopen(backupFilename, "w");
    if (file == NULL) {
        perror("Error opening backup file");
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        Contact* temp = hashTable->table[i];
        while (temp != NULL) {
            fprintf(file, "%s %s\n", temp->name, temp->phone);
            temp = temp->next;
        }
    }
    fclose(file);
    printf("Backup completed successfully.\n");
}

void restoreContacts(HashTable* hashTable, const char* backupFilename) {
    FILE* file = fopen(backupFilename, "r");
    if (file == NULL) {
        perror("Error opening backup file");
        return;
    }
    freeContacts(hashTable);
    char name[50];
    char phone[20];
    while (fscanf(file, "%49s %19s", name, phone) != EOF) {
        addContact(hashTable, name, phone);
    }
    fclose(file);
    printf("Contacts restored from backup successfully.\n");
}
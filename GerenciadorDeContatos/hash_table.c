#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"
#include "file_operations.h"

void initializeHashTable(HashTable* hashTable) {
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

int getHashIndex(const char* name) {
    char firstLetter = tolower(name[0]);
    if(firstLetter >= 'a' && firstLetter <= 'z') {
        return firstLetter - 'a';
    }
    return -1;
}

void addContact(HashTable* hashTable, const char* name, const char* phone) {
    int index = getHashIndex(name);
    if(index == -1) {
        printf("Nome inválido.\n");
        return;
    }
    if (searchContactDuplicate(hashTable->table[index], name, phone) != NULL) {
        printf("Contato duplicado.\n");
        return;
    }

    Contact* newContact = createContact(name, phone);
    if (hashTable->table[index] == NULL) { 
        hashTable->table[index] = newContact;
    } else {
        Contact* temp = hashTable->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newContact;
    }
    saveContacts(hashTable, FILENAME);
    backupContacts(hashTable, "backup_contacts.txt");
}

int searchContacts(HashTable* hashTable, const char* name) {
    int index = getHashIndex(name);
    if(index == -1) {
        printf("Nome inválido.\n");
        return 0;
    }
    
    Contact* temp = hashTable->table[index];
    int contactIndex = 1;

    printf("Contatos com o nome: %s\n\n", name);
    while (temp != NULL) {
        if (strcasestr(temp->name, name) != NULL) {
            printf("%d. Nome = %s, Telefone = %s\n", contactIndex, temp->name, temp->phone);
            contactIndex++;
        }
        temp = temp->next;
    }

    return contactIndex;
}

void removeContact(HashTable* hashTable, const char* name) {
    int index = getHashIndex(name);
    if(index == -1) {
        printf("Nome inválido");
        return;
    }

    Contact* temp = hashTable->table[index];
    Contact* prev = NULL;

    if (temp != NULL && strcmp(temp->name, name) == 0) {
        hashTable->table[index] = temp->next;
        free(temp);
        saveContacts(hashTable, FILENAME);
        backupContacts(hashTable, "backup_contacts.txt"); 
        return;
    }

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Contact not found.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    saveContacts(hashTable, FILENAME);
    backupContacts(hashTable, "backup_contacts.txt"); 
}

void editContact(HashTable* hashTable, const char* name) {
    int contactIndex = searchContacts(hashTable, name);
    if (contactIndex == 1) {
        printf("Nenhum contato encontrado com o nome fornecido.\n");
        return;
    }
    printf("%d. Sair.\n", contactIndex);
    int choice;
    printf("Escolha o número do contato que deseja editar: ");
    scanf("%d", &choice);
    getchar(); 
    if (choice == contactIndex) {
        printf("Saindo...\n");
        return;
    }
    while (choice < 0 || choice >= contactIndex) {
        printf("Escolha inválida. Tente novamente.\n");
        printf("Escolha o número do contato que deseja editar: ");
        scanf("%d", &choice);
        getchar();
        if (choice == contactIndex) {
            printf("Saindo...\n");
            return;
        }
    }
    char newName[50] = "";
    char newPhone[20] = "";
    int contador = 1;
    Contact* temp = hashTable->table[getHashIndex(name)];
    while (temp != NULL) {
        if (strcasestr(temp->name, name) != NULL) {
            if (contador == choice && contador <= contactIndex) {
                Contact* contact = temp;
                printf("Digite o novo nome (ou deixe vazio para manter o atual): ");
                getValidName(newName, sizeof(newName));
                printf("Digite o novo telefone (ou deixe vazio para manter o atual): ");
                getValidPhone(newPhone, sizeof(newPhone));
                if (contact != NULL) {
                    if (newName[0] != '\0') {
                        strcpy(contact->name, newName);
                    }
                    if (newPhone[0] != '\0') {
                        strcpy(contact->phone, newPhone);
                    }
                    saveContacts(hashTable, FILENAME);
                    printf("Contato atualizado.\n");
                } else {
                    printf("Contato não encontrado.\n");
                }
            }
            contador++;
        }
        temp = temp->next;
    }
}

void displayContacts(HashTable* hashTable) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        Contact* temp = hashTable->table[i];
        while (temp != NULL) {
            printf("Contato: Nome = %s, Telefone = %s\n", temp->name, temp->phone);
            temp = temp->next;
        }
    }
}

void freeContacts(HashTable* hashTable) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        Contact* temp = hashTable->table[i];
        while (temp != NULL) {
            Contact* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
        hashTable->table[i] = NULL;
    }
}

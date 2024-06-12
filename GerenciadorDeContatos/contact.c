#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '-') {
            return 0;
        }
    }
    return 1;
}

int isValidPhoneNumber(const char *phone) {
    int length = strlen(phone);
    char formattedPhoneNumber[length];
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (isdigit(phone[i])) {
            formattedPhoneNumber[j++] = phone[i];
        }
    }
    formattedPhoneNumber[j] = '\0';
    if (strlen(formattedPhoneNumber) != 10 && strlen(formattedPhoneNumber) != 11) {
        return 0;
    }
    return 1;
}

void readString(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
}

char* getValidName(char* buffer, int size) {
    readString(buffer, size);
    while (!isValidName(buffer)) {
        printf("Nome inválido. O nome deve conter apenas letras, espaços e possivelmente hífens.\n");
        printf("Digite o nome novamente: ");
        readString(buffer, size);
    }
    return buffer;
}

char* getValidPhone(char* buffer, int size) {
    readString(buffer, size);
    while (!isValidPhoneNumber(buffer)) {
        printf("Telefone inválido. O telefone deve conter apenas números.\n");
        printf("Digite o telefone novamente: ");
        readString(buffer, size);
    }
    return buffer;
}

Contact* createContact(const char* name, const char* phone) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = NULL;

    return newContact;
}

Contact* searchContactDuplicate(Contact* head, const char* name, const char* phone) {
    Contact* temp = head;
    while (temp != NULL) {
        if (strcasecmp(temp->name, name) == 0 && strcmp(temp->phone, phone) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact {
    char name[50];
    char phone[20];
    struct Contact* next;
} Contact;

int isValidName(const char *name);
int isValidPhoneNumber(const char *phone);
void readString(char* buffer, int size);
char* getValidName(char* buffer, int size);
char* getValidPhone(char* buffer, int size);
Contact* createContact(const char* name, const char* phone);
Contact* searchContactDuplicate(Contact* head, const char* name, const char* phone);

#endif // CONTACT_H

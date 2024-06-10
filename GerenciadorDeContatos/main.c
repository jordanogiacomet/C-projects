#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "contacts.txt"

typedef struct Contact {
  
  char name[50];
  char phone[20];
  struct Contact* next;

} Contact;

int isValidName(const char *name) {
  for(int i = 0; name[i] != '\0'; i++) {
    if(!isalpha(name[i]) && name[i] != " " && name[i] != '-') {
      return 0;
    }
  }
  return 1;
}

int isValidPhoneNumber(const char *phone) {
  int length = strlen(phone);

  char formattedPhoneNumber[length];
  int j = 0;
  for(int i = 0; i < length; i++) {
    if(isdigit(phone[i])) {
      formattedPhoneNumber[j++] = phone[i];
    }
  }
  formattedPhoneNumber[j] = '\0';
  if(strlen(formattedPhoneNumber) != 10 && strlen(formattedPhoneNumber) != 11) {
    return 0;
  }
  return 1;
}

void readString(char* buffer, int size) {
  if(fgets(buffer, size, stdin) != NULL) {
    size_t len = strlen(buffer);
    if(len > 0 && buffer[len-1] == '\n') {
      buffer[len-1] = '\0';
    } else {
      int c;
      while((c = getchar()) != '\n' && c != EOF);
    }
  } else {
    printf("Erro ao ler entrada.\n");
    exit(EXIT_FAILURE);
  }
}

char* getValidName(const char* buffer, int size) {
  readString(buffer, size);
  while(!isValidName(buffer)) {
    printf("Nome inválido. O nome deve conter apenas letras, espaços e possivelmente hífens.\n");
    printf("Digite o nome novamente: ");
    readString(buffer, size);
  }
  return buffer;
}

char* getValidPhone(const char* buffer, int size) {
  readString(buffer, size);
  while(!isValidPhoneNumber(buffer)) {
    printf("Telefone inválido. O telefone deve conter apenas números.\n");
    printf("Digite o telefone novamente: ");
    readString(buffer, size);
  }
  return buffer;
}

void saveContacts(Contact* head, const char* filename) {
  FILE* file = fopen(filename, "w");

  if(file == NULL) {
    printf("Error to open file.\n");
    return;
  }
  Contact *temp = head;

  while(temp != NULL) {
    fprintf(file, "%s %s\n", temp->name, temp->phone);
    temp = temp->next;
  }
  fclose(file);
}


Contact* createContact(const char* name,   const char* phone) {
  
  Contact* newContact = (Contact*)malloc(sizeof(Contact));
  
  if(newContact == NULL) {
    
    printf("Memory allocation failed.\n");
    exit(1);
  }

  strcpy(newContact->name, name);
  strcpy(newContact->phone, phone);
  newContact->next = NULL;

  return newContact;
}

Contact* searchContactDuplicate(Contact* head, const char* name, const char* phone) {
  Contact* temp = head;
  while(temp != NULL) {
    if(strcasecmp(temp->name, name) == 0 && strcmp(temp->phone, phone) == 0) {
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

Contact* addContact(Contact** head, const char* name, const char* phone) {
  if(searchContactDuplicate(*head, name, phone) != NULL) {
    printf("Contato duplicado.\n");
    return NULL;
  }

  Contact* newContact = createContact(name, phone);
  
  if(*head == NULL){ 
    *head = newContact;
  } else {
   
    Contact* temp = *head;
    
    while(temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newContact;
  }
  saveContacts(*head, FILENAME);
  printf("Contato adicionado.\n");
}

int searchContacts(Contact* head, const char* name) {
  
  Contact* temp = head;
  int index = 1;
  
  printf("Contatos com o nome: %s\n\n", name);
  while(temp != NULL) {
    if(strcasestr(temp->name, name) != NULL) {
      printf("%d. Nome = %s, Telefone = %s\n", index, temp->name, temp->phone);
      index++;
    }
    temp = temp->next;
  }
  
  return index;
}

void removeContact(Contact** head, const char* name) {
  if (*head == NULL) {
      printf("Contact not found.\n");
      return;
  }
  
  Contact* temp = *head;
  Contact* prev = NULL;

  if(strcmp(temp->name, name) == 0) {
    *head = temp->next;
    free(temp);
    saveContacts(*head, FILENAME);
    return;
  }

  while(temp != NULL && strcmp(temp->name, name) != 0) {
    prev = temp;
    temp = temp->next;
  }
  if(temp == NULL) {
    printf("Contact not found.\n");
    return;
  }
  prev->next = temp->next;
  free(temp);
  saveContacts(*head, FILENAME);
}

void editContact(Contact* head, const char* name) {
  int index = searchContacts(head, name);
  if(index == 1) {
    printf("Nenhum contato encontrado com o nome fornecido.\n");
    return;
  }

  printf("%d. Sair.\n", index);
  
  int choice;
  printf("Escolha o número do contato que deseja editar: ");
  scanf("%d", &choice);
  getchar(); 

  if(choice == index) {
    printf("Saindo...\n");
    return;
  }

  while (choice < 0 || choice >= index) {
      printf("Escolha inválida. Tente novamente.\n");
      printf("Escolha o número do contato que deseja editar: ");
      scanf("%d", &choice);
      getchar();  
      if(choice == index) {
        printf("Saindo...\n");
        return;
    }
  }
  
  char newName[50] = "";
  char newPhone[20] = "";
  int contador = 1;
  Contact* temp = head;

  while(temp != NULL) {
    if(strcasestr(temp->name, name) != NULL) {
      if(contador == choice && contador <= index) {
        Contact* contact = temp;
        printf("Digite o novo nome (ou deixe vazio para manter o atual): ");
        getValidName(newName, sizeof(newName));
        printf("Digite o novo telefone (ou deixe vazio para mander o atual): ");
        getValidPhone(newPhone, sizeof(newPhone));
        
        if(contact != NULL) {
          if(newName[0] != '\0') {
            strcpy(contact->name, newName);
          }
          if(newPhone[0] != '\0') {
            strcpy(contact->phone, newPhone); 
          }

          saveContacts(head, FILENAME);
          printf("Contato atualizado.\n");
          

        } else {
          printf("Contact not found");
        }
      }
      contador++;
    }
    temp = temp->next;
  }
}


void loadContacts(Contact **head, const char* filename) {
  FILE* file = fopen(filename, "r");

  if(file == NULL) {
    file = fopen(filename, "w");
    if(file == NULL) {
      printf("Error to create file.\n");
      return;
    }
    fclose(file);
    return;
  }

  char name[50];
  char phone[20];

  while(fscanf(file, "%49s %14s", name, phone) != EOF) {
    addContact(head, name, phone);
  }

  fclose(file);
}

void displayContacts(Contact* head) {
  Contact* temp = head;
  while(temp != NULL) {
    printf("Contato: Nome = %s, Telefone = %s\n", temp->name, temp->phone);
    temp = temp->next;
  }
}

void displayMenu() {
  printf("Menu:\n");
  printf("1. Adicionar contato\n");
  printf("2. Editar contato\n");
  printf("3. Remover contato\n");
  printf("4. Buscar contato\n");
  printf("5. Exibir contatos\n");
  printf("6. Sair\n");
  printf("Escolha uma opção: ");
}

void freeContacts(Contact* head) {
  Contact* temp;
  while(head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
}

int main(void) {
    Contact* head = NULL;
    const char* filename = FILENAME;

    loadContacts(&head, filename);
    
    int choice;
    char name[50];
    char phone[20];
    char newName[50];
    char newPhone[20];

    while(1) {
      displayMenu();
      scanf("%d", &choice);
      getchar();

      switch(choice) {
        case 1:
            printf("Digite o nome: ");
            getValidName(name, sizeof(name));
            while(strlen(name) == 0) {
              printf("Não é permitido cadastrar contato sem o nome.\n");
              printf("Digite o nome novamente: ");
              getValidName(name, sizeof(name));
            } 
            printf("Digite o telefone: ");
            getValidPhone(phone, sizeof(phone));
            addContact(&head, name, phone); 
            break;
        case 2:
            printf("Digite o nome do contato a ser editado: ");
            getValidName(name, sizeof(name));
            editContact(head, name);
            break;
        case 3: 
            printf("Digite o nome do contato a ser removido: ");
            getValidName(name, sizeof(name));
            removeContact(&head, name);
            printf("Contato removido. \n");
            break;
        case 4:
            printf("Digite o nome do contato a ser buscado: ");
            getValidName(name, sizeof(name));
            searchContacts(head, name);
            break;
        case 5:
            printf("Contatos: \n\n");
            displayContacts(head);
            break;
        case 6:
            printf("Saindo...\n");
            freeContacts(head);
            exit(0);
            break;
        default:
            printf("Opção invalida. Tente novamente.\n");
      }
    }
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "hash_table.h"
#include "file_operations.h"

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

int main(void) {
    HashTable hashTable;
    initializeHashTable(&hashTable);
    loadContacts(&hashTable, FILENAME);

    int choice;
    char name[50];
    char phone[20];

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Digite o nome: ");
                getValidName(name, sizeof(name));
                while (strlen(name) == 0) {
                    printf("Não é permitido cadastrar contato sem o nome.\n");
                    printf("Digite o nome novamente: ");
                    getValidName(name, sizeof(name));
                } 
                printf("Digite o telefone: ");
                getValidPhone(phone, sizeof(phone));
                addContact(&hashTable, name, phone); 
                break;
            case 2:
                printf("Digite o nome do contato a ser editado: ");
                getValidName(name, sizeof(name));
                editContact(&hashTable, name);
                break;
            case 3: 
                printf("Digite o nome do contato a ser removido: ");
                getValidName(name, sizeof(name));
                removeContact(&hashTable, name);
                printf("Contato removido.\n");
                break;
            case 4:
                printf("Digite o nome do contato a ser buscado: ");
                getValidName(name, sizeof(name));
                searchContacts(&hashTable, name);
                break;
            case 5:
                printf("Contatos:\n\n");
                displayContacts(&hashTable);
                break;
            case 6:
                printf("Saindo...\n");
                freeContacts(&hashTable);
                exit(0);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}

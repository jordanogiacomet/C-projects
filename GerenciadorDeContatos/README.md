
# Agenda de Contatos

Este projeto é uma aplicação simples de agenda de contatos em C, utilizando uma tabela hash para armazenar e gerenciar contatos. A aplicação permite adicionar, editar, remover, buscar e exibir contatos, bem como salvar e carregar os contatos de um arquivo.



## Estrutura do Projeto
- main.c: Contém a função principal e o menu do programa.
- contact.h e contact.c: Funções relacionadas aos contatos.
- hash_table.h e hash_table.c: Funções relacionadas à tabela hash.
- file_operations.h e file_operations.c: Funções relacionadas às operações de arquivo.
## Funcionalidades
- Adicionar Contato: Permite adicionar um novo contato à agenda.
- Editar Contato: Permite editar os dados de um contato existente.
- Remover Contato: Permite remover um contato da agenda.
- Buscar Contato: Permite buscar contatos pelo nome.
- Exibir Contatos: Exibe todos os contatos armazenados na agenda.
- Salvar Contatos: Salva os contatos em um arquivo.
- Carregar Contatos: Carrega os contatos a partir de um arquivo.
- Backup e Restauração: Permite criar um backup dos contatos e restaurá-los a partir do backup.
## Roadmap

- Autenticação: Implementar um sistema de autenticação para proteger os contatos.
- Interface Gráfica (GUI): Desenvolver uma interface gráfica para melhorar a usabilidade.
- Testes Unitários: Escrever testes unitários para garantir a qualidade do código.
- Validação Avançada: Melhorar a validação de entrada para nomes e telefones.
- Pesquisa Avançada: Implementar funcionalidades de pesquisa mais avançadas, como busca por número de telefone ou por parte do nome.
- Importação/Exportação: Adicionar funcionalidades para importar e exportar contatos em formatos diferentes (CSV, JSON, etc.).
- Logs: Implementar um sistema de logs para monitorar as operações realizadas na agenda.
- Documentação: Melhorar a documentação do código e adicionar exemplos de uso.
- Multilinguagem: Adicionar suporte a múltiplos idiomas.


## Rodando localmente

Clone o projeto

```bash
  git clone https://github.com/jordanogiacomet/Gerenciador-de-Contatos.git
```

Entre no diretório do projeto

```bash
  cd Gerenciador-de-Contatos
```


Use um compilador de C, como gcc, para compilar o projeto. Por exemplo:

```bash
  gcc main.c contact.c hash_table.c file_operations.c -o agenda
```
Após compilar, execute o programa:

```bash
  ./agenda
```


## Contribuindo

Contribuições são sempre bem-vindas!

- Faça um fork do projeto.
- Crie uma branch para a sua feature (git checkout -b feature/sua-feature).
- Commit suas mudanças (git commit -am 'Adiciona nova feature').
- Push para a branch (git push origin feature/sua-feature).
- Abra um Pull Request.

## Licença

[MIT](https://choosealicense.com/licenses/mit/)


## Autores

- [@jordanogiacomet](https://www.github.com/jordanogiacomet)


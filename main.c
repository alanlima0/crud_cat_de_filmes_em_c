#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct filme {
    char titulo[50];
    char categoria[30];
    int duracao;
    int lancamento;
} filme;

typedef struct No {
    struct No* proximo;
    struct No* anterior;
    filme dados;  // Contém os dados do filme
} No;

void exibir_menu(){
    printf("--------------MENU---------------------\n");
    printf("1 - Inserir Filme\n2 - Buscar Filme\n3 - Exibir Catálogo\n4 - Excluir Filme\n0 - Sair\n");
    printf("Escolha uma opção: ");
}

void voltar_menu(){
    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); 
}

No* inserir_filme(No* catalogo, const char* titulo, const char* categoria, int duracao, int lancamento) {
    No* novo_filme = (No*)malloc(sizeof(No));

    strcpy(novo_filme->dados.titulo, titulo);
    strcpy(novo_filme->dados.categoria, categoria);
    novo_filme->dados.duracao = duracao;
    novo_filme->dados.lancamento = lancamento;

    novo_filme->proximo = catalogo;
    novo_filme->anterior = NULL;

    if (catalogo != NULL)
        catalogo->anterior = novo_filme;

    return novo_filme;
}

void imprime_catalogo(No* catalogo) {
    No* atual = catalogo;

    if (atual == NULL) {
        printf("Catálogo vazio!\n");
        return;
    }
    while (atual != NULL) {
        printf("Título")
        printf("Título: %s, Categoria: %s, Duração: %d min, Lançamento: %d\n",
               atual->dados.titulo, atual->dados.categoria, atual->dados.duracao, atual->dados.lancamento);
        atual = atual->proximo;
    }
}

No* procura_filme(No* catalogo, const char* inicio_titulo) {
    No* temp = catalogo;
    int encontrado = 0;
    while (temp != NULL) {
        if (strncmp(temp->dados.titulo, inicio_titulo, strlen(inicio_titulo)) == 0) {
            printf("Título: %s, Categoria: %s, Duração: %d min, Lançamento: %d\n",
                   temp->dados.titulo, temp->dados.categoria, temp->dados.duracao, temp->dados.lancamento);
            encontrado = 1;
        }
        temp = temp->proximo;
    }
    if (!encontrado) {
        printf("Nenhum filme encontrado!\n");
    }
    return NULL;
}

No* excluir_filme(No* catalogo, const char* parte_titulo) {
    No* temp = catalogo;
    int encontrado = 0;

    while (temp != NULL) {
        if (strstr(temp->dados.titulo, parte_titulo) != NULL) {
            encontrado = 1;
            break; 
        }
        temp = temp->proximo;
    }

    if (!encontrado) {
        printf("Filme não encontrado!\n");
        return catalogo;
    }

    if (temp == catalogo) {
        catalogo = temp->proximo;
        if (catalogo != NULL) 
            catalogo->anterior = NULL;
    } else {
        if (temp->anterior != NULL)
            temp->anterior->proximo = temp->proximo;
        if (temp->proximo != NULL)
            temp->proximo->anterior = temp->anterior;
    }

    free(temp);
    printf("Filme removido com sucesso!\n");
    return catalogo;
}

int main() {
    No* catalogo = NULL;
    int opcao;

    do {
        system("clear"); 
        
        exibir_menu();
        scanf("%d", &opcao);
        getchar(); 

        system("clear"); 

        switch (opcao) {
            case 1: {
                char titulo[50], categoria[30];
                int duracao, lancamento;

                printf("Título do filme: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Categoria do filme: ");
                fgets(categoria, 30, stdin);
                categoria[strcspn(categoria, "\n")] = '\0';

                printf("Duração (min): ");
                scanf("%d", &duracao);
                printf("Ano de lançamento: ");
                scanf("%d", &lancamento);
                getchar(); 

                catalogo = inserir_filme(catalogo, titulo, categoria, duracao, lancamento);
                printf("Filme inserido com sucesso!\n");

                voltar_menu();
                break;
            }
            case 2: {
                char inicio_titulo[50];
                printf("Digite o título do filme que deseja buscar: ");
                fgets(inicio_titulo, 50, stdin);
                inicio_titulo[strcspn(inicio_titulo, "\n")] = '\0';
                procura_filme(catalogo, inicio_titulo);

                voltar_menu();
                break;
            }
            case 3:
                imprime_catalogo(catalogo);

                voltar_menu();
                break;
            case 4: {
                char parte_titulo[50];
                printf("Digite parte do título do filme que deseja excluir: ");
                fgets(parte_titulo, 50, stdin);
                parte_titulo[strcspn(parte_titulo, "\n")] = '\0';
                catalogo = excluir_filme(catalogo, parte_titulo);

                voltar_menu();
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");

                voltar_menu();
        }
    } while (opcao != 0);

    return 0;
}

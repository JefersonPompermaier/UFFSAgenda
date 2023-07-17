#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "agenda.h"
#include "agenda.c"

int main() {
    setlocale(LC_ALL, "Portuguese");
    Evento* raiz = NULL;
    int cod = 0, opcao=1;

    while (opcao != 0) {
        printf("\n--- MENU ---\n");
        printf("1. Incluir compromisso\n");
        printf("2. Consultar compromisso por data e hora\n");
        printf("3. Consultar compromissos por data\n");
        printf("4. Alterar compromisso por data e hora\n");
        printf("5. Listar todos os compromissos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao);
        if (opcao == 1) {
            cod++;
            Data dataEvento;
            printf("\nDigite a data e hora do compromisso! \n");
            printf("Dia: ");
            scanf("%d", &dataEvento.dia);
            printf("Mes: ");
            scanf("%d", &dataEvento.mes);
            printf("Ano: ");
            scanf("%d", &dataEvento.ano);
            printf("Hora: ");
            scanf("%d", &dataEvento.hora);
            printf("Minuto: ");
            scanf("%d", &dataEvento.minuto);
            float duracao;
            printf("Defina a duração do evento: ");
            scanf("%f", &duracao);
            char descricao[100];
            printf("Descrição: ");
            scanf("%s", descricao);
            raiz = incluirComp(raiz, cod, dataEvento, duracao, descricao);
            
        }else if(opcao == 2){
            Data dataEvento;
            printf("Digite o dia que deseja consultar: \n");
            scanf("%d", &dataEvento.dia);
            printf("Digite o mes que deseja consultar: \n");
            scanf("%d", &dataEvento.mes);
            printf("Digite o ano que deseja consultar: \n");
            scanf("%d", &dataEvento.ano);
            printf("Digite a hora que deseja consultar: \n");
            scanf("%d", &dataEvento.hora);
            printf("Digite o minuto que deseja consultar: \n");
            scanf("%d", &dataEvento.minuto);
            if(verificarExistenciaComp(raiz, dataEvento)==1){
                consultarCompDataHora(raiz, dataEvento);
            }else{
                printf("\nNenhum compromisso encontrado na data e hora informada!\n\n");

            }
        }else if(opcao == 3){
            Data dataEvento;
            printf("Digite o dia que deseja consultar: \n");
            scanf("%d", &dataEvento.dia);
            printf("Digite o mes que deseja consultar: \n");
            scanf("%d", &dataEvento.mes);
            printf("Digite o ano que deseja consultar: \n");
            scanf("%d", &dataEvento.ano);
            if(verificarExistenciaData(raiz, dataEvento)==1){
            consultarCompData(raiz, dataEvento);
            }else{
                printf("\nNenhum compromisso encontrado na data informada!\n\n");
            }
        }else if(opcao == 4){
            Data dataEvento;
            printf("Digite o dia do compromisso que deseja alterar: \n");
            scanf("%d", &dataEvento.dia);
            printf("Digite o mes do compromisso que deseja alterar: \n");
            scanf("%d", &dataEvento.mes);
            printf("Digite o ano do compromisso que deseja alterar: \n");
            scanf("%d", &dataEvento.ano);
            printf("Digite a hora do compromisso que deseja alterar: \n");
            scanf("%d", &dataEvento.hora);
            printf("Digite o minuto do compromisso que deseja alterar: \n");
            scanf("%d", &dataEvento.minuto);
            
            if(verificarExistenciaComp(raiz, dataEvento)==1){
            float duracao;
            printf("Defina a nova duração do evento: ");
            scanf("%f", &duracao);
            char descricao[100];
            printf("Nova descrição: ");
            scanf("%s", descricao);
            cod = encontraCod(raiz, dataEvento);
            alterarCompDataHora(cod, raiz, dataEvento, duracao, descricao);
            }else{
                printf("\nNenhum compromisso encontrado na data e hora informada!\n\n");
            }
        }else if(opcao == 5){
            printf("Todos os compromissos: \n");
            listarComp(raiz);
        }

    }
 
    void liberarMemoria(Evento* raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarMemoria(raiz->left);
    liberarMemoria(raiz->right);
    free(raiz);
    }
}
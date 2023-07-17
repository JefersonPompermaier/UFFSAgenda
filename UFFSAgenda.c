
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


struct _data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minuto;

};

typedef struct _data Data;


struct _evento {
    int codigo;
    Data dataEvento;
    float duracao;
    char descricao[100];
    struct _evento *right;
    struct _evento *left;
};

typedef struct _evento Evento;

// Função para criar um novo evento
Evento* defineComp(int codigo, Data dataEvento, float duracao, char descricao[]) {
    Evento* evento = (Evento*)malloc(sizeof(Evento));
    evento->codigo = codigo;
    evento->dataEvento.dia = dataEvento.dia;
    evento->dataEvento.mes = dataEvento.mes;
    evento->dataEvento.ano = dataEvento.ano;
    evento->dataEvento.hora = dataEvento.hora;
    evento->dataEvento.minuto = dataEvento.minuto;
    evento->duracao = duracao;
    strcpy(evento->descricao, descricao);
    evento->left = NULL;
    evento->right = NULL;
    return evento;
}

// Função para verificar a existência de um compromisso na árvore
int verificarExistenciaComp(Evento* raiz, Data dataEvento) {
    if (raiz == NULL) {
        return 0;
    }
    if (dataEvento.dia == raiz->dataEvento.dia &&
        dataEvento.mes == raiz->dataEvento.mes &&
        dataEvento.ano == raiz->dataEvento.ano &&
        dataEvento.hora == raiz->dataEvento.hora &&
        dataEvento.minuto == raiz->dataEvento.minuto) {
        return 1;
    }
    verificarExistenciaComp(raiz->left, dataEvento);
    verificarExistenciaComp(raiz->right, dataEvento);
}

int verificarExistenciaData(Evento* raiz, Data dataEvento) {
    if (raiz == NULL) {
        return 0;
    }
    if (dataEvento.dia == raiz->dataEvento.dia &&
        dataEvento.mes == raiz->dataEvento.mes &&
        dataEvento.ano == raiz->dataEvento.ano) {
        return 1;
    }
    verificarExistenciaData(raiz->left, dataEvento);
    verificarExistenciaData(raiz->right, dataEvento);
}


//Funcao para verificar a existencia de compromissos na data informada

void consultarCompDataHora(Evento* raiz, Data dataEvento) {
    if ( verificarExistenciaComp(raiz, dataEvento) == 0) {
        return;
    }
    if (dataEvento.dia == raiz->dataEvento.dia &&
        dataEvento.mes == raiz->dataEvento.mes &&
        dataEvento.ano == raiz->dataEvento.ano &&
        dataEvento.hora == raiz->dataEvento.hora &&
        dataEvento.minuto == raiz->dataEvento.minuto) {
        printf("\nCompromisso encontrado!\n");
        printf("Descrição: \n%s\n\n", raiz->descricao);
        return;
    }
    consultarCompDataHora(raiz->left, dataEvento);
    consultarCompDataHora(raiz->right, dataEvento);
}


//consulta compromissos na data informada

void consultarCompData(Evento* raiz, Data dataEvento) {
    if ( raiz == NULL) {
        return;
    }else{
    if (dataEvento.dia == raiz->dataEvento.dia &&
        dataEvento.mes == raiz->dataEvento.mes &&
        dataEvento.ano == raiz->dataEvento.ano) {
        printf("\nCodigo: %d\n", raiz->codigo);
        printf("Hora: %d\n", raiz->dataEvento.hora);
        printf("Minuto: %d\n", raiz->dataEvento.minuto);
        printf("Duração: %.2f\n", raiz->duracao);    
        printf("Descrição: %s\n", raiz->descricao);
        consultarCompData(raiz->left, dataEvento);
        consultarCompData(raiz->right, dataEvento);
        return;
        }
    }

}

// Função para incluir um novo compromisso na árvore
Evento* incluirComp(Evento* raiz, int codigo, Data dataEvento, float duracao, char descricao[]) {
    if (raiz == NULL) {
        return defineComp(codigo, dataEvento, duracao, descricao); 
    }
    if (verificarExistenciaComp(raiz, dataEvento)) {
        printf("Já existe um compromisso agendado para a mesma data e hora.\n");
        return raiz; 
    }
    if (codigo < raiz->codigo) {
        raiz->left = incluirComp(raiz->left, codigo, dataEvento, duracao, descricao); 
    } else if (codigo > raiz->codigo) {
        raiz->right = incluirComp(raiz->right, codigo, dataEvento, duracao, descricao); 
    }
    return raiz;
}

void listarComp(Evento* raiz) {
    if (raiz == NULL) {
        return; 
    }

    listarComp(raiz->left); 
    printf("\n");
    printf("Codigo: %d\n", raiz->codigo);
    printf("Data e hora: %d/%d/%d - %d:%d\n", raiz->dataEvento.dia, raiz->dataEvento.mes,
           raiz->dataEvento.ano, raiz->dataEvento.hora, raiz->dataEvento.minuto);
    printf("Duração: %.2f\n", raiz->duracao);
    printf("Descrição: %s\n", raiz->descricao);

    listarComp(raiz->right);
}

void alterarCompDataHora(int cod, Evento* raiz, Data dataEvento, float duracao, char descricao[]) {
    if (raiz == NULL)
        return;
    else {
        consultarCompDataHora(raiz, dataEvento);
        raiz->codigo = cod;
        raiz->dataEvento.dia = dataEvento.dia;
        raiz->dataEvento.mes = dataEvento.mes;
        raiz->dataEvento.ano = dataEvento.ano;
        raiz->duracao = duracao;
        strcpy(raiz->descricao, descricao);
        printf("Compromisso alterado!\n");
    }
}

int encontraCod(Evento * raiz, Data dataEvento){
        if (raiz == NULL) {
        return 0;
    }
    if (dataEvento.dia == raiz->dataEvento.dia &&
        dataEvento.mes == raiz->dataEvento.mes &&
        dataEvento.ano == raiz->dataEvento.ano) {
        return raiz->codigo;
    }
    encontraCod(raiz->left, dataEvento);
    encontraCod(raiz->right, dataEvento);
    
}
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

/*

void excluirComp(){



}

*/
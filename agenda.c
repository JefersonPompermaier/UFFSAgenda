#include <stdio.h>
#include "agenda.h"

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

// Função para criar um novo compromisso
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


//verifica se a data esta presente na agenda

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


//Funcao para verificar a existencia de compromissos na data e hora informada

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

//retorna o codigo presente na raiz para a funcao alterarCompDataHora

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

// altera o compromisso
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




//lista todos os compromissos
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



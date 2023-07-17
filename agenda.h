#ifndef AGENDA_H
#define AGENDA_H

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

Evento* defineComp(int codigo, Data dataEvento, float duracao, char descricao[]);
int verificarExistenciaComp(Evento* raiz, Data dataEvento);
int verificarExistenciaData(Evento* raiz, Data dataEvento);
void consultarCompDataHora(Evento* raiz, Data dataEvento);
void consultarCompData(Evento* raiz, Data dataEvento);
Evento* incluirComp(Evento* raiz, int codigo, Data dataEvento, float duracao, char descricao[]);
void listarComp(Evento* raiz);
void alterarCompDataHora(int cod, Evento* raiz, Data dataEvento, float duracao, char descricao[]);
int encontraCod(Evento* raiz, Data dataEvento);
void liberarMemoria(Evento* raiz);

#endif

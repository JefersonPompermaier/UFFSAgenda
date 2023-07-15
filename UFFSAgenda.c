
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


// define a raiz para ser incluida na arvore;

struct Evento* defineComp(int codigo, Data dataEvento, float duracao, char descricao[]){
    struct Evento* evento = (struct Evento*)malloc(sizeof(struct Evento));
    evento->codigo=codigo;
    evento->dataEvento.dia=dataEvento.dia;
    evento->dataEvento.mes=dataEvento.mes;
    evento->dataEvento.ano=dataEvento.ano;
    evento->dataEvento.hora=dataEvento.hora;
    evento->dataEvento.minuto=dataEvento.minuto;
    evento->duracao=duracao;
    strcpy(evento->descricao, descricao);
    evento->left=NULL;
    evento->right=NULL;
    return evento;
}

//desalocar memoria para a funcao anterior no decorrer do codigo: free(evento)



// verifica existencia do compromisso na arvore

int verificarExistenciaComp(struct Evento* raiz, Data dataEvento) {
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
    int existeEsquerda = verificarExistenciaComp(raiz->left, dataEvento);
    int existeDireita = verificarExistenciaComp(raiz->right, dataEvento);
    return existeEsquerda || existeDireita; 
}

struct Evento* incluirComp(struct Evento* raiz, int codigo, Data dataEvento, float duracao, char descricao[]) {
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






int main(){

    int i=1;
    struct Evento* raiz = NULL;
    int cod = 0;

    while (i==1) {
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 1) {
            cod++;
            Data dataEvento;
            printf("Digite a data e hora do compromisso! \n");
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
    return 0;
}

}
}

void consultarComp()(
    
)

void listarComp(){


}

void altComp(){


}

/*
.
.funcao em lista simples
.
void listarTodos(Evento *EstruturaPrinc){
    if(EstruturaPrinc){
        printf("Codigo: %d\n", EstruturaPrinc->codigo);
        printf("Data: %d/%d/%d\n", EstruturaPrinc->data.dia, EstruturaPrinc->data.mes, EstruturaPrinc->data.ano);
        printf("Hora: %d:%d\n", EstruturaPrinc->data.hora, EstruturaPrinc->data.minuto);
        printf("Duração: %.2f\n", EstruturaPrinc->duracao);
        printf("Descrição: %s\n", EstruturaPrinc->descricao);
        listarTodos(EstruturaPrinc->proximo);
    }

} 
*/

void excluirComp(){



}


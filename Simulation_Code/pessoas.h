/*
 Autor: Diogo Dias Almeida
 Número: 2019126638
 Email: a2019126638@isec.pt
 */
#include "espaco.h"
#ifndef PESSOAS_H
#define PESSOAS_H

typedef struct multidao pessoas, *pessoast;
typedef struct list lista,*plista;
struct multidao{
    char nome[30];
    int idade;
    char estado;
    int dias;
    int id;
    pessoast seguinte; //APONTA PARA A PRÓXIMA LIGAÇÃO   
};

struct list{ // PRINCIPAL
    int dias; //Dia em questao
    plista prox; //Aponta para o proximo
    pessoast prox1; //APONTA PARA As pessoas
};

pessoast leitura_pessoas(pessoast multidoes,int *total_pessoas);
void verifica(pessoast multidoes,int total);
void verifica_nomes(pessoast multidoes,int total);

plista eliminap(plista p,int *conta);
pessoast recua(pessoast multidoes, int *dia, plista p,int *total_pessoas,int conta,int total_locais,int *tab,local *salas,int *alter);
void avanca(plista p,pessoast multidoes);
plista dianovo(plista p,int dia,int *conta);
#endif /* PESSOAS_H */


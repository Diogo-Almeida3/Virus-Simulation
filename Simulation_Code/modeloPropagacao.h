/*
 Autor: Diogo Dias Almeida
 Número: 2019126638
 Email: a2019126638@isec.pt
 */
#include "espaco.h"
#include "pessoas.h"
#ifndef MODELOPROPAGACAO_H
#define MODELOPROPAGACAO_H
void taxaDisseminacao(pessoast multidoes, plocal salas, int total_locais,int total_pessoas,int *tab);
void maximoDiasRecuperacao(pessoast multidoes,int total_pessoas);
void modeloPropagacao(pessoas *multidoes,local *salas,int total_locais,int total_pessoas,int *tab);
void probabilidadeRecuperacao(pessoas *multidoes,int total_pessoas);
char taxaImunidade(char aux_estado);

#endif /* MODELOPROPAGACAO_H */


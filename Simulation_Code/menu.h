/*
 Autor: Diogo Dias Almeida
 Número: 2019126638
 Email: a2019126638@isec.pt
 */
#include "pessoas.h"
#include "utils.h"
#include "espaco.h"
#ifndef MENU_H
#define MENU_H

void transferir(pessoast multidoes, local *salas,int total_locais, int total_pessoas,int *tab);
pessoast adicionar(pessoast multidoes, local *salas, int total_locais, int *total_pessoas, int *tab);
pessoast preenche(pessoast ,int id,int total_pessoas,pessoast verifica);
pessoast remover(pessoast multidoes,local *salas, int total_locais,int *total_pessoas,int *tab);
#endif /* MENU_H */


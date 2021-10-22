/*
 Autor: Diogo Dias Almeida
 Número: 2019126638
 Email: a2019126638@isec.pt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "espaco.h"
#include "pessoas.h"
#include "utils.h"
#include "modeloPropagacao.h"
#include "menu.h"

void transferir(pessoast multidoes, local *salas, int total_locais, int total_pessoas, int *tab) {

    int i, j, aux;
    int id_atual = 0, id_envio= 0;
    int c_reserva = 0, aux_i1 = 0, aux_i2 = 0;
    int max_envio = 0, apoio = 0, decisao = 0;
    
    printf("\n********************************************************************************************************\n");
    printf("\nIndique o id do local que pretende retirar as pessoas.\n");
    
    do {
        decisao = 0;
        printf("Lista: ");
        for (i = 0; i < total_locais; i++)
            printf("\n\t->%d", salas[i].id);
        printf("\n");
        printf("\nEscolha: ");
        scanf("%d", &id_atual); //LOCAL DE ONDE QUER RETIRAR AS PESSOAS
        for (i = 0, aux = 0; i < total_locais; i++)
            if (salas[i].id == id_atual) {
                aux = 1;
                c_reserva = *(tab + i); //NAO POSSO TRANSFERIR DE UM LOCAL SEM PESSOAS
                aux_i1 = i; //ARMAZENA O I PARA COMPARAR MAIS TARDE AS LIGACOES
                break;
            }
        if(aux == 0)
            printf("O local nao existe.\n");
        else if(c_reserva == 0){          
            printf("O local esta vazio\n\n");
         
                printf("Prima 1 para continuar ou 0 para voltar ao menu.\n");
                do {
                    printf("\nDecisao:");
                    scanf("%d", &decisao);
                    printf("\n");
                } while (decisao < 0 || decisao > 1);
                if (decisao == 0)
                    return;
            }
    } while (aux == 0 || c_reserva == 0); //ENQUANTO O LOCAL ESTIVER VAZIO


    printf("\nIndique o id do local para onde vai transferir as pessoas.\n");
    
    do {
        decisao = 0;
        printf("Lista: ");
        for (i = 0; i < total_locais; i++)
            if (salas[i].id != id_atual)
                printf("\n\t->%d", salas[i].id);
        printf("\n");
        printf("\nEscolha: ");
        scanf("%d", &id_envio); //Recolhe o id do local para onde sao enviadas as pessoas
        for (i = 0, aux = 0; i < total_locais; i++)
            if (salas[i].id == id_envio && salas[i].id != id_atual) {
                aux = 1;
                aux_i2 = i;
                break;
            }
        if (aux == 1) {
            max_envio = salas[aux_i2].capacidade - *(tab + aux_i2);
            for (j = 0; j < 3; j++)
                if (salas[aux_i1].liga[j] == id_envio)
                    apoio += 1;
            if(max_envio == 0 && apoio == 1){ //Caso nao exista espaço mas os locais estejam ligados
                printf("O local para onde pretende transferir pessoas esta cheio.\n");
                apoio = 0;
            }
            else if(apoio == 0) //Caso os locais nao estejam ligado
                printf("Os locais nao se encontram ligados\n");
            
            if (apoio == 0) { 
                printf("Prima 1 para continuar ou 0 para voltar ao menu.\n");
                do {
                    printf("\nDecisao:");
                    scanf("%d", &decisao);
                    printf("\n");
                } while (decisao < 0 || decisao > 1);
                if (decisao == 0)
                    return;
            }           
        }
        else if(aux == 0)//Caso o local nao exista
            printf("Local nao existe.\n\n");
        
    } while (aux == 0 || apoio == 0);
    
    int enviados = 0,n_pessoas = 0;
    pessoast head_pessoas = multidoes;
    printf("\nIndique quantas pessoas pretende transferir.\n");
    do{
        printf("Numero: ");
        scanf("%d",&n_pessoas);
        if(n_pessoas > *(tab+aux_i1))
            printf("Impossivel transferir mais pessoas do que as que existem.\n\n");
        else if(n_pessoas < 0)
            printf("Impossivel transferir um numero negativo de pessoas.\n\n");
        else if(n_pessoas > max_envio)
            printf("O local nao suporta tantas pessoas. Impossivel Transferir.\n\n");
                 
    }while(n_pessoas > max_envio || n_pessoas < 0 || n_pessoas > *(tab+aux_i1));
    
    for(i = 0; i < total_pessoas;i++){
        if(head_pessoas->id == id_atual && n_pessoas != enviados){
            head_pessoas->id = id_envio;
            enviados +=1;
        }
        head_pessoas = head_pessoas->seguinte;
    }
    *(tab+aux_i1) -= n_pessoas;
    *(tab+aux_i2) += n_pessoas ;
}

pessoast adicionar(pessoast multidoes, local *salas, int total_locais, int *total_pessoas, int *tab){

    int id,aux,i_armazena;
    int i,decisao;
    printf("\n********************************************************************************************************\n");
    printf("\nIndique o id do local onde pretende adicionar um doente.\n");

    do {
        decisao = 0;
        printf("Lista: ");
        for (i = 0; i < total_locais; i++)
            printf("\n\t->%d", salas[i].id);
        printf("\n");
        printf("\nEscolha: ");
        scanf("%d", &id); //LOCAL DE ONDE QUER RETIRAR AS PESSOAS
        for (i = 0, aux = 0; i < total_locais; i++){
            if (salas[i].id == id && salas[i].capacidade != *(tab+i)) {
                aux = 1;
                i_armazena = i;
            } 
            else if(salas[i].capacidade == *(tab+i) && salas[i].id == id){
                printf("\nSala cheia\n"); 
                do{
                    printf("\nPrima 1 para continuar ou 0 para voltar ao menu.\n");
                    printf("Decisao: ");
                    scanf("%d",&decisao);
                    printf("\n");
                }while(decisao < 0 || decisao > 1);
                
                if(decisao == 0)
                    return multidoes;
            }
        }
        if(aux == 0 && decisao != 1)
            printf("O local nao existe.\n\n");
                        
    } while (aux == 0); //ENQUANTO O LOCAL ESTIVER VAZIO
    
    pessoast head_pessoas,novo,verifica = multidoes;
    novo = malloc(sizeof(pessoas));
    if(novo == NULL){
        printf("Erro na alocacao de memoria.\n");
        exit(0);
    }
    preenche(novo,id,*total_pessoas,verifica);
    if(multidoes == NULL || novo->id == salas[0].id){ // 1 == 1
        novo->seguinte = multidoes;
        multidoes = novo;
        *total_pessoas += 1;
        *(tab+i_armazena) += 1;
    }
    else{
        head_pessoas = multidoes;
        while(head_pessoas->seguinte != NULL && novo->id != head_pessoas->seguinte->id)
            head_pessoas = head_pessoas->seguinte;
        novo->seguinte = head_pessoas->seguinte;
        head_pessoas->seguinte = novo;
        *total_pessoas += 1;
        *(tab+i_armazena) += 1;
    }
    return multidoes;
}

pessoast preenche(pessoast novo,int id,int total_pessoas,pessoast verifica){
    int aux = 0,aux_1 = 0;
    int i;
    pessoast ver;
    
    do {
        printf("Nome: ");
        scanf("%s", novo->nome);
        ver = verifica;
        for(i = 0,aux_1 = 0; i < total_pessoas; i++) {
            if (strcmp(ver->nome, novo->nome) == 0) {
                printf("Nome repetido\n");
                aux_1 = 1;
            }
            ver = ver->seguinte;
        }
        free(ver);
        if(aux_1 == 0)
            aux = 1;
    }while(aux == 0);
    
    do{
        printf("Idade: ");
        scanf("%d",&novo->idade);  
        if(novo->idade <= 0)
            printf("Idade negativa ou nula.\n");
    }while(novo->idade <= 0);
    
    int d = novo->idade/10,j;
    int total;
    do{
        printf("Dias: ");
        scanf("%d",&novo->dias);
        total = 5 + d;
        if(novo->dias > total){
            printf("Impossivel usar este numero de dias.\n");
            j = 1;
        }
        else if(novo->dias < 0){
            printf("Dias negativos.\n");
            j = 1;
        }
        else
            j = 0;
            
    }while(j == 1);
    
    novo->estado = 'D';
    novo->id = id;
    novo->seguinte = NULL;
}

pessoast remover(pessoast multidoes,local *salas, int total_locais,int *total_pessoas,int *tab){
        
    int id,aux,i_armazena,apoio;
    int i,j,decisao;
    pessoast head_pessoas = multidoes;
    

    do {
        decisao = 0;
        printf("Lista: ");
        for (i = 0; i < total_locais; i++)
            printf("\n\t->%d", salas[i].id);
        printf("\n");
        printf("\nEscolha: ");
        scanf("%d", &id); //LOCAL DE ONDE QUER RETIRAR A PESSOA
        for (i = 0, aux = 0; i < total_locais; i++){
            if (salas[i].id == id && *(tab+i) > 0) {
                aux = 1;
                i_armazena = i;
            } 
            else if(*(tab+i) == 0 && salas[i].id == id){
                printf("\nSala vazia\nPrima 1 para continuar ou 0 para voltar ao menu.\n");
                do {
                    printf("\nDecisao:");
                    scanf("%d", &decisao);
                    printf("\n");
                } while (decisao < 0 || decisao > 1);
                if (decisao == 0)
                    return multidoes;
            }
                
        }
        if(aux == 0 && decisao != 1)
            printf("O local nao existe.\n\n");
            
    } while (aux == 0); //ENQUANTO O LOCAL ESTIVER VAZIO
    
    char nome[30];
    printf("\nIndique o nome da pessoa que pretende remover.\n");
    for(i = 0,j = 1; i < *total_pessoas;i++){
        if(i == 0)
            printf("\nNomes: \n");
        if(head_pessoas->id == salas[i_armazena].id){
            printf("%d: %s\n",j,head_pessoas->nome);
            j++; //SERVE PARA MELHORAR A LISTA DE NOMES DISPONIVEIS
        }
        
      head_pessoas = head_pessoas->seguinte; 
    }
    
    
    do{
        head_pessoas = multidoes;
        printf("Escolha: ");
        scanf("%s",nome);
        for(i = 0,aux = 0; i < *total_pessoas;i++){
            if(head_pessoas->id == salas[i_armazena].id){
                if(strcmp(head_pessoas->nome,nome) == 0){
                    aux = 1;
                    if(i == 0)
                        apoio = i;
                    else
                        apoio = i - 1;
                    
                }
                    
            }
            head_pessoas = head_pessoas->seguinte;
        }
        if(aux == 0)
            printf("Pessoa inexistente.\n\n");
    }while(aux == 0);
    
    pessoast teste,anterior = NULL;  
    teste = multidoes;
    
    while(teste != NULL && strcmp(teste->nome,nome) != 0 ){
        anterior = teste;
        teste = teste->seguinte;

    }
    
    if(teste == NULL)
        return multidoes;
    if(anterior == NULL)
        multidoes = teste->seguinte;
    else
        anterior->seguinte = teste->seguinte;
    free(teste);
        
       
    
    *(total_pessoas) -= 1;
    *(tab+i_armazena) -=1;
    return multidoes;
    
    
}
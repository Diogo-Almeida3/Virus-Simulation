/*
 Autor: Diogo Dias Almeida
 Número: 2019126638
 Email: a2019126638@isec.pt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoas.h"


pessoast leitura_pessoas(pessoast multidoes, int *total_pessoas) {
    FILE *f;
    char ficheiro[50];
    int total = 0,z = 0;
 
    /*PEDIDO AO UTILIZADOR PARA INTRODUZIR O FICHEIRO QUE PRETENDE UTILIZAR NA SIMULAÇÃO*/
    printf("\n=========================\n\t1: PessoasA\n\t2: PessoasB\n\t3: Outro\n=========================\n\n");
    do {
        
        do{
            printf("Escolha da populacao: ");
            scanf("%d",&z);
        }while(z <1 || z> 3);
        switch(z){
            case 1:
                strcpy(ficheiro,"pessoasa.txt");
                break;
            case 2:
                strcpy(ficheiro,"pessoasb.txt");
                break;
            case 3:
                printf("Indique a lista de pessoas: ");
                scanf("%s", &ficheiro);
                break;
        }
        f = fopen(ficheiro, "r");
        if (f == NULL) {
            printf("\nFicheiro inexistente.\n\n");
        }
    } while (f == NULL);
    /*----------------------------------------------------------------------------------*/
    char aux[30];
    pessoast novo,aux1;
    
    /*ALOCAÇÃO DA LISTA LIGADA */
    while(fscanf(f,"%s",aux) == 1){
        total++;
        novo = malloc(sizeof(pessoas));
        if(novo==NULL){
            printf("FALHA NA ALOCACAO"),
            exit(0);
        }
        strcpy(novo->nome,aux);
        fscanf(f,"%d %c",&novo->idade,&novo->estado);
        if(novo->estado == 'D')
            fscanf(f,"%d",&novo->dias);
        else
            novo->dias = 0;
        novo->seguinte = NULL;
        
        if(multidoes == NULL)
            multidoes = novo;
        else{
            
            aux1 = multidoes;
            while(aux1->seguinte != NULL)
                aux1 = aux1->seguinte;
            aux1->seguinte = novo;
        }
        
    }
    /*-------------------------------------------*/
   
    /*FECHAR O FICHEIRO*/
    fclose(f);
    /*-----------------*/
    if(total == 0){
        printf("Nao existem pessoas no ficheiro.\n");
        exit(0);
    }
    *total_pessoas = total;
    verifica_nomes(multidoes,total);
    verifica(multidoes,total);
    return multidoes;

}

void verifica(pessoast multidoes,int total){
    int i;
    char aux;
    
    for(i = 0; i < total; i++){
        aux = multidoes->estado;
        if(multidoes->idade < 0){
            printf("Idade negativa!\n");
            exit(0);
        }
        else if(aux != 'D' && aux != 'S' && aux != 'I'){
            printf("Estado invalido!\n");
            exit(0);
        } 
        else if(multidoes->dias < 0){
            printf("Dias de infecao negativos!\n");
            exit(0);
        }
            
        multidoes=multidoes->seguinte;
    }
}

void verifica_nomes(pessoast multidoes,int total){
    
    int i,j,aux,z;
    pessoast head_pessoas,suporte = multidoes;
    
    for(i = 0; i < total-1; i++){
        head_pessoas = multidoes; //RESETA A LISTA
        for(z = 0; z < i+1;z++)
            head_pessoas=head_pessoas->seguinte; //Anda sempre 1 elemento a frente do nome
        for(j = 0; j < total-i-1; j++){ //Faz apenas as vezes necessarias
            
            aux = strcmp(head_pessoas->nome,suporte->nome); //Compara se forem iguais devolve 0 e sai do programa
            if(aux == 0){
                printf("Nome repetido\n");
                exit(0);
            }
            head_pessoas = head_pessoas->seguinte; //Avança na lista que verifica
        }
        suporte = suporte->seguinte; //Avança na lista que escolhe o nome a ser verificado
    }
}
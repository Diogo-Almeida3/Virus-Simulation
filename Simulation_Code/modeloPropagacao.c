/*
 Autor: Diogo Dias Almeida
 Número: 2019126638
 Email: a2019126638@isec.pt
 */
#include <stdio.h>
#include <stdlib.h>
#include "modeloPropagacao.h"
#include "pessoas.h"
#include "utils.h"
#include "espaco.h"

void modeloPropagacao(pessoas *multidoes,local *salas,int total_locais,int total_pessoas,int *tab){
    
    taxaDisseminacao(multidoes,salas,total_locais,total_pessoas,tab);
    maximoDiasRecuperacao(multidoes,total_pessoas);
    probabilidadeRecuperacao(multidoes,total_pessoas);
}

void taxaDisseminacao(pessoast multidoes, plocal salas, int total_locais, int total_pessoas, int *tab) {
    int transmissor;
    int max[total_locais];
    int i,j,z,t,novo;
    int infetados,total_transmicoes,aux,total = 0,a_total = 0;
    pessoast verifica = multidoes,head_pessoas = multidoes,aux1,aux2= multidoes,aux3 = NULL;
    for(i = 0; i < total_locais; i++)
        *(max+i) = *(tab+i) * 0.75; //MAXIMO DE PESSOAS QUE PODEM SER INFETADAS POR SALA

    
        
    
    for(i = 0,transmissor = 0; i < total_locais; i++){ //VERIFICAR CADA LOCAL EXISTENTE
        total += *(tab+i); // VAI CALCULANDO O TOTAL DE PESSOAS PARA O FOR NAO REPETIR PESSOAS
        for(j = a_total,infetados = 0,total_transmicoes = 0; j < total;j++,a_total++){ //RESETAR OS INFETADOS NO LOCAL E O TOTAL POSSIVEL DE TRANSMISSOES
            if(verifica->estado == 'D')
                infetados +=1;
            verifica = verifica->seguinte;
        }     
        total_transmicoes = infetados * *(max+i); //CALCULAR O TOTAL DE TRANSMICOES POSSIVEIS
        
        for(j = 0,novo = 0; j < total_transmicoes && novo < infetados;){ //ENQUANTO O J NAO ULTRAPASSAR O NUMERO DE INFEÇOES NECESSARIAS CONTINUAS A CORRER
            
            if(head_pessoas->estado == 'D'){    //CASO ESTEJA DOENTE VAI FAZER Z INFEÇOES
                novo +=1;
                for(z = 0; z < *(max+i);z++,j++){
                    aux = intUniformRnd(0,*(tab+i))-1 ; //CALCULA UM PESSOA PARA SER INFETADA ENTRE A ATUAL E A ULTIMA
                    if(aux == transmissor && aux != (*(tab+i)-1))
                        aux +=1;
                    else if(aux == transmissor && aux == (*(tab+i)-1))
                        aux -=1;
                        
                    aux1 = aux2;                              //RESETAR LISTA
                    for(t = 0; t < aux;t++)
                        aux1 = aux1->seguinte; //ENCONTRA O ELEMENTO ESCOLHIDO
                    if(aux1->estado == 'S'){ //VERIFICA SE ESTA SAUDAVEL PARA PODER SER INFETADO VISTO QUE DOENTES E IMUNES NAO PODEM SER INFETADOS
                        aux1->estado = 'D';
                        aux1->dias = 0; //Igual a 0 pois quando for aplicada a funçao maximoDiasRecuperacao irá ser atualizada para 1
                    }
                    aux3 = aux1;                        //ATUALIZAR LISTA
                    
                }
            } 
            transmissor +=1;   
            head_pessoas = head_pessoas->seguinte;
        }
        for(j = 0; j < *(tab+i);j++)
            aux2 = aux2->seguinte;  
    }
}

void maximoDiasRecuperacao(pessoast multidoes,int total_pessoas){
    int i;
    int maximo,dezenas;
    char aux_estado;
    pessoast head_pessoas = multidoes;
    for(i = 0,maximo = 0; i < total_pessoas;i++){
        
        if (head_pessoas->estado == 'D'){
            head_pessoas->dias += 1;
            dezenas = head_pessoas->idade/10;
            maximo = 5 + dezenas;
            
            if(head_pessoas->dias >= maximo){
                head_pessoas->dias = 0;                                           //Reseta os dias de infeçao
                aux_estado = head_pessoas->estado;
                head_pessoas->estado = taxaImunidade(aux_estado);                 //VERIFICA SE SE TORNA IMUNE OU SAUDAVEL
            }
        }
        head_pessoas = head_pessoas->seguinte;
    }
}

void probabilidadeRecuperacao(pessoast multidoes,int total_pessoas){
    
    int i,aux;
    float taxa;
    char aux_estado;
    pessoast head_pessoas = multidoes;
    for(i = 0,aux = 0; i < total_pessoas;i++){

        if (head_pessoas->estado == 'D') {
            taxa = 1.0 / head_pessoas->idade;
            
            aux = probEvento(taxa);                                             //PROBABILIDADE DE SE RECUPERAR APOS 1 ITERAÇÃO
            if (aux == 1) {
                head_pessoas->dias = 0;                                           //Reseta os dias de infeçao
                aux_estado = head_pessoas->estado;
                head_pessoas->estado = taxaImunidade(aux_estado);                 //VERIFICA SE SE TORNA IMUNE OU SAUDAVEL
            }
        }
        
        head_pessoas = head_pessoas->seguinte;
    }
}

char taxaImunidade(char aux_estado){
    
    int aux;   
    aux = probEvento(0.20);             //PROBABILIDADE DE IMUNIDADE = 20%
    if(aux == 1)                        //CASO AUX DEVOLVA 1 A PESSOA FICA IMUNE    
        aux_estado = 'I'; 
    else
        aux_estado = 'S';
    return aux_estado;                  //DEVOLVE O NOVO ESTADO DO DOENTE
}
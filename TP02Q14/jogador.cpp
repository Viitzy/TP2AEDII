#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMENTRADA 1000
#define TAMLINHA 1000
int comp = 0;


typedef struct Jogador{
    int id, altura, peso, anoNascimento;
    char nome[100], universidade[100], cidadeNascimento[100], estadoNascimento[100];
}Jogador;

bool isFim(char s[]){
    return (strlen(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M');
}

void ler(Jogador *j, char player[]){
    j->id = atoi(strsep(&player,","));

    strcpy(j->nome, strsep(&player , ","));    

    j->altura = atoi(strsep(&player,","));    

    j->peso = atoi(strsep(&player,","));    

    strcpy(j->universidade, strsep(&player , ","));
    if(strcmp(j->universidade, "")==0)
        strcpy(j->universidade, "nao informado");

    j->anoNascimento = atoi(strsep(&player,",")); 
    
    strcpy(j->cidadeNascimento, strsep(&player , ","));
    if(strcmp(j->cidadeNascimento, "")==0)
        strcpy(j->cidadeNascimento, "nao informado");
    
    for(int i=0; i<strlen(player); i++){
        if(player[i]=='\n'){
           player[i]='\0';
        }   
    }
    strcpy(j->estadoNascimento, player);
    if(strcmp(j->estadoNascimento, "")==0)
        strcpy(j->estadoNascimento, "nao informado");
    
}

void imprimir(Jogador *i){
    printf("[%i ## %s ## %i ## %i ## %i ## %s ## %s ## %s]\n",i->id ,i->nome , i->altura, i->peso, i->anoNascimento, i->universidade, i->cidadeNascimento, i->estadoNascimento);
}

void log(long cronometro){
    FILE *arq;
    arq = fopen("677213_radixsort.txt","w");
    fprintf(arq,"677213\t%ld\t%d",cronometro,comp);
    fclose(arq);
}

void radixsort(Jogador vetor[], int tamanho) {
    int i;
    Jogador maior = vetor[0];
    int exp = 1;

    Jogador b[tamanho];

    for (i = 0; i < tamanho; i++) {
        if (vetor[i].id > maior.id){
    	    maior = vetor[i];
            comp++;
        }
    }

    while (maior.id/exp > 0) {
        comp++;
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i].id / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i].id / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

}

int main(){
    char entrada[NUMENTRADA][TAMLINHA];
    int numEntrada = 0;
    
    do{
        fgets(entrada[numEntrada],TAMLINHA, stdin);
    }while(isFim(entrada[numEntrada++]) == false);
    numEntrada--;
    
    
    char players[3923][200];
    int numLinha = 0;
    
    FILE * fPointer;
        fPointer = fopen("/tmp/players.csv", "r");   

        do{
            fgets(players[numLinha],200,fPointer);  
            numLinha++; 
        }while(numLinha<3923);
                

        fclose(fPointer);

        Jogador jogador[numEntrada];
        int pos[numEntrada];

        for(int i= 0; i < numEntrada; i++){
            ler(&jogador[i] , players[atoi(entrada[i])+1]);
        }

        long tempo = clock();
        
        radixsort(jogador , numEntrada);

        tempo = clock() - tempo;
        log(tempo);

        for(int i= 0; i < numEntrada; i++){
            imprimir(&jogador[i]);
        }
    return 0;
}

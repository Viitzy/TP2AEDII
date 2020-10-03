#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMENTRADA 1000
#define TAMLINHA 1000
int comp;

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
    arq = fopen("677213_quicksort.txt","w");
    fprintf(arq,"677213\t%ld\t%d",cronometro,comp);
    fclose(arq);
}

void swap(int a, int b , Jogador array[]){
    Jogador aux = array[a];
    array[a] = array[b];
    array[b] = aux;
}

 void quicksort(int esq, int dir , Jogador array[]){
    int i = esq, j = dir;
    Jogador pivo = array[(dir+esq)/2];
    while (i <= j) {
        while (strcmp(array[i].estadoNascimento,pivo.estadoNascimento) < 0){ i++; comp++;}
        while (strcmp(array[j].estadoNascimento,pivo.estadoNascimento) > 0){ j--; comp++;}
        if (i <= j) {
            swap(i, j , array);
            i++;
            j--;
        }
    }
    if (esq < j)  
        quicksort(esq, j, array);
    if (i < dir)  
        quicksort(i, dir, array);
}

int main(){
    char entrada[NUMENTRADA][TAMLINHA];
    int numEntrada = 0;
    comp = 0;
    
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
        quicksort(0, (numEntrada-1), jogador);
        tempo = clock() - tempo;
        log(tempo);
            for (int i = (numEntrada - 1); i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if ((strcmp(jogador[j].nome,jogador[j + 1].nome) > 0) && (strcmp(jogador[j].estadoNascimento,jogador[j + 1].estadoNascimento) == 0)) {
                    Jogador a = jogador[j];
                    jogador[j]=jogador[j+1];
                    jogador[j+1]=a;
                }
            }
        }

        for(int i= 0; i < numEntrada; i++){
            imprimir(&jogador[i]);
        }
    return 0;
}

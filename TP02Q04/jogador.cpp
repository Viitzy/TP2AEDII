#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMENTRADA 1000
#define TAMLINHA 1000
int comp;

typedef struct{
    int id, altura, peso, anoNascimento;
    char nome[100], universidade[100], cidadeNascimento[100], estadoNascimento[100];
}Jogador;

bool isFim(char s[]){
    return (strlen(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M');
}

void ler(Jogador *j, char player[]){
    j->id = atoi(strsep(&player,","));

    strcpy(j->nome, strsep(&player , ","));
    char tratarnome[30]; 
    strcpy(tratarnome , j->nome);
    for(int i = 0; i<strlen(tratarnome);i++)
        if(tratarnome[i]== '*')
            tratarnome[i] = '\0';
    strcpy(j->nome, tratarnome);
            

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
    arq = fopen("677213_binaria.txt","w");
    fprintf(arq,"677213\t%ld\t%d",cronometro,comp);
    fclose(arq);
}

int PesquisaBinaria (Jogador vet[], char chave[], int Tam)
{
     int inf = 0;     // limite inferior (o primeiro índice de vetor em C é zero          )
     int sup = Tam-1; // limite superior (termina em um número a menos. 0 a 9 são 10 números)
     int meio;
     
     while (inf <= sup)
     {
          meio = (inf + sup)/2;
          //printf("%s", vet[meio].nome);
          if (strcmp(chave , vet[meio].nome) == 0){
               comp++;
               return 1;
               inf = sup;
          }
          if (strcmp(chave , vet[meio].nome) < 0){
               sup = meio-1;
               comp++;
          }else
               inf = meio+1;
     }
     
     return 0;   // não encontrado
}

int main(){
    char entrada[NUMENTRADA][TAMLINHA];
    char nomes[NUMENTRADA][TAMLINHA];
    int numEntrada = 0;
    int numNomes = 0;
    comp = 0;
    
    do{
        fgets(entrada[numEntrada],TAMLINHA, stdin);
    }while(isFim(entrada[numEntrada++]) == false);
    numEntrada--;

    do{
        fgets(nomes[numNomes],TAMLINHA, stdin);
    }while(isFim(nomes[numNomes++]) == false);
    numNomes--;

    for(int j = 0; j<numNomes ; j++){
        for(int i=0; i<strlen(nomes[j]); i++){
            if(nomes[j][i]=='\n'){
                nomes[j][i]='\0';
            }   
        }
    }
    
    
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

        
        for (int i = (numEntrada - 1); i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (strcmp(jogador[j].nome,jogador[j + 1].nome) > 0) {
                    Jogador a = jogador[j];
                    jogador[j]=jogador[j+1];
                    jogador[j+1]=a;
                }
            }
        }


        long tempo = clock();
        for(int i= 0; i < numNomes; i++){
            if (PesquisaBinaria(jogador , nomes[i] , numEntrada) == 1)
                printf("SIM\n");
            else
            {
                printf("NAO\n");
            }
        }
        tempo = clock() - tempo;
        log(tempo);

    return 0;
}

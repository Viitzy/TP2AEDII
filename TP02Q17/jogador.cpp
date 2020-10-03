#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMENTRADA 1000
#define TAMLINHA 1000
int comp = 0;
int tam = 0;

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
    arq = fopen("677213_heapsortParcial.txt","w");
    fprintf(arq,"677213\t%ld\t%d",cronometro,comp);
    fclose(arq);
}

void swap(Jogador vet[], int pos1, int pos2){
	Jogador aux = vet[pos2];
	vet[pos2] = vet[pos1];
	vet[pos1] = aux;
}

void add_to_heap(Jogador vet_heap[], int n, Jogador x){
	int pos_x = tam;
    vet_heap[tam] = x;
    tam++;
	while(pos_x > 0){
		if(vet_heap[(pos_x-1)/2].altura < vet_heap[pos_x].altura){
            comp++;
			swap(vet_heap, (pos_x-1)/2, pos_x);
			pos_x = (pos_x-1)/2;
		}else{
			pos_x = -1;
		}
	}
}

Jogador remove_from_heap(int n, Jogador vet_heap[]){
	Jogador removido = vet_heap[0];
	int i = 0;
	int pos;
	vet_heap[0] = vet_heap[--tam];
	
	while(i < ((n-1)/2)){
		if(vet_heap[i].altura < vet_heap[2*i+1].altura || vet_heap[i].altura < vet_heap[2*i+2].altura){
            comp+=2;
			pos = vet_heap[2*i+1].altura > vet_heap[2*i+2].altura ? 2*i+1 : 2*i+2;
			swap(vet_heap, i, pos);
			i = pos;
		}else{
			i+=n;
		}
	}
	return removido;
}

void heap(Jogador vet[], int n){
    Jogador vet_heap[n];
		
	for(int i = 0; i< n; i++)
		add_to_heap(vet_heap, n, vet[i]);

	for(int i= n-1; i>=0; i--)
	    vet[i] = remove_from_heap(n--, vet_heap);
	
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
        
        heap(jogador , numEntrada);

        tempo = clock() - tempo;
        log(tempo);

        for (int i = (numEntrada - 1); i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (( jogador[j].altura > jogador[j + 1].altura )||((strcmp(jogador[j].nome,jogador[j + 1].nome) > 0) && jogador[j].altura == jogador[j + 1].altura)) {
                    Jogador a = jogador[j];
                    jogador[j]=jogador[j+1];
                    jogador[j+1]=a;
                }
            }
        }

        for(int i= 0; i < 10; i++){
            imprimir(&jogador[i]);
        }
    return 0;
}

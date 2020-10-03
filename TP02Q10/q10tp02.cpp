#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale>
#include <time.h>
#define NUMENTRADA 2000
#define TAMLINHA 2000
#define TAM_ATRIBUTOS 200
#define TAM_CONTEUDO 2000

typedef struct Jogador{
    int id;
    char nome[TAM_ATRIBUTOS];
    int altura;
    int peso;
    char universidade[TAM_ATRIBUTOS];
    int anoNascimento;
    char cidadeNascimento[TAM_ATRIBUTOS];
    char estadoNascimento[TAM_ATRIBUTOS];
}Jogador;

bool isFim(char* s){
	return(strlen(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M') ;
}
static char *replace(char *in,const char *pattern,const char *by){
    size_t outsize = strlen(in) + 1;
    char *res = (char*)malloc(outsize);
    size_t resoffset = 0;

    char *needle;
    while (needle = strstr(in, pattern)) {
        memcpy(res + resoffset, in, needle - in);
        resoffset += needle - in;

        in = needle + strlen(pattern);

        outsize = outsize - strlen(pattern) + strlen(by);
        res = (char*)realloc(res, outsize);

        memcpy(res + resoffset, by, strlen(by));
        resoffset += strlen(by);
    }

    strcpy(res + resoffset, in);

    return res;
}

void implementacao (Jogador* s,char* result){
    char* resp = (char*) malloc(TAM_CONTEUDO*sizeof(char));
    char *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8;
    strcpy(resp,replace(result,",,",",nao informado,"));

    t1 = strsep(&resp, ",");
    t2 = strsep(&resp, ",");
    t3 = strsep(&resp, ",");
    t4 = strsep(&resp, ",");
    t5 = strsep(&resp, ",");
    t6 = strsep(&resp, ",");
    t7 = strsep(&resp, ",");
    t8 = strsep(&resp, ",");
    if(t8[strlen(t8)-1] == '\n')t8[strlen(t8)-1]= '\0';
    if(t7[0] == 'n' && t7[1]=='a')strcpy(t8,"nao informado");

    s->id = atoi(t1);
    strcpy(s->nome,t2);
    s->altura = atoi(t3);
    s->peso = atoi(t4);
    strcpy(s->universidade,t5);
    s->anoNascimento = atoi(t6);
    strcpy(s->cidadeNascimento,t7);
    strcpy(s->estadoNascimento,t8);

    free(resp);
}
void ler (Jogador* s,char* idEntrada){
    FILE *arq;
    char linha[TAM_CONTEUDO];
    char* result = (char*) malloc(TAM_CONTEUDO*sizeof(char));
    arq = fopen("/tmp/players.csv","r");

    if(arq != NULL){
        int i = 0;
        while (i<3923 && i != 9999){
            result = fgets(linha, 2000, arq);
            if(i == atoi(idEntrada)+1){
                implementacao(s,result);
                i = 9998;            
            }
            i++;
        }
    }
    else{
        printf("PERSONAGEM NAO ESTA EM TEMP.\n");
    }
    fclose(arq);   
}

void imprimir(Jogador* s){
    printf("[%d ##",s->id);
    printf(" %s ##",s->nome);
    printf(" %d ##",s->altura);
    printf(" %d ##",s->peso);   
    printf(" %d ##",s->anoNascimento);
    printf(" %s ##",s->universidade);
    printf(" %s ##",s->cidadeNascimento);
    printf(" %s]\n",s->estadoNascimento);
}

void swap(int a, int b, Jogador jog[]){
    Jogador aux = jog[a];
    jog[a] = jog[b];
    jog[b] = aux;
}

void quicksortRec(Jogador jog[],int esq, int dir){
    int cont = 0;

    int i = esq, j = dir;
    Jogador pivo = jog[(dir+esq)/2];
    while (i <= j) {
        while (strcmp(jog[i].universidade,pivo.universidade) < 0) i++;
        while (strcmp(jog[j].universidade,pivo.universidade) > 0) j--;
        if (i <= j) {
            swap(i, j,jog);
            i++;
            j--;
        }
    }
    if (esq < j) quicksortRec(jog, esq, j);
    if (i < dir) quicksortRec(jog, i, dir);
    
}
void log(const char* matricula,long cronometro, int nComparacoes){
    FILE *arq;
    arq = fopen("matricula_quicksort.txt","w");
    fprintf(arq,"Matricula: %s  Tempo(ns): %ld Comparações: %d",matricula,cronometro,nComparacoes);
    fclose(arq);
}

int main(){
    setlocale(LC_CTYPE, "");

    long start = clock();
    int comp = 0;
    char entrada[NUMENTRADA][TAMLINHA];
    int numEntrada = 0;
	do{
		fgets(entrada[numEntrada], TAMLINHA, stdin);
        if(entrada[numEntrada][strlen(entrada[numEntrada])-1] == '\n')entrada[numEntrada][strlen(entrada[numEntrada])-1] = '\0';
	}while(isFim(entrada[numEntrada++]) == false);
	numEntrada--;
    Jogador jog[numEntrada];

	for(int i = 0;i < numEntrada;i++){
        ler(&jog[i], entrada[i]);
    }
    quicksortRec(jog,0,numEntrada-1);
    
    for(int i = 0;i < numEntrada;i++){
       imprimir(&jog[i]);
    }
    long elapsed = clock();
    long tempoTotal = elapsed - start;
    log("647822",tempoTotal,comp);
	return 0;
}
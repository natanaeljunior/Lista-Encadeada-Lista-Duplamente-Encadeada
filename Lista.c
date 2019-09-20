#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
///////// ESTRUTURAS //////////////

typedef struct cliente{
	int id;
	char nome[80];
	char valor[80];
}TCliente;

typedef struct noCliente {
	TCliente cliente;
	struct noCliente* prox;		
}NoCLiente;

typedef struct noClienteRef {
	NoCLiente * clienteRef;
	struct noClienteRef* prox;
	struct noClienteRef* ant;		
}NoCLienteRef;

typedef struct list {
	int size;
	void * head;
	void * fim;
}TList;

////// DECLARAÇÃO DE FUNÇÕES //////
TList* createList();
void add(TList* list, TCliente cliente);
void lerarquivo(TList* listaCliente);
void quebraStr(TList* listaCliente,char string[100]);
void del(TList* listaCliente);
void ordenarLista(TList* listaOriginal, TList* listaDestino, int opOrdena);
void bubbleSort(TList* listaCliente) ;
void geraDadosCsv(TList* listaCliente, char TCSV[30]);

///////// FUNÇÕES ////////////////

TList* createList(){
	TList* listCliente = (TList*)malloc(sizeof(TList));
	
	listCliente->size = 0;
	listCliente->head = NULL;		 
	
	return listCliente;
}

void geraDadosCsv(TList* listaCliente, char TCSV[30]){


		FILE * arquivoCsv;
			
            arquivoCsv = fopen(TCSV, "r");
            if(arquivoCsv==NULL)
            {
	 			arquivoCsv = fopen(TCSV, "w");
                printf("Arquivo CSV criado! \n\n");
                
            } 

	    arquivoCsv=fopen(TCSV,"w"); 

     	NoCLienteRef* aux = listaCliente->head;
     	bool i=true;
	while(aux!= NULL){
		if(i==true){
		 fprintf(arquivoCsv,"id;nome;saldo\n");
		 i=false;
		}
		 fprintf(arquivoCsv,"%d;%s;%s", aux->clienteRef->cliente.id, aux->clienteRef->cliente.nome, aux->clienteRef->cliente.valor);
		 aux = aux->prox;
	}
     	             
     printf("\n Arquivo CSV gerado com sucesso!\n");     
	 
	 fclose(arquivoCsv);  
	
}

bool listaVazia(TList* listaCliente){
	return (listaCliente->size ==0);
}

void add(TList* listaCliente, TCliente cliente){
	NoCLiente* noCliente = (NoCLiente*) malloc(sizeof(NoCLiente));
	
	
	noCliente->cliente = cliente;
	noCliente->prox = listaCliente->head;
	
	listaCliente->head = noCliente;
	
	if(listaCliente->size ==0){
		listaCliente->fim = noCliente;
	}
	listaCliente->size++; 	
}

void addRef(TList* listaCliente, NoCLiente * clienteRef){
	NoCLienteRef* noClienteRef = (NoCLienteRef*) malloc(sizeof(NoCLienteRef));
	
	NoCLienteRef * aux = listaCliente->head;
	noClienteRef->clienteRef = clienteRef;
	noClienteRef->prox = listaCliente->head;
	noClienteRef->ant = NULL;
	listaCliente->head = noClienteRef;
	
		if(listaCliente->size !=0){
		aux->ant = noClienteRef;
		listaCliente->head = noClienteRef;
	}
	
	if(listaCliente->size ==0){
		listaCliente->fim = noClienteRef;
	}
	listaCliente->size++; 
				
}

void del(TList* listaCliente){
	
NoCLiente *no = listaCliente->head, *aux;
    while (no != NULL)
    {
        aux = no;
        no = no->prox;
        free (aux);
    }
    listaCliente->size  = 0;
    listaCliente->head = NULL;
}

void lerArquivo(TList* listaCliente){
	
  FILE *arqTxt;
  char Linha[100];
  char *result;
  int i;
 
  // Abre um arquivo TEXTO para LEITURA
  arqTxt = fopen("DadosBanco.txt", "rt");
 	
	if (arqTxt == NULL)
	{
	    printf("Problemas na LEITURA do arquivo\n");
	    return;
	}else{
		printf("\n LEITURA DO ARQUIVO OK! \n");
	}
	
  i = 1;
  while (!feof(arqTxt))
  {

     result =  fgets(Linha, 100, arqTxt);
      if (result) {
     	quebraStr(listaCliente, Linha);	
	  }
      
      i++;
  }
  
  fclose(arqTxt);
  printf(" \n DADOS INSERIDOS COM SUCESSO!\n");
   
}

void imprimeLista(TList* listaCliente ){
		
	if(listaVazia(listaCliente)){
		printf("LISTA VAZIA! \n");
		return;
	}
	
	NoCLiente* aux = listaCliente->head;
	printf("\n===============================================");
	while(aux!= NULL){
		printf("\n %d - %s - %s", aux->cliente.id, aux->cliente.nome, aux->cliente.valor);
		aux = aux->prox;
	}
	printf("\n===============================================");
	printf("\n");
}

void imprimeListaRef(TList* listaCliente ){
		
	if(listaVazia(listaCliente)){
		printf("LISTA VAZIA! \n");
		return;
	}
	
	NoCLienteRef* aux = listaCliente->head;
	printf("\n===============================================");
	while(aux!= NULL){
	
		printf("\n %d - %s - %s", aux->clienteRef->cliente.id, aux->clienteRef->cliente.nome, aux->clienteRef->cliente.valor);
		
		aux = aux->prox;
	}
	printf("\n===============================================");
	printf("\n");
}

void quebraStr(TList* listaCliente,char string[100]){
	
	
    char v[3][80];
	
   TCliente cliente;
   const char s[2] = "|";
   char* strQuebrada;
   
 	int i = 0;
   strQuebrada = strtok(string, s);
	 
   while( strQuebrada != NULL ) {

    	if(i==0){
    		cliente.id = atoi(strQuebrada);
		}else
		if(i==1){
			 sprintf(cliente.nome, "%s", strQuebrada);
		}else
		if(i==2){
			sprintf(cliente.valor, "%s", strQuebrada);	
		}
	    i++;
	   
      strQuebrada = strtok(NULL, s);

   }
   
     add(listaCliente, cliente);
}

void setListRef(TList* listaOriginal, TList* listaDestino){
	
	 if(listaVazia(listaOriginal)){
		printf("LISTA ORIGINAL VAZIA! \n");
		return;
	}
	
	if(!listaVazia(listaDestino)){
	
		while(listaDestino->size!=0){
			
		del(listaDestino);
		
	}
	listaDestino->size = 0;
	listaDestino->head = NULL;
	}
	
	NoCLiente* aux = (NoCLiente*) malloc(sizeof(NoCLiente));
 	aux  = listaOriginal->head;
 
	while(aux != NULL){
					
				addRef(listaDestino, aux);
					aux = aux->prox;
	}
	free(aux);

	
}

void bubbleSort(TList* listaCliente) {  

	if(listaCliente->size ==0){
		printf("\n LISTA VAZIA! \n");
		return;
	}
	
	NoCLienteRef* aux_cli = listaCliente->head;
		
		while (aux_cli != NULL ){
				NoCLienteRef* aux_cli2 = aux_cli->prox;
		    while (aux_cli2 != NULL ){
		    
		      if ( strcmp(  aux_cli->clienteRef->cliente.nome,  aux_cli2->clienteRef->cliente.nome)>0){ 
		      
		       			   NoCLiente * temp = aux_cli->clienteRef;   			   
		       			   aux_cli->clienteRef = aux_cli2->clienteRef;
		       			   aux_cli2->clienteRef = temp;
		        }
				aux_cli2 = aux_cli2->prox;
		    }
			aux_cli = aux_cli->prox;  
		}

}


NoCLienteRef *partition (NoCLienteRef *inicio, NoCLienteRef * fim){
	NoCLienteRef * esq = inicio; 
	NoCLienteRef * dir = fim;
	NoCLienteRef * pivot = inicio;
	

	while(inicio!=fim){
		while(atof( esq->clienteRef->cliente.valor) < atof( pivot->clienteRef->cliente.valor)){
			inicio  = inicio->prox;
			esq = esq->prox;			
		}
		while(atof(dir->clienteRef->cliente.valor) > atof(pivot->clienteRef->cliente.valor)){
			fim  = fim->ant;
			dir = dir->ant;			
		}
		
		if(atof(esq->clienteRef->cliente.valor) > atof(  dir->clienteRef->cliente.valor)){
			NoCLiente * temp = esq->clienteRef;
			esq->clienteRef = dir->clienteRef;
			dir->clienteRef = temp;
		}
		
	}
	
	inicio->clienteRef  =dir->clienteRef;
	dir->clienteRef = pivot->clienteRef;
	
	return dir;
	
}
void quickSort(NoCLienteRef* l, NoCLienteRef *h) 
{ 
	
     if(h!=NULL && h->prox!=l ){ 
    
        NoCLienteRef *p = partition(l, h); 
        quickSort(l, p->ant); 
        quickSort(p->prox, h); 
    } 
} 


int main(int argc, char *argv[]) {
		
	TList * listaOriginal = createList();
	TList * listaNome = createList();
	TList * listaSaldo = createList();
	
	clock_t TOrdenacao[2];
   
	
	TCliente cliente;

	int escolha=-1;

while (escolha!=0){

printf("\n\n =============================== ");

	printf("\n 1 - SET DADOS LISTA ORIGINAL ");
	printf("\n 2 - IMPRIMIR LISTA ORIGINAL");
	printf("\n 3 - SET DADOS LISTA NOME ");
	printf("\n 4 - IMPRIMIR LISTA NOME");
	printf("\n 5 - SET DADOS LISTA SALDO ");
	printf("\n 6 - IMPRIMIR LISTA SALDO");
	printf("\n 7 - ORDENA BUBBLESORT NOME");
	printf("\n 8 - ORDENA QUICKSORT SALDO");
	printf("\n 9 - GERA CSV NOME - SALDO");
	printf("\n 0 - SAIR");
	printf("\n\n Escolha uma opcao: ");
	scanf("%d",&escolha);

	switch (escolha) {

	case 1:
	{	system("cls");
	printf("\n SETA VALORES PARA LISTA - NOME \n");
		lerArquivo(listaOriginal);		
	break;
	}
	case 2:
	{	system("cls");
		printf("\n IMPRIME LISTA ORIGINAL \n");
		imprimeLista(listaOriginal);		
	break;
	}
	case 3:
	{	system("cls");
		printf("\n SETA VALORES PARA LISTA - NOME \n");
		setListRef(listaOriginal,listaNome);		
	break;
	}
	case 4:
	{	system("cls");
		printf("\n IMPRIME LISTA NOME \n");
		imprimeListaRef(listaNome);		
	break;
	}
	case 5:
	{	system("cls");
		printf("\n SETA VALORES PARA LISTA - SALDO \n");
		setListRef(listaOriginal,listaSaldo);		
	break;
	}
	case 6:
	{	system("cls");	
		printf("\n IMPRIME LISTA SALDO \n");
		imprimeListaRef(listaSaldo);		
	break;
	}
	case 7:
	{	system("cls");
		printf(" \n ORDENA - BUBBLESORT - NOME ");
		TOrdenacao[0] = clock();
		bubbleSort(listaNome);
		TOrdenacao[1] = clock();
  		printf("\n TEMPO ORDENACAO : BUBBLESORT %f", (TOrdenacao[1] - TOrdenacao[0]) * 1000.0 / CLOCKS_PER_SEC);
		printf("\n================================");
	
	break;
	}
	case 8:
	{	system("cls");
	
		if(listaSaldo->size ==0){
		printf("\n LISTA VAZIA! \n");
	}else{
		printf(" \n ORDENA - QUICKSORT - SALDO ");
		TOrdenacao[0] = clock();
		quickSort(listaSaldo->head, listaSaldo->fim);
		TOrdenacao[1] = clock();
 		printf("\n TEMPO ORDENACAO : QUICKSORT %f", (TOrdenacao[1] - TOrdenacao[0]) * 1000.0 / CLOCKS_PER_SEC);
		printf("\n================================");	
	
	}
	break;
	}
	case 9:
	{	system("cls");
		 	printf("\n GERA DADOS CSV LISTA NOME \n");
			geraDadosCsv(listaNome,"NomeCSV.csv");
	
			printf("\n GERA DADOS CSV LISTA SALDO \n");
	
			geraDadosCsv(listaSaldo,"SaldoCSV.csv");
	break;
	}
	
	}
}


	return 0;
}

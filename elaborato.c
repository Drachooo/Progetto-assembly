/*
  Algoritmo di ordinamento naive sort

  100 unità di tempo
  10 prodotti
*/

#include <stdio.h>
#define N 2

struct struct_prodotto{
  int identificativo;
  int durata;
  int scadenza;
  int priorita;
}prodotto[N], supporto;


void edf(); //priorità alla scadenza più vicina, se = si guarda la priorità
void hpf(); //priorità alla priorità più alta, se = si guarda scadenza


int main(){
  
  //10 prodotti
  int i;
  int scelta=0;
  
  for(i=0; i<N; i++){
    printf("%d^ Prodotto:\n", i+1);
    
    printf("Identificativo: ");
    scanf("%d", &prodotto[i].identificativo);
    printf("Durata: ");
    scanf("%d", &prodotto[i].durata);
    
    printf("Scadenza: ");
    scanf("%d", &prodotto[i].scadenza);
    printf("Priorità: ");
    scanf("%d", &prodotto[i].priorita);
    printf("\n");
  }
  
  printf("Quale metodo di ordinamento vuoi usare?: ");
  scanf("%d", &scelta);
  
  if(scelta==1)
    edf();
  else
    hpf();

  
  printf("\n");
}




void edf(){  //priorità alla scadenza più vicina, se = si guarda la priorità
  
  int i, j;
  int min=100;
  int priorita=0;
  int check=0;
  int posizione=0;
  int tempo[N+1];
  tempo[0]=0;
  int ritardo=0;
  int penalita=0;

  //stampa acquisizione
  printf("Vettore acquisito:\n");
  for(i=0; i<N; i++){
    printf("%d-%d || ", prodotto[i].scadenza, prodotto[i].priorita);
  }

  
  printf("\n\n");
  printf("Vettore ordinato:\n");
  for(j=0; j<N; j++){
    for(i=j; i<N; i++){
      
      //cerco il prodotto con scadenza minore
      if(min>prodotto[i].scadenza){
	min=prodotto[i].scadenza;    //
	priorita=prodotto[i].priorita; //
	check=0;
	posizione=i;
	printf("\nMINIMO: %d, Priorità: %d\n", min, priorita);
      }
      
      //caso in cui ce ne sia uno uguale al minimo, viene controllata la priorità più alta
      if(check==1 && min==prodotto[i].scadenza) //
	if(prodotto[i].priorita>priorita){ //
	  min=prodotto[i].scadenza;  
	  priorita=prodotto[i].priorita;
	  posizione=i;
	  printf("\nMINIMO IF: %d, Priorità: %d\n", min, priorita);
	} //
      
      check=1;
    }
    //uscendo da qua, abbiamo trovato il minimo

    //scambio di posizioni tra il minimo e la prima posizione libera
    supporto=prodotto[j];
    prodotto[j]=prodotto[posizione];
    prodotto[posizione]=supporto;
    
    //azzeramento variabili
    min=100;
    check=0;
    priorita=0;
  }
 
  for(i=0; i<N; i++)
    //stampa ordinato
    printf("%d-%d || ", prodotto[i].scadenza, prodotto[i].priorita);


  
  printf("\n\n");
  
  //stampa coso ordinato
  for(i=1; i<=N; i++){
    tempo[i]=tempo[i-1]+prodotto[i-1].durata;

    if(tempo[i]-prodotto[i-1].scadenza>0)
      penalita=((tempo[i]-prodotto[i-1].scadenza)*prodotto[i-1].priorita)+penalita;
  }

  for(i=0; i<N; i++)
    printf("ID: %d - Tempo: %d\n", prodotto[i].identificativo, tempo[i]);

  
  printf("Conclusione: %d", tempo[N]);
  printf("\nPenalità: %d", penalita);
}

/*******************************************************************************/


void hpf(){  //priorità alla priorità più alta, se = si guarda scadenza
  
  int i, j;
  int max=0;
  int scadenza=0;
  int check=0;
  int posizione=0;
  int tempo[N+1];
  tempo[0]=0;
  int ritardo=0;
  int penalita=0;

  //stampa acquisizione
  printf("Vettore acquisito:\n");
  for(i=0; i<N; i++){
    printf("%d-%d || ", prodotto[i].priorita, prodotto[i].scadenza);
  }
  
  printf("\n\n");
  printf("Vettore ordinato:\n");
  for(j=0; j<N; j++){
    for(i=j; i<N; i++){
      
      //cerco il prodotto con scadenza minore
      if(max<prodotto[i].priorita){
	max=prodotto[i].priorita;
	scadenza=prodotto[i].scadenza;
	check=0;
	posizione=i;
	//printf("\nMINIMO: %d, Priorità: %d\n", min, priorita);
      }
      
      //caso in cui ce ne sia uno uguale al minimo, viene controllata la priorità più alta
      if(check=1 && max==prodotto[i].priorita)
	if(prodotto[i].scadenza<scadenza){
	  max=prodotto[i].priorita;
	  scadenza=prodotto[i].scadenza;
	  posizione=i;
	  printf("\nMINIMO IF: %d, Priorità: %d\n", max, scadenza);
	}
      
      check=1;
    }
    //uscendo da qua, abbiamo trovato il minimo

    supporto=prodotto[j];
    prodotto[j]=prodotto[posizione];
    prodotto[posizione]=supporto;
    
    //azzeramento variabili
    max=100;
    check=0;
    scadenza=0;
  }
 
  for(i=0; i<N; i++)
    //stampa ordinato
    printf("%d-%d || ", prodotto[i].priorita, prodotto[i].scadenza);

  printf("\n\n");
  
  for(i=1; i<=N; i++){
    tempo[i]=tempo[i-1]+prodotto[i-1].durata;

    if(tempo[i]-prodotto[i-1].scadenza>0)
      penalita=((tempo[i]-prodotto[i-1].scadenza)*prodotto[i-1].priorita)+penalita;
  }

  for(i=0; i<N; i++)
    printf("ID: %d - Tempo: %d\n", prodotto[i].identificativo, tempo[i]);

  
  printf("Conclusione: %d", tempo[N]);
  printf("\nPenalità: %d", penalita);
}

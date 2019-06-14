//
//  main.c
//  GRAFI
//
//  Created by Marco Del Giudice on 22/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "grafo.h"
#include "matrice.h"
#include "coda.h"

void stampa_menu1(void);
GRAFO* gestisci_menu1(int scelta, GRAFO *grafo);
void setta_grafo(GRAFO *grafo);
int scegli_indice(GRAFO *grafo);
int *scegli_arco(GRAFO *grafo);
float scegli_peso (void);

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    GRAFO *grafo=NULL;
    int rnd=0;
    grafo=alloca_grafo(grafo);
    setta_grafo(grafo);
    printf("\nscegli come realizzare l'albero\n1-inizializza grafo     2-grafo casuale\n");
    scanf("%d",&rnd);
    if(rnd==1){
        inizializza_grafo(grafo);
    }else{
        int n=1+(rand()%(10-1+1));
        int e=1+(rand()%(10-1+1));
        grafo_casuale(grafo, n, e);
    }
    int scelta=1;
    while (scelta!=0){
        stampa_menu1();
        scanf("%d",&scelta);
        grafo=gestisci_menu1(scelta, grafo);
    }
    return 0;
}

void stampa_menu1(){
    printf("\n___________________________________\n\n"
           "immetti un carattere per scegliere\n"
           "___________________________________\n");

    printf("\n1-stampa grafo\n2-aggiungi arco\n3-aggiungi vertice\n4-cancella arco\n5-cancella vertice\n6-percorso minimo\n7-controlla cicli\n8-ordinamento topologico\n9-visita in profondita\n10-visita in ampiezza\n11-converti struttura di rappresentazione\n12-genera grafo trasposto\n13-massimo sottografo\n0-nessuna operazione\n\n");
}

GRAFO *gestisci_menu1(int scelta, GRAFO *grafo){
    int i,y,path;
    int *arco;
    GRAFO *trasposto=NULL;
    NODO_L *ord=NULL;
    //float peso;
    switch(scelta){
        case 1:
            printf("\n___________________________________\n\n");
            stampa_grafo(grafo);
            printf("___________________________________\n\n");
            break;
        case 2:
            setta_arco(grafo);
            break;
        case 3:
            aggiungi_vertice(grafo);
            break;
        case 4:
            arco=scegli_arco(grafo);
            cancella_arco(grafo,arco[0],arco[1]);
            free(arco);
            break;
        case 5:
            i=scegli_indice(grafo);
            cancella_vertice(grafo,i);
            break;
        case 6:
            printf("\nscegli il tipo di percorso\n\n1-percoso di lunghezza minima\n2-percorso di peso minimo\n");
            scanf("%d",&path);
            arco=scegli_arco(grafo);
            percorso_minimo(grafo,arco[0], path, arco[1]);
            free(arco);
            break;
        case 7:
            y=dfs_aciclico(grafo);
            if(y==1){
                printf("c'è un ciclo\n");
            }else{
                printf("non ci sono cicli\n");
            }
            break;
        case 8:
            ord=ordinamento_top(grafo);
            stampa_ord_top(grafo, ord);
            break;
        case 9:
            dfs(grafo);
            break;
        case 10:{
            i=scegli_indice(grafo);
            int *pred=bfs(grafo, i);
            printf("array predecessori");
            for(int i=0;i<grafo->n;i++){
                printf("%d |",pred[i]);
            }
            free(pred);
        }
        case 11:
            grafo=converti(grafo);
            break;
        case 12:
            trasposto=grafo_trasposto(grafo);
            if(trasposto!=NULL){
                stampa_grafo(trasposto);
                elimina_grafo(trasposto);
            }else{
                printf("\nil grafo deve essere orientato\n");
            }
            break;
        case 13:
            massimo_sottografo(grafo);
            break;
        case 0:
            elimina_grafo(grafo);
            break;
        default:
            printf("errore input.. riprova\n");
            break;
    }
    return grafo;
}

void setta_grafo(GRAFO *grafo) {
    int matorlist,tipo,oriented;
    printf("\n___________________________________\n\n"
           "   Imposta l'heap da realizzare\n"
           "___________________________________\n\n");
    printf("\nscegli come rappresentarlo\n\n1. MATRICE\n2. LISTE\n");
    scanf("%d",&matorlist);
    printf("\nscegli il tipo di grafo\n\n1-orientato       2-non orientato\n");
    scanf("%d",&oriented);
    printf("\nscegli il tipo di valore da inserire\n\n1-intero       2-float\n3-stringa      4-struct\n");
    scanf("%d",&tipo);
    if(tipo<1 || tipo >4){
        printf("selezione tipo errata!");
    }
    grafo=imposta_grafo(tipo, matorlist, oriented, grafo);
    
}

int scegli_indice(GRAFO *grafo){
    int i=-1;
    stampa_array_vertici(grafo);
    while(i<0 || i>grafo->n){
        printf("\nscegli il vertice : ");
        scanf("%d",&i);
    }
    return i;
}

int *scegli_arco(GRAFO *grafo){
    int *arco=malloc((sizeof(int)*3));
    arco[0]=-1;
    arco[1]=-1;
    stampa_array_vertici(grafo);
    while(arco[0]>grafo->n || arco[0]<0){
    printf("\nscegli il vertice di partenza: ");
    scanf("%d",&arco[0]);
    }
    while(arco[1]>grafo->n || arco[1]<0){
    printf("\nscegli il vertice di arrivo: ");
    scanf("%d",&arco[1]);
    }
    return arco;
}

float scegli_peso () {
    float peso;
    printf("\nscegli il peso dell'arco: ");
    scanf("%f",&peso);
    return peso;
}

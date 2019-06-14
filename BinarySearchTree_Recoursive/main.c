//
//  main.c
//  LASD
//
//  Created by Marco Del Giudice N86001422.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "abr.h"
#include "lista.h"
#include "callback.h"


void stampa_menu1(void);
void stampa_menu2(LISTA *alb_curr);
LISTA *gestisci_menu1(int scelta, LISTA *alberi);
LISTA *gestisci_menu2(int scelta, LISTA *alb_curr , LISTA *alberi);
LISTA *inserimento_casuale (int n, LISTA *alb_curr,CMPDATA cmp ,ALLOCA all);
void stampa_array (void ** array, int max, GETOUT print);

int main(int argc, const char * argv[]) {
    
    LISTA *alberi=NULL;
    LISTA *alb_curr=NULL;
    int scelta1=1;
    int scelta2=1;
    srand(time(NULL));
    printf("\n___________________________________\n\n");
    printf(" MARCO DEL GIUDICE N86001422");
    printf("\n___________________________________\n\n");
    
    
    while (scelta1!=0){
        stampa_menu1();
        scanf("%d",&scelta1);
        if (scelta1!=3){
            alberi=gestisci_menu1(scelta1, alberi);
        }else {
            alb_curr=gestisci_menu1(scelta1, alberi);
        }
        if (scelta1==3 && alb_curr!=NULL){
            scelta2=1;
            while (scelta2!=0){
                stampa_menu2(alb_curr);
                scanf("%d",&scelta2);
                alberi=gestisci_menu2(scelta2, alb_curr, alberi);
                if (scelta2==6){
                    scelta2=0;
                }
            }
        }
        
    }
    return 0;
}

void stampa_menu2(LISTA *alb_curr){
    printf("\n___________________________________\n\n");
    printf("stai operando sull'albero %s",alb_curr->nome);
    if (alb_curr->tipo==0){
        printf(" - intero\n");
    }else if (alb_curr->tipo==1){
        printf(" - float\n");
    }else if (alb_curr->tipo==2){
        printf(" - string\n");
    }else {
        printf(" - struct\n");
    }
    printf("\n___________________________________\n\n"
           "immetti un carattere per scegliere\n"
           "___________________________________\n\n1-inserimento nodo\n2-inserisci n nodi casuali\n3-cancella un nodo\n4-cancella nodi con condzione\n5-stampa\n6-elimina intero albero\n7-duplica albero\n8-confronta alberi\n9-costruisci array ordinato\n10-bilancia albero\n0-nessuna operazione\n");
}

void stampa_menu1(){
    printf("\n___________________________________\n\n"
           "immetti un carattere per scegliere\n"
           "___________________________________\n\n1-stampa lista degli alberi\n2-crea nuovo albero\n3-scegli albero su cui operare\n0-nessuna operazione\n\n");
}

LISTA *gestisci_menu1(int scelta, LISTA *alberi){
    char* str=malloc((sizeof(char))*20);
    int tipo;
    LISTA* tmp=NULL;
    switch (scelta){
        case 3:
            //SCEGLI ALBERO
            printf("gli alberi esistenti sono : \n");
            printf("\n___________________________________\n\n");
            stampa_lista(alberi);
            printf("\n___________________________________\n\n");
            printf("inserisci il nome dell'albero su cui operare\n");
            scanf("%s",str);
            alberi = estrai_lista(alberi, str);
            if (alberi==NULL){
                printf("\nalbero scelto non esistente!\n");
            }
            break;
        case 2:
            //CREA ALBERO
            printf("inserisci stringa per il nome del nuovo albero\n");
            scanf("%s",str);
            printf("inserisci il tipo di albero: \n0-intero       1-float\n2-stringa      3-struct\n");
            scanf("%d",&tipo);
            if(tipo != 0 && tipo != 1 && tipo!=2 && tipo!=3){
                printf("selezione tipo errata!");
                break;
            }
            tmp=estrai_lista(alberi, str);
            if (tmp==NULL){
                alberi = inserisci_in_lista(alberi, str, tipo);
                printf("creazione avvenuta! \n");
            }else {
                printf("\nun albero con questo nome è già esistente!\n");
            }
            break;
        case 1:
            //STAMPA
            stampa_lista(alberi);
        case 0:
            break;
        default:
            printf("errore input.. riprova\n");
            break;
    }
    free(str);
    return alberi;
}

LISTA *gestisci_menu2(int scelta, LISTA *alb_curr , LISTA *alberi){
    char *str=malloc((sizeof(char))*20);
    char *a=malloc((sizeof(char))*20);
    char *b=malloc((sizeof(char))*20);
    void ** array;
    void *val;
    CMPDATA cmp = NULL;
    ALLOCA all = NULL;
    GETOUT print=NULL;
    GETIN get=NULL,rnd=NULL;
    DEALLOCA deall=&DeallocaElem;
    COND cond=NULL;
    int p1,p2,p=0,n,x;
    int confronto;
    switch(alb_curr->tipo){
            
            
            
        case 0:
            get=&GetInputInt;
            cmp=&CmpInt;
            all=&AllocaIntero;
            rnd=&GetRandomInt;
            print=&StampaIntero;
            cond=&condint;
            break;
        case 1:
            get=&GetInputFloat;
            cmp=&CmpFloat;
            all=&AllocaFl;
            rnd=&GetRandomFloat;
            print=&StampaFloat;
            break;
            
        case 2:
            get=&GetInputString;
            cmp=&CmpString;
            all=&AllocaStringa;
            rnd=&GetRandomString;
            print=&StampaStringa;
            break;
        case 3:
            get=&GetInputStruct;
            cmp=&CmpStruct;
            all=&AllocaStruct;
            rnd=&GetRandomStruct;
            print=&StampaStruct;
            deall=&Deallocastruttura;
            break;
        default:
            printf("errore input.. riprova\n");
            break;
    }
    
    LISTA* tmp=NULL;
    switch (scelta){
        case 1:
            //INSERISCE NODO
            val=get();
            alb_curr->albero = inserisci(alb_curr->albero, val, cmp , all);
            printf("inserimento riuscito! \n");
            free(val);
            break;
        case 2:
            //INSERISCE N NODI CASUALI
            printf("inserisci il numero di nodi da inserire casualmente\n");
            scanf("%d",&n);
            int i=0;
            for (i;i<n;i++){
                val=rnd();
                alb_curr->albero = inserisci(alb_curr->albero, val, cmp , all);
            }
            break;
        case 3:
            //CANCELLA NODO
            val=get();
            alb_curr->albero = cancella(alb_curr->albero, val, cmp, all, deall);
            break;
        case 4:
            //CANCELLA CON CONDIZIONE
            printf("cancella i nodi vi tali che (a<= v <= b) (p1<= p <=p2) \n");
            printf("immetti valore a\n");
            a=get();
            printf("immetti valore b\n");
            b=get();
            printf("immetti il valore intero p1\n");
            scanf("%d",&p1);
            printf("immetti il valore intero p2\n");
            scanf("%d",&p2);
            alb_curr->albero = cancella_condizione(alb_curr->albero, a, b, p, p1, p2,cmp,all, deall);
            
        case 5:
            //STAMPA
            if (alb_curr->albero!=NULL){
                stampa_abr(alb_curr->albero, print);
            }else {
                printf("l'albero è vuoto!");
            }
            break;
            
        case 6:
            //ELIMINA INTERO ALBERO
            elimina_albero(alb_curr->albero, deall);
            alberi=cancella_in_lista(alberi, alb_curr->nome);
            printf("l'albero è stato eliminato! \n");
            
            break;
        case 7:
            //DUPLICA
            printf("inserisci stringa per il nome del nuovo albero\n");
            scanf("%s",str);
            tmp = inserisci_in_lista(alberi, str, alb_curr->tipo);
            tmp->albero = duplica(alb_curr->albero,all);
            alberi=tmp;
            printf("albero %s duplicato in %s\n", alb_curr->nome, alberi->nome);
            break;
        case 8:
            //CONFRONTA ALBERI
            printf("con quale albero lo vuoi confrontare?\n");
            stampa_lista(alberi);
            scanf("%s",str);
            tmp = estrai_lista(alberi, str);
            confronto = confronta_alberi(alb_curr->albero, alberi->albero, cmp);
            if (confronto == 0){
                printf("i due alberi sono uguali!");
            }else {
                printf("i due alberi non sono uguali");
            }
            break;
        case 9:
            //RIEMPI ARRAY ORDINATO
            x=0;
            x=conta_nodi(alb_curr->albero, x);
            array=malloc(sizeof(void*)*(x+1));
            n=0;
            riempi_arrayord(alb_curr->albero, array, n,all);
            stampa_array(array, x,print);
            break;
        case 10:
            //BILANCIA CON ARRAY
            x=0;
            x=conta_nodi(alb_curr->albero, x);
            array=malloc(sizeof(void*)*(x+1));
            n=0;
            riempi_arrayord(alb_curr->albero, array, n,all);
            alb_curr->albero = bilancia(array, 0, x,cmp,all);
            break;
        case 11:
            x=maxd(alb_curr->albero, cond);
            printf("x %d",x);
            break;
        case 0:
            break;
            
        default:
            printf("errore input.. riprova\n");
            break;
    }
    free(str);
    free(a);
    free(b);
    return alberi;
}

void stampa_array (void ** array, int max, GETOUT print){
    int i=0;
    for (i;i<max;i++){
        printf("[ ");
        print(array[i]);
        printf("] ");
        
    }
}



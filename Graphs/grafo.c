//
//  grafo.c
//  GRAFI
//
//  Created by Marco Del Giudice on 22/05/18.
//  Copyright © 2018 Marco Del Giudice. All rights reserved.
//

#include "grafo.h"
#include "lista.h"
#include <stdlib.h>
#include <unistd.h>
#include "matrice.h"
#include "coda.h"
#include "heap.h"

void *get_val_vertice(GRAFO *g, int i){
    if(g->matorlist==1){
        return ((VERTICE*)g->vertici[i])->val;
    }
    else{
        return ((NODO_L*)g->adj[i])->val;
    }
}

int get_indice_vertice(GRAFO *g, void *val){
    int i=0;
    for(i=0;i<g->n;i++){
        if(g->cmp(get_val_vertice(g, i),val)==0){
            break;
        }
    }
    return i;
}

void *invia_vertice(GRAFO *g, int i){
    if(g->matorlist==1){
        return g->vertici[i];
    }
    else{
        return g->adj[i];
    }
}



GRAFO *alloca_grafo(GRAFO* g) {
    g = malloc(sizeof(GRAFO));
    return g;
}

void *setta_vertice (int indice,GRAFO *g){
    void *tmp;
    if(g->matorlist==1){
        tmp = (VERTICE*) malloc(sizeof(VERTICE));
        ((VERTICE*)tmp)->val=g->getin();
    }
    else {
        tmp = (NODO_L*)malloc(sizeof(NODO_L));
        ((NODO_L*)tmp)->val=g->getin();
        ((NODO_L*)tmp)->next=NULL;
    }
    return tmp;
}

void *vertice_random (int indice,GRAFO *g){
    void *tmp;
    if(g->matorlist==1){
        tmp = (VERTICE*) malloc(sizeof(VERTICE));
        ((VERTICE*)tmp)->val=g->rnd();
    }
    else {
        tmp = (NODO_L*)malloc(sizeof(NODO_L));
        ((NODO_L*)tmp)->val=g->rnd();
        ((NODO_L*)tmp)->next=NULL;
    }
    return tmp;
}

void setta_arco(GRAFO *g){
    int src = -1,dst = -1;
    float peso;
    stampa_array_vertici(g);
    int ok=0;
    while(ok==0){
        printf("\nscegli il vertice di partenza: ");
        scanf("%d",&src);
        printf("\nscegli il vertice di arrivo: ");
        scanf("%d",&dst);
        if(src>=0 && src<g->n && dst>=0 && dst<g->n)
            ok=1;
    }
    printf("\nscegli il peso dell'arco: ");
    scanf("%f",&peso);
    if(peso<0){
        g->negativew=1;
    }
    if(g->matorlist==1){
        setta_arco_matrice(g,1,src,dst,peso);
       //NON ORIENTATO
       if(src!=dst && g->oriented==2){
            setta_arco_matrice(g, 1, dst, src, peso);
        }
    }else if (g->matorlist==2){
        setta_arco_lista(g, 1, src, dst, peso);
        //NON ORIENTATO
        if(src!=dst && g->oriented==2){
            setta_arco_lista(g, 1, dst, src, peso);
        }
    }
}

void arco_random(GRAFO *g){
    int b=g->n-1;
    int src = 0+(rand()%(b-0+1));
    int dst = 0+(rand()%(b-0+1));
    float peso=(rand()/(float)RAND_MAX)*100;
    if(peso<0){
        g->negativew=1;
    }
    if(g->matorlist==1){
        setta_arco_matrice(g,1,src,dst,peso);
        //NON ORIENTATO
        if(src!=dst && g->oriented==2){
            setta_arco_matrice(g, 1, dst, src, peso);
        }
    }else if (g->matorlist==2){
        setta_arco_lista(g, 1, src, dst, peso);
        //NON ORIENTATO
        if(src!=dst && g->oriented==2){
            setta_arco_lista(g, 1, dst, src, peso);
        }
    }
}

void stampa_grafo(GRAFO *g){
    //IF DI TIPO MATRICE
    if(g->matorlist==1){
        stampa_matrice(g);
    }else{
        stampa_lista(g);
    }
}

void stampa_vertice(GRAFO *g, void *v, int i){
    
    printf("\n[ ");
    printf("%d",i);
    printf(" ] - ");
    if(g->matorlist==1){
        g->print(((VERTICE*)v)->val);
    }else{
        g->print(((NODO_L*)v)->val);
    }
}

GRAFO *imposta_grafo (int tipo, int matorlist, int oriented, GRAFO *g) {
    g->matorlist=matorlist;
    g->tipo=tipo;
    g->negativew=0;
    g->oriented=oriented;
    switch(matorlist) {
        case 1://MATRICE
            g->swap=&scambia_vertici_mat;
            break;
        case 2://LISTE
            g->swap=&scambia_vertici_lista;
            break;
        default:
            break;
    }
    switch (tipo){
        case 1:
            g->getin=&GetInputInt;
            g->print=&StampaIntero;
            g->cmp=&CmpInt;
            g->all=&AllocaIntero;
            g->rnd=&GetRandomInt;
            break;
        case 2:
            g->print = &StampaFloat;
            g->getin = &GetInputFloat;
            g->cmp=&CmpFloat;
            g->all=&AllocaFl;
            g->rnd=&GetRandomFloat;
            break;
        case 3:
            g->print = &StampaStringa;
            g->getin = &GetInputString;
            g->cmp=&CmpString;
            g->all=&AllocaStringa;
            g->rnd=&GetRandomString;
            break;
        case 4:
            g->print = &StampaStruct;
            g->getin = &GetInputStruct;
            g->cmp=&CmpStruct;
            g->all=&AllocaStruct;
            g->rnd=&GetRandomStruct;

            break;
        default:
            break;
    }
    return g;
}

void realloca_vertici(GRAFO *g) {
    if(g->matorlist==1){
        g->vertici = realloc(g->vertici, sizeof(VERTICE**) * g->n );
    }else{
        g->adj = realloc(g->adj, sizeof(NODO_L**) * g->n );
    }
}

void aggiungi_vertice (GRAFO *g){
    g->n=g->n+1;
    realloca_vertici(g);
    if(g->matorlist==1){
        g->vertici[g->n-1]=setta_vertice(g->n-1, g);
        g->adj=(void **)realloca_matrice(g);
    }else{
        g->adj[g->n-1]=setta_vertice(g->n-1, g);
    }
}

void cancella_arco (GRAFO *g,int src,int dst){
    if(dst>g->n)
        return;
    if(g->matorlist==1){
        setta_arco_matrice(g,0,src,dst,0);
    }else if (g->matorlist==2){
        cancella_arco_list(g, src, dst);
        //NON ORIENTATO
        if(src!=dst && g->oriented==2){
            cancella_arco_list(g, dst, src);
        }
    }
}

void cancella_vertice (GRAFO *g, int i){
    if(g->matorlist==1){
    MATRICE **adj=(MATRICE **)g->adj;
    setta_arco_matrice(g, 0, i, g->n-1, 0);
    setta_arco_matrice(g, 0, g->n-1, i, 0);
    if(i!=g->n-1){
        g->swap(g->vertici[i], g->vertici[g->n-1]);
        for(int j=0;j<g->n;j++){
            setta_arco_matrice(g,adj[j][g->n-1].conn , j, i, adj[i][g->n-1].peso);
        }
        for(int j=0;j<g->n;j++){
            setta_arco_matrice(g,adj[g->n-1][j].conn , i, j, adj[g->n-1][j].peso);
        }
    }
    free(((VERTICE*)g->vertici[g->n-1])->val);
    free(((VERTICE*)g->vertici[g->n-1]));
    free((MATRICE *)adj[g->n-1]);
    }else{
        if(g->oriented==1){
            NODO_L *nodo=NULL;
            for(int j=0;j<g->n;j++){
                if(j!=i){
                    nodo=(NODO_L*)g->adj[j];
                    while(nodo->next!=NULL){
                        int dst=get_indice_vertice(g, nodo->next->val);
                        if(dst==i){
                            cancella_arco(g, j, i);
                        }else{
                            nodo=nodo->next;
                        }
                    }
                }
            }
        }
        while(((NODO_L*)g->adj[i])->next!=NULL){
            int dst=get_indice_vertice(g, ((NODO_L*)g->adj[i])->next->val);
            cancella_arco(g, i, dst);
        }
        g->swap(g->adj[i],g->adj[g->n-1]);
        free(((NODO_L*)g->adj[g->n-1])->val);
        free((NODO_L*)g->adj[g->n-1]);
    }
    g->n=g->n-1;
}

void stampa_array_vertici(GRAFO *g){
    for(int i=0;i<g->n;i++){
        if(g->matorlist==1){
            stampa_vertice(g, g->vertici[i],i);
        }else{
            stampa_vertice(g, g->adj[i],i);
        }
    }
}

void elimina_grafo(GRAFO *g){
    if(g!=NULL){
        while(g->n>0){
            cancella_vertice(g,g->n-1);
        }
        free(g->adj);
        if(g->matorlist==1){
        free(g->vertici);
        }
        free(g);
    }
}

void inizializza_grafo (GRAFO *g){
    if(g->matorlist==1){
        inizializza_matrice(g);
    }else{
        inizializza_lista(g);
    }
}

void inizializza_colore(char *col, GRAFO *g, int *pred){
    for(int i=0;i<g->n;i++){
        col[i]='b';
        pred[i]=-1;
    }
}

void percorso_minimo(GRAFO *g, int src,int path, int dst){
    int *pred=NULL;
    if(path==1){//lunghezza minima
        pred = bfs(g, src);
    }else if(path==2){//peso minimo
        if(g->negativew==0){
            pred=dijkstra(g, src);
        }else{
            pred=bellman_ford(g, src);
        }
    }
    if(pred!=NULL){
        printf("\nil percorso minimo è: ");
        stampa_percorso(g, src, dst, pred);
        printf("\n");
        free(pred);
    }
}

void stampa_percorso(GRAFO *g, int src, int dst, int* pred){
    if (src == dst){
        stampa_vertice(g, invia_vertice(g, src), src);
    }else{
        if (pred[dst]== -1){
            printf("percorso non esistente");
        }else{
            stampa_percorso(g, src, pred[dst], pred);
            stampa_vertice(g, invia_vertice(g, dst), dst);
        }
    }
}

int *bfs (GRAFO *g, int src){
    char *col=(char *)malloc(sizeof(char)*g->n);
    int *pred=(int*)malloc(sizeof(int)*g->n);
    inizializza_colore(col, g, pred);
    col[src]='g';
    CODA *c=NULL;
    int t;
    c=accoda(c, &src);
    while(c !=NULL){
        t=*(int*)testa(c);
        int i=0;
        if(g->matorlist==2){
            NODO_L *nodo=((NODO_L*)g->adj[t]);
            while(nodo->next!=NULL){
                i=get_indice_vertice(g, nodo->next->val);
                if(col[i]=='b'){
                    col[i]='g';
                    pred[i]=t;
                    c=accoda(c, &i);
                }
            nodo=nodo->next;
            }
        }else if(g->matorlist==1){
            MATRICE **a=(MATRICE**)g->adj;
            while(i<g->n){
                if(a[t][i].conn!=0){
                    if(col[i]=='b'){
                        col[i]='g';
                        pred[i]=t;
                        c=accoda(c, &i);
                    }
                }
                i++;
            }
        }
        c=decoda(c);
        col[src]='n';
    }
    free(col);
    return pred;
}

int dfs_visita_aciclico (GRAFO *g, int src, char *col){
        col[src]='g';
        if(g->matorlist==2){
            NODO_L* nodo=g->adj[src];
            while(nodo->next!=NULL){
                int i=get_indice_vertice(g, nodo->next->val);
                if(col[i]=='b'){
                    return dfs_visita_aciclico(g, i,col);
                }else if(col[i]=='g'){
                    return 1;
                }
                nodo=nodo->next;
            }
        }else{
            MATRICE **a=(MATRICE**)g->adj;
            int i=0;
            while(i<g->n){
                if(a[src][i].conn!=0){
                    if(col[i]=='b'){
                        return dfs_visita_aciclico(g, i,col);
                    }else if(col[i]=='g'){
                        return 1;
                    }
                }
                i++;
            }
        }
        col[src]='n';
    return 0;
}


int dfs_aciclico (GRAFO *g){
    char *col=(char *)malloc(sizeof(char)*g->n);
    for(int i=0;i<g->n;i++){
        col[i]='b';
    }
    int x=0;
    for(int i=0;i<g->n;i++){
        if(col[i]=='b'){
            x=dfs_visita_aciclico(g, i,col);
        }
    }
    free(col);
    return x;
}

NODO_L *ins_ord(NODO_L *lista,void *vertice){
    NODO_L *nodo=NULL;
    nodo=malloc(sizeof(NODO_L));
    nodo->val=((NODO_L*)vertice)->val;
    nodo->next=lista;
    return nodo;
}

NODO_L *dfs_visita_top (GRAFO *g, int src, char *col, NODO_L *lista){
        col[src]='g';
        if(g->matorlist==2){
            NODO_L* nodo=g->adj[src];
            while(nodo->next!=NULL){
                int i=get_indice_vertice(g, nodo->next->val);
                if(col[i]=='b'){
                    lista=dfs_visita_top(g, i,col,lista);
                }
                nodo=nodo->next;
            }
        }else{
            MATRICE **a=(MATRICE**)g->adj;
            int i=0;
            while(i<g->n){
                if(a[src][i].conn!=0){
                    if(col[i]=='b'){
                        lista=dfs_visita_top(g, i,col,lista);
                }
                i++;
            }
        }
        }
        col[src]='n';
        lista=ins_ord(lista, invia_vertice(g, src));
        return lista;
}

NODO_L *ordinamento_top(GRAFO *g){
    char *col=(char *)malloc(sizeof(char)*g->n);
    int *pred=(int*)malloc(sizeof(int)*g->n);
    inizializza_colore(col, g, pred);
    NODO_L *lista=NULL;
    for(int i=0;i<g->n;i++){
        if(col[i]=='b'){
            lista=dfs_visita_top(g, i,col,lista);
        }
    }
    free(col);
    free(pred);
    return lista;
}

void stampa_ord_top(GRAFO *g,NODO_L *ord){
    NODO_L *nodo=ord;
    if(nodo!=NULL){
        g->print(nodo->val);
        while(nodo->next!=NULL){
            g->print(nodo->next->val);
            NODO_L *tmp=nodo->next;
            free(nodo);
            nodo=tmp;
        }
        free(nodo);
    }
}



void dfs_visita (GRAFO *g, int src, char *col, int *pred, int tempo,int *d,int *f){
        col[src]='g';
        tempo=tempo+1;
        d[src]=tempo;
        if(g->matorlist==2){
            NODO_L* nodo=g->adj[src];
            while(nodo->next!=NULL){
                int i=get_indice_vertice(g, nodo->next->val);
                if(col[i]=='b'){
                    pred[i]=src;
                    dfs_visita(g, i,col,pred,tempo,d,f);
                }
                nodo=nodo->next;
            }
        }else{
            MATRICE **a=(MATRICE**)g->adj;
            int i=0;
            while(i<g->n){
                if(a[src][i].conn!=0){
                    if(col[i]=='b'){
                        pred[i]=src;
                        dfs_visita(g, i,col,pred,tempo,d,f);
                    }
                }
            i++;
            }
        }
        col[src]='n';
        tempo=tempo +1;
        f[src]=tempo;
}

int *dfs (GRAFO *g){
    char *col=(char *)malloc(sizeof(char)*g->n);
    int *pred=(int*)malloc(sizeof(int)*g->n);
    int *d=(int*)malloc(sizeof(int)*g->n);
    int *f=(int*)malloc(sizeof(int)*g->n);
    inizializza_colore(col, g, pred);
    int tempo=0;
    for(int i=0;i<g->n;i++){
        if(col[i]=='b'){
            dfs_visita(g, i,col,pred,tempo,d,f);
        }
    }
    printf("array predecessori");
    for(int i=0;i<g->n;i++){
        printf("%d | ",pred[i]);
    }
    free(col);
    free(pred);
    free(d);
    free(f);
    return pred;
}

void cc_visita(GRAFO *g,int i,int cc,int *componente)
{
    componente[i] = cc;
    if(g->matorlist==2){
        NODO_L* nodo=g->adj[i];
        while(nodo->next!=NULL){ //adiacenti
            int i=get_indice_vertice(g, nodo->next->val);
            if(componente[i]== -1){
                cc_visita(g, i, cc, componente);
            }
            nodo=nodo->next;
        }
    }else{
        MATRICE **a=(MATRICE**)g->adj;
        int j=0;
        while(j<g->n){
            if(a[i][j].conn!=0){ //adiacenti
                if(componente[j]== -1){
                    cc_visita(g, j, cc, componente);
                }
            }
            j++;
        }
    }
}

int *componente_connessa(GRAFO *g){
    int *componente=malloc(sizeof(int)*g->n);
    int i;
    int cc=0;
    for (i = 0; i < g->n; i++) {
        componente[i] = -1;
    }
    for (i = 0; i < g->n; i++) {
        if (componente[i] == -1) {
            cc_visita(g,i,cc,componente);
            cc++;
        }
    }
    return componente;
}

void massimo_sottografo(GRAFO*g){
    int *componente=componente_connessa(g);
    int *max=malloc(sizeof(int)*3);
    max[1]= -1;
    int tmp=0;
    int j=0;
    while(j<g->n){
        for (int i = 0; i < g->n; i++) {
            if(componente[i] == j ){
                tmp = tmp + 1;
            }
        }
        if(tmp == 0){
            break;
        }
        if(tmp > max[1]){
            max[1] = tmp;
            max[0] = j;
        }
        tmp = 0;
        j++;
    }
    for(int i=0;i<g->n;i++){
        if(componente[i]==max[0]){
        stampa_vertice(g, invia_vertice(g, i), i);
        }
    }
    free(componente);
}

void inizializza_dijkstra(GRAFO *g,HEAP *heap,float *d,int *pred,int *visited,int src){
    for(int i=0;i<g->n;i++){
        pred[i]=-1;
        visited[i]=0;
        void *nuovo_val=NULL;
        nuovo_val=g->all(nuovo_val,get_val_vertice(g, i));
        if(i==src){
            d[i]=0;
            inserisci_chiave(heap, nuovo_val, 0);
        }else{
            d[i]=999;
            inserisci_chiave(heap, nuovo_val, 999);
        }
    }
}


void relax(HEAP *heap,int s,int v, int h, float w, int *pred ,float *d){
    
    if(d[v] > (d[s] + w)){
        d[v]=d[s]+w;
        increase_key(heap, h, d[s]+w);
        pred[v] = s;
    }
}

int *dijkstra(GRAFO *g,int src){
    int *pred=(int*)malloc((sizeof(int))* g->n);
    float *d=(float*)malloc((sizeof(float))* g->n);
    int *visited=(int*)malloc((sizeof(int))* g->n);
    void *u;
    int v,s;
    int h;
    float w;
    HEAP *heap=NULL;
    heap=alloca_heap(heap);
    imposta_heap(heap, g->tipo, 2, 1);
    heap=inizializza_heap_tree(heap, 0);
    inizializza_dijkstra(g, heap,d, pred, visited, src);
    while (heap->heapsize > 0){
        u=max_elem(heap);
        s=get_indice_vertice(g,((COPPIA*)u)->val); //indice attuale sorgente
        if(g->matorlist==2){
            NODO_L* nodo=g->adj[s];
            while(nodo->next!=NULL){
                w=nodo->next->peso; //Peso adiacente
                v=get_indice_vertice(g, nodo->next->val);
                h=(get_indice_heap(heap, nodo->next->val)); //indice heap adiacente
                relax(heap, s, v, h, w, pred, d);
                nodo=nodo->next;
            }
        }else{
            MATRICE **a=(MATRICE**)g->adj;
            int i=0;
            while(i<g->n){
                if(a[s][i].conn!=0){
                    w=a[s][i].peso;
                    v=i;
                    h=(get_indice_heap(heap, get_val_vertice(g, i)));//indice heap adiacente
                    relax(heap, s, v, h, w, pred, d);
                }
                i++;
            }
        }
        estrai_max(heap);
    }
    free(heap->elem);
    free(heap);
    free(d);
    free(visited);
    return pred;
}

void inizializza_bellman_ford(GRAFO *g,float *d,int *pred,int src){
    for(int i=0;i<g->n;i++){
        pred[i]=-1;
        if(i==src){
            d[i]=0;
        }else{
            d[i]=999;
        }
    }
}

float *get_peso (GRAFO *g, int src, int dst) {
    float *peso;
    if(g->matorlist==1){
        MATRICE **a=(MATRICE**)g->adj;
        if(a[src][dst].conn==1){
            peso=&(a[src][dst].peso);
            return peso;
        }
    }else if(g->matorlist==2){
        NODO_L* nodo=g->adj[src];
        while(nodo->next!=NULL && (get_indice_vertice(g, nodo->next->val) != dst)){
            nodo=nodo->next;
        }
        if(nodo->next!=NULL){
            if(get_indice_vertice(g, nodo->next->val) == dst){
                peso=&(nodo->next->peso);
                return peso;
            }
        }
    }
    return NULL;
}

void relax_b(int s,int v, float w, int *pred ,float *d){
    if(d[v] > (d[s] + w)){
        d[v]=d[s]+w;
        pred[v] = s;
    }
}


void *bellman_ford (GRAFO *g, int src){
    int *pred=(int*)malloc((sizeof(int))* g->n);
    float *d=(float*)malloc((sizeof(float))* g->n);
    float *w;
    inizializza_bellman_ford(g, d, pred, src);
    for(int i=0;i<g->n-1;i++){
        for(int u=0;u < g->n;u++) {
            for(int v=0;v < g->n;v++) {
                w=get_peso(g, u, v);
                if(w!=NULL){
                    relax_b(u,v,*w,pred,d);
                }
            }
        }
        for(int u=0;u < g->n;u++) {
            for(int v=0;v < g->n;v++) {
                w=get_peso(g, u, v);
                if(w!=NULL){
                    if(d[v] > (d[u] + *w)){
                        printf("ERRORE ESISTE UN CICLO\n");
                        free(d);
                        free(pred);
                        return NULL;
                    }
                }
            }
        }
    }
    free(d);
    for(int i=0;i<g->n;i++){
        printf("PRED \n");
        printf("%d | ",pred[i]);
    }
    return pred;
}

GRAFO *converti(GRAFO *g){
    if(g!=NULL){
        GRAFO *n=(GRAFO*)malloc(sizeof(GRAFO));
        if(g->matorlist==1){
            n=imposta_grafo(g->tipo, 2, g->oriented, n);
            n->adj=malloc(sizeof(NODO_L**)*g->n);
            n->n=g->n;
            for(int i=0;i<g->n;i++){ //creo i vertici
                n->adj[i] = malloc(sizeof(NODO_L));
                ((NODO_L*)n->adj[i])->val=g->all(((NODO_L*)n->adj[i])->val,((VERTICE*)g->vertici[i])->val);
                ((NODO_L*)n->adj[i])->next=NULL;
            }
            MATRICE **a=(MATRICE**)g->adj;
            for(int s=0;s<g->n;s++){
                for(int d=0;d<g->n;d++){
                    if(a[s][d].conn!=0){
                        setta_arco_lista(n, 1, s, d, a[s][d].peso);
                    }
                }
            }
        }else{
            n=imposta_grafo(g->tipo, 1, g->oriented, n);
            n->adj=alloca_matrice(g->n);
            n->n=g->n;
            azzera_matrice(n);
            n->vertici=malloc(sizeof(VERTICE**) * n->n);
            for(int i=0;i<n->n;i++){ //creo i vertici
                n->vertici[i]=(VERTICE*) malloc(sizeof(VERTICE));
                n->vertici[i]->val=n->all(n->vertici[i]->val,((NODO_L*)g->adj[i])->val);
            }
            int d;
            NODO_L *nodo=NULL;
            for(int i=0;i<g->n;i++){
                nodo=(NODO_L*)g->adj[i];
                while(nodo->next!=NULL){
                    d=get_indice_vertice(g, nodo->next->val);
                    setta_arco_matrice(n, 1, i, d, nodo->next->peso);
                    nodo=nodo->next;
                }
            }
            
        }
        elimina_grafo(g);
        return n;
    }
    return NULL;
}

GRAFO *grafo_trasposto (GRAFO *g){
    if(g!=NULL && g->oriented==1){
        GRAFO *n=NULL;
        n=alloca_grafo(n);
        n=imposta_grafo(g->tipo, g->matorlist, g->oriented, n);
        n->n=g->n;
        if(g->matorlist==2){
            n->adj=malloc(sizeof(NODO_L**)*g->n);
            for(int i=0;i<g->n;i++){ //creo i vertici
                n->adj[i] = malloc(sizeof(NODO_L));
                ((NODO_L*)n->adj[i])->val=g->all(((NODO_L*)n->adj[i])->val,((NODO_L*)g->adj[i])->val);
                ((NODO_L*)n->adj[i])->next=NULL;
            }
            NODO_L *nodo;
            int d;
            for(int i=0;i<g->n;i++){
                nodo=(NODO_L*)g->adj[i];
                while(nodo->next!=NULL){
                    d=get_indice_vertice(g, nodo->next->val);
                    setta_arco_lista(n, 1, d, i, nodo->next->peso);
                    nodo=nodo->next;
                }
            }
        }else if(g->matorlist==1){
            n=imposta_grafo(g->tipo, 1, g->oriented, n);
            n->adj=alloca_matrice(g->n);
            n->n=g->n;
            azzera_matrice(n);
            n->vertici=malloc(sizeof(VERTICE**) * n->n);
            for(int i=0;i<n->n;i++){ //creo i vertici
                n->vertici[i]=(VERTICE*) malloc(sizeof(VERTICE));
                n->vertici[i]->val=n->all(n->vertici[i]->val,((VERTICE*)g->vertici[i])->val);
            }
            MATRICE **a=(MATRICE**)g->adj;
            for(int s=0;s<g->n;s++){
                for(int d=0;d<g->n;d++){
                    if(a[s][d].conn!=0){
                        setta_arco_matrice(n, 1, d, s, a[s][d].peso);
                    }
                }
            }
        }
        return n;
    }
    return NULL;
}

void grafo_casuale (GRAFO *g,int n,int e){
    g->n=n;
    int archi=e;
    if(g->matorlist==1){
        g->adj=alloca_matrice(g->n);
        azzera_matrice(g);
        g->vertici=malloc(sizeof(VERTICE**) * g->n);
    }else{
         g->adj=malloc(sizeof(NODO_L**)*g->n);
    }
    for(int i=0;i<g->n;i++){
        if(g->matorlist==2){
            g->adj[i]=vertice_random(i, g);
        }else{
            g->vertici[i]=vertice_random(i, g);
        }
    }
    if(g->n>0){
        for(int j=0;j<archi;j++){
            arco_random(g);
        }
    }
    
}





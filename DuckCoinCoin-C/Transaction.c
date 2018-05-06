#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "sha256_utils.h"
#include "Transaction.h"


/********FONCTION DE CREATION DE DATE*************/

char * getTimeStamp(){
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}

/*************************************************/

struct s_transaction {
    struct s_transaction *next ;
    struct s_transaction *prev ;
    int index ;
    char srcDest[512] ;
    char hash[SHA256_BLOCK_SIZE*2 + 1] ; // calcul et stockage du hash directement à l'ajout d'une transaction dans la deque
} ;

struct s_transactionDeque {
    Transaction sentinel ;
    int size ;
} ;

/****************************************************/

TransactionDeque transaction_genesis() {
   TransactionDeque t = malloc(sizeof(struct s_transactionDeque)) ;
   t->sentinel = malloc(sizeof(struct s_transaction)) ;
   Transaction trans = malloc(sizeof(struct s_transaction)) ;
   sprintf(trans->srcDest,"Genesis") ;
   trans->next = t->sentinel ;
   trans->prev = t->sentinel ;
   t->sentinel->next = trans ;
   t->sentinel->prev = trans ;
   trans->index = 0 ;
   t->size = 1 ; 
   return t ;
}

void create_transaction(char trans[512]) {
    sprintf(trans,"Source-Destination : %d",rand()%MAX_VALUE) ;
}

char * getSrcDest(TransactionDeque t) {
    return t->sentinel->next->srcDest ;
}

TransactionDeque init_transaction_deque() {
    TransactionDeque t = malloc(sizeof(struct s_transactionDeque)) ;
    t->sentinel = malloc(sizeof(struct s_transaction)) ;
    t->sentinel->next = t->sentinel ;
    t->sentinel->prev = t->sentinel ;
    t->size = 0 ;
    return t ;
}

bool isEmpty(TransactionDeque t){
    return t->size == 0;
}

/****************************************************/


void set_hash_transaction(Transaction  transaction) {
    sha256ofString(transaction->srcDest, transaction->hash) ;
}


void add_transaction_to_transactionDeque(TransactionDeque t){
    Transaction new = malloc(sizeof(struct s_transaction)) ;
    new->index = t->size ;
    create_transaction(new->srcDest) ;
    set_hash_transaction(new);
    new->next = t->sentinel ;
    new->prev = t->sentinel->prev ;
    t->sentinel->prev->next = new ;
    t->sentinel->prev = new ;
    t->size++ ;
}


void remove_transaction(TransactionDeque t, int index) { 
    assert(!isEmpty(t));
    if(index>=t->size){
       printf("Index entered is higher than max transactions. Last transactions is removed in stead of that one\n");
       index = t->size - 1 ;
    }
    Transaction itr = t->sentinel->next ;
    while (index--) 
        itr = itr->next ;
    itr->prev->next = itr->next ;
    itr->next->prev = itr->prev ;
    free(itr) ;
    --(t->size) ;
}


void delete_transaction_deque(TransactionDeque t){
    while(t->size) {
        remove_transaction(t,0) ;
    }
    free(t->sentinel) ;
    free(t) ;
}


int get_index(Transaction transaction) { 
    return transaction->index ;
}

int get_nb_total_transactions(TransactionDeque t) {
    return t->size ;
}

void hash_Merkle_tree(TransactionDeque t, char *hash){
 /*   (void)t ;
    hash = "" ;
    */
    assert(!isEmpty(t));
    int taille = t->size ;
    Transaction itr ;
    char c[2*(SHA256_BLOCK_SIZE*2 + 1)] ;
    int cpt ;

    if ( taille%2==1 ){
        taille+=1 ;
    }

    char hashTab[taille/2+1][SHA256_BLOCK_SIZE*2 + 1] ; // Stocke Nb_transactions/2 Hashs
   
    // Si nombre impair, taille>t-size, permet de gérer le dédoublement du dernier hash
    if (taille > t->size){
        sprintf(c,"%s%s",t->sentinel->prev->srcDest,t->sentinel->prev->srcDest) ;
        sha256ofString(c,hashTab[taille/2-1]) ;
        itr = t->sentinel->prev->prev ;
        cpt = taille/2-2 ;
    }
    else {
        cpt = taille/2-1 ;
        itr = t->sentinel->prev ;
    }


    // initialisation de hashTab
    while (itr != t->sentinel && cpt >= 0) {
        sprintf(c,"%s%s",itr->prev->srcDest,itr->srcDest) ;
        sha256ofString(c,hashTab[cpt]) ;
        cpt-- ;
        itr = itr->prev->prev ;
    }


    while (taille/2 > 1) {
        taille = taille/2 ;
        cpt = 0 ;
        if (taille%2==1) {
            strcpy(hashTab[taille],hashTab[taille-1]) ;
            taille++ ;
        }
        while (cpt*2 < taille){
            sprintf(c,"%s%s",hashTab[cpt*2],hashTab[cpt*2+1]) ;
            sha256ofString(c,hashTab[cpt]) ;
            cpt++ ;
        }
    }

    strcpy(hash,hashTab[0]);
} 

// fonction pour tester les valeurs d'un bloc
/*void display_info(TransactionDeque t){
    for(Transaction itr = t->sentinel->next;itr != t->sentinel;itr=itr->next){
        printf(" Transaction: %s\n Index: %d\n Hash: %s\n",itr->srcDest,get_index(itr),itr->hash) ;
    }
}*/

/*int main(int argc,char *argv[]) {
    srand(time(NULL)) ;
    TransactionDeque t = init_transaction_deque() ;
    for (int i=0; i<5;i++) 
        add_transaction_to_transactionDeque(t) ;
    for(Transaction itr = t->sentinel->next;itr != t->sentinel;itr=itr->next){
        printf(" Transaction: %s\n Index: %d\n Hash: %s\n",itr->srcDest,get_index(itr),itr->hash) ;
    }
    char h[SHA256_BLOCK_SIZE*2+1] ;
    hash_Merkle_tree(t,h);
    printf(" Hash du tree : %s\n",h);
    delete_transaction_deque(t) ;
    return 0 ;

} */

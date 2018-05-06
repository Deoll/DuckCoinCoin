#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>

#include "blockchain.h"
#include "Transaction.h"

#define NB_MAX_TRANSACTIONS 10 
#define GENESIS_MANQUANT 1 ;
#define ERR_CHAINAGE_HASH 2 ;
#define ERR_HASH 3 ;
#define ERR_MERKLE_ROOT 4 ;

struct s_blockchain {
	int difficulty  ;
	int nbBlocks ;
	Block sentinel ;
};

/*----------------------------------------------------------------*/

void init_genesis(Blockchain blockchain) {
	Block b = create_block(transaction_genesis(),0,"0",blockchain->difficulty) ;
	b->next = blockchain->sentinel ;
	b->prev = blockchain->sentinel ;
	blockchain->sentinel->next = b ;
	blockchain->sentinel->prev = b ;
}

/*----------------------------------------------------------------*/

Blockchain create_blockchain(int dif) {
	Blockchain blockchain = malloc(sizeof(struct s_blockchain)) ;
	blockchain->sentinel = malloc(sizeof(struct s_block)) ;
	blockchain->difficulty = dif ;
	init_genesis(blockchain) ;
	blockchain->nbBlocks = 1 ;
	return blockchain ;
}


/*----------------------------------------------------------------*/

void push_block(Blockchain blockchain,Block block) {
	block->next = blockchain->sentinel ;
	block->prev = blockchain->sentinel->prev ;
	blockchain->sentinel->prev->next = block ;
	blockchain->sentinel->prev = block ;
	(blockchain->nbBlocks)++ ;
}

/*----------------------------------------------------------------*/

void remove_block_from_blockchain(Blockchain blockchain,int indexBlock) {
	assert((indexBlock >= 0) && (blockchain->nbBlocks > indexBlock)) ;
	Block block = blockchain->sentinel->next ;
	while (indexBlock--)
		block = block->next ;	//on trouve block à suppr
	block->next->prev = block->prev ;				
	block->prev->next = block->next ;
	remove_block(block) ;								//on le free
	--(blockchain->nbBlocks) ;
}

/*----------------------------------------------------------------*/

bool empty(Blockchain blockchain) {
	return (blockchain->nbBlocks == 0) ;
}

/*----------------------------------------------------------------*/

Block get_block(Blockchain blockchain, int indexBlock) {
	assert(0<=indexBlock && indexBlock<Blockchain->nbBlocks) ;
	Block itr = blockchain->sentinel->next ;
	for(; indexBlock>0; indexBlock--, itr=itr->next) ;
	return itr ;
}

int get_difficulty(Blockchain b) {
	return b->difficulty ; 
}

/*----------------------------------------------------------------*/

void rebuild_Blockchain(Blockchain blockchain, int indexBlock) {
	Block cur = blockchain->sentinel->next ;
	while (indexBlock--) // on va au block a partir du quel on recalcul les hash
		cur = cur->next ;

	while (cur != blockchain->sentinel) { // tq pas fin de la blockchain 
		if(cur->prev == blockchain->sentinel) { // si on rebuild a partir du genesis
			delete_transaction_deque(cur->transactions) ;
			cur->transactions = transaction_genesis() ;
			cur->nbTransaction = 1 ;
			sprintf(cur->hashPrev,"0") ;
			cur->index = 0 ;
			cur->nonce = 0 ;
			calcul_hash_block(cur) ;
		}
		else {
			cur->index = (cur->prev->index)+1 ;
			strcpy(cur->hashPrev,get_hash(cur->prev)) ;
			cur->nonce = 0 ;
			minage(cur,blockchain->difficulty) ;
		}
		cur = cur->next ;
	}
}

/*----------------------------------------------------------------*/
	

void delete_Blockchain (Blockchain blockchain){
	while (blockchain->nbBlocks){
		remove_block_from_blockchain(blockchain,0) ; //remove le premier element de la blockchain
	}
	free(blockchain->sentinel) ;
	free(blockchain) ;							//free la blockchain
}


/*-----------------------------VERIF-------------------------------*/

int verif_hash_block(Blockchain B,Block b) {
	bool unic = true ;
	Block itr = B->sentinel->next ;
	while(itr != B->sentinel && unic){
		if (itr != b && strcmp(itr->hashCour,b->hashCour) == 0){
			unic = false ;
		}
		itr = itr->next ;
	}
	return unic ;
}

/*	this function was used to test the module		

void display_info_block(Block block) {
	printf("Block info\n index: %d\n Transactions:\n",block->index) ;
	printf("timeStamp: %s\n hash precedent: %s\n",block->timeStamp,block->hashPrev);
	printf("nombre de transactions: %d\n hash transactions: %s\n",block->nbTransaction,block->hashTreeRoot);
	printf("nonce: %d\n hash du block: %s\n",block->nonce,block->hashCour) ;
}

*/


bool verif_hash_block_naif (Block b,int d) {
	int nonce = b->nonce ;
	char hash[SHA256_BLOCK_SIZE*2 + 1] ;
	strcpy(hash,b->hashCour) ;
	b->nonce = 0 ;
	minage(b,d) ;
	if (strcmp(b->hashCour,hash) == 0) {
		return true  ;
	}
	b->nonce = nonce ;
	strcpy(b->hashCour,hash) ;
	return false ;

}

bool genesis_is_the_first_block(Blockchain b) {
	Block bl = b->sentinel->next ;
	if (strcmp(bl->hashPrev,"0")==0 && strcmp(getSrcDest(bl->transactions),"Genesis")==0 && bl->nonce == 0)
		return true ;
	return false ;
}

int verification_1(Blockchain b) {
	Block itr = b->sentinel->next->next ;
	if (!(genesis_is_the_first_block(b))){
		fprintf(stderr,"Error : No genesis !\n");
		return GENESIS_MANQUANT ;
	}
	while (itr != b->sentinel) {
		if (strcmp(itr->hashPrev,itr->prev->hashCour)){
			fprintf(stderr,"Error : Hash chain !\n");
			return ERR_CHAINAGE_HASH ;
		}
		if (!(verif_hash_block_naif(itr,b->difficulty))){
			fprintf(stderr,"Error : hash !\n");
			return ERR_HASH ;
		}
		itr = itr->next ;
	}
	return 0 ;
}

int verification_2(Blockchain b) {
	char str[SHA256_BLOCK_SIZE*2 + 1] ;
	Block itr = b->sentinel->next ;
	while (itr != b->sentinel) {
		hash_Merkle_tree(get_transaction(itr),str) ;
		if (strcmp(str,itr->hashTreeRoot)){
			printf("Error : merkle root !\n");
			strcpy(itr->hashTreeRoot,str) ;
			return ERR_MERKLE_ROOT ;
		}
		itr = itr->next ;
	}
	return 0 ;
}

/*-----------------------------------------------------------------*/


//---------TESTS----------//

/*

int main(void) {

	srand(time(NULL)) ;
	
	printf("Création TransactionDeque :\n");
    TransactionDeque t = init_transaction_deque() ;
    TransactionDeque t1 = init_transaction_deque() ;

    for (int i=0; i<5;i++) {
    	printf("Ajout de Transaction :\n");
        add_transaction_to_transactionDeque(t) ;
        add_transaction_to_transactionDeque(t1) ;
    }
    
    printf("Création blockchain : \n");
    Blockchain bc = create_blockchain(3) ;
   
    printf("Initialisation du genesis : \n");
    init_genesis(bc) ;

    printf("Ajout de block :\n");
   	push_block(bc,create_block(t,1,get_block(bc,bc->nbBlocks)->hashCour,3)) ; // ajout d'un block à la bc
   	push_block(bc,create_block(t1,2,get_block(bc,bc->nbBlocks)->hashCour,3)) ; // ajout d'un block à la bc
    
   	printf("Affichage des infos des block de la bc :\n") ;
   	for (int i = 0; i < bc->nbBlocks ; i++)
   		display_info_block(get_block(bc,i)) ;


    printf("Suppression blockchain :\n");
    delete_Blockchain(bc) ;
    printf("Done.\n");
	return 0 ;
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>

#include "cheater.h"


void cheater_block(Blockchain blockchain, int indexBlock){
	clock_t debut = clock() ;		//start chrono
	remove_block_from_blockchain(blockchain,indexBlock) ;
	rebuild_Blockchain(blockchain,indexBlock) ;
	clock_t fin = clock() ;			//fin chrono
	printf("temps CPU = %.2f secondes \n", (double) (fin-debut)/CLOCKS_PER_SEC ) ;
}

void cheater_transaction(Blockchain blockchain, int indexBlock, int indexTransaction){
	clock_t debut = clock() ;  		//start timer
	Block block = get_block(blockchain,indexBlock) ;
	TransactionDeque t = get_transaction(block) ;
	remove_transaction(t, indexTransaction) ;
	block->nbTransaction = (block->nbTransaction)-1 ;
	hash_Merkle_tree(t, block->hashTreeRoot) ;
	rebuild_Blockchain(blockchain,indexBlock) ;
	clock_t fin = clock() ;			//fin timer
	printf("temps CPU = %.2f secondes \n", (double) (fin-debut)/CLOCKS_PER_SEC ) ;	
}
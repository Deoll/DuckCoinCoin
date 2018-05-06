#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>

#include "block.h"

void calcul_hash_block(Block block) {
	char str[512] ;
	sprintf(str, "%s%d", "", block->index);
	sprintf(str,"%s%s",str,block->timeStamp);
	sprintf(str,"%s%s",str,block->hashPrev);
	sprintf(str,"%s%d",str,block->nbTransaction);
	sprintf(str,"%s%s",str,block->hashTreeRoot);
	sprintf(str,"%s%d",str, block->nonce);
	sha256ofString(str,block->hashCour);
}
/* ******************************************************* */
//copy a string without the last character
void copy(char dest[128], char *src) {
	for (unsigned int i=0; i<strlen(src)-1;i++)
		dest[i] = src[i] ;
}
/* ******************************************************* */
Block create_block(TransactionDeque transactions,int idBlock, char hashPrev[SHA256_BLOCK_SIZE*2 + 1], int diff){
	Block block = malloc(sizeof(struct s_block)) ;
	block->index = idBlock ;
	copy(block->timeStamp,getTimeStamp()) ;
	sprintf(block->hashPrev,"%s",hashPrev) ;
	block->transactions = transactions ;
	block->nbTransaction = get_nb_total_transactions(transactions) ;
	hash_Merkle_tree(transactions,block->hashTreeRoot) ;
	block->nonce = 0 ;
	if (idBlock) // if this is not the genesis block 
		minage(block,diff) ;
	else
		calcul_hash_block(block) ;
	return block ;
}
/* ******************************************************* */
//the d first letters of hash are the character '0'
bool verif_diff_hash(char *hash,int d) {
	for(int i=0;i<d;i++)
		if (hash[i] != '0')
			return false ;
	return true ;
}
/* ******************************************************* */
void minage(Block b,int d) {
	bool diffAttent = false ;
	while(!diffAttent) {
		calcul_hash_block(b) ;
		if (verif_diff_hash(b->hashCour,d))
			diffAttent = true ;
		else
			b->nonce++ ;
	}
}
/* ******************************************************* */
bool block_empty(Block block){
	return (block->nbTransaction == 0);
}
/* ******************************************************* */
char *get_hash(Block block){
	assert(!block_empty(block));
	return block->hashCour;
}
/* ******************************************************* */
char *get_timeStamp(Block block){
	assert(!block_empty(block));
	return block->timeStamp;
}
/* ******************************************************* */
TransactionDeque get_transaction(Block block){
	assert(!block_empty(block));
	return block->transactions;
}
/* ******************************************************* */
void remove_block(Block block) {
	delete_transaction_deque(block->transactions) ;
	free(block);
	block = NULL ;
}
/* ******************************************************* */


/* *********************TESTS***************************** */
/*
void display_info_block(Block block) {
	printf("Block info\n index: %d\n Transactions:\n",block->index) ;
	display_info(block->transactions) ;
	printf("timeStamp: %s\n hash precedent: %s\n",block->timeStamp,block->hashPrev);
	printf("nombre de transactions: %d\n hash transactions: %s\n",block->nbTransaction,block->hashTreeRoot);
	printf("nonce: %d\n hash du block: %s\n",block->nonce,block->hashCour) ;
}


int main(void) {
	srand(time(NULL)) ;
    TransactionDeque t = init_transaction_deque() ;
    int i;
    for (i=0; i<5;i++) 
        add_transaction_to_transactionDeque(t) ;
    Block b = create_block(t,0,"") ;
    display_info_block(b) ;
    minage(b,4);
    printf("toto\n");
    display_info_block(b) ;
    printf("start remove\n");
    remove_block(b) ;
    printf("fin remove\n");
	return 0 ;
}*/
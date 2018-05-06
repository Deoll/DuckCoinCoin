#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>

#include "block.h"

void calcul_hash_block(Block block) {
	char str[512] ;
	//printf("debut calcul_hash_block-->%ld\n",block->nonce );
	sprintf(str, "%s%d", "", block->index);
	//printf("\n %s 1\n",str);
	sprintf(str,"%s%s",str,block->timeStamp);
	//printf("\n%s 2\n",str);
	sprintf(str,"%s%s",str,block->hashPrev);
	//printf("\n%s 3\n",str);
	sprintf(str,"%s%d",str,block->nbTransaction);
	//printf("\n%s 4\n",str);
	sprintf(str,"%s%s",str,block->hashTreeRoot);
	//printf("\n%s 5\n",str);
	sprintf(str,"%s%d",str, block->nonce);
	//printf("\n%s 6\n",str);
	//printf("\n index: %d, timeStamp: %s, hasprev: %s, nbTransaction: %d, hashTreeRoot: %s, nonce: %ld \n",block->index,
	//	block->timeStamp,block->hashPrev,block->nbTransaction,block->hashTreeRoot,block->nonce);

	sha256ofString(str,block->hashCour);
}

void copy(char dest[128], char *src) {
	for (unsigned int i=0; i<strlen(src)-1;i++){
		dest[i] = src[i] ;
	}
	//printf("%s\n",dest);
}

Block create_block(TransactionDeque transactions,int idBlock, char hashPrev[SHA256_BLOCK_SIZE*2 + 1], int diff){

	// Initialiser les valeurs du block
	Block block = malloc(sizeof(struct s_block)) ;
	block->index = idBlock ;
	copy(block->timeStamp,getTimeStamp()) ;
	//strcpy(block->timeStamp,getTimeStamp()) ;
	//block->timeStamp = getTimeStamp() ;	
	sprintf(block->hashPrev,"%s",hashPrev) ; //<-- block->hashPrev = hash ;
	block->transactions = transactions ;
	block->nbTransaction = get_nb_total_transactions(transactions) ;
	hash_Merkle_tree(transactions,block->hashTreeRoot) ;
	block->nonce = 0 ;
	if (idBlock) // si pas génésis
		minage_naif(block,diff) ;
	else
		calcul_hash_block(block) ;
	return block ;
}





//On peut créer une fonction "Minage" et qu'on peut appliquer dans le create et dans set_HashPrev qui fait :
void minage(Block block, int difficulty){ 
	//BYTE * tempLine ;
	//printf("start minage\n");
	//printf("nonce = %d\n",block->nonce );
	int i=0;
	//printf("start 1er calcul_hash_block\n");
	calcul_hash_block(block);
	while (i<difficulty){
		if (block->hashCour[i] != '0'){
			//printf("recalcule\n");
			++(block->nonce);
			//printf("calcul_hash_block:\n");
			calcul_hash_block(block);
			//printf("end calcul_hash_block, nonce = %d\n",block->nonce);
			//printf("%s\n",block->hashCour);
			//printf("premier car du hash:%c ",block->hashCour[0]);
			//sha256ofString(tempLine,block->hashCour);
			i=0;
		}
		else
			++i;
	}
	//printf("fin Minage\n");
}
bool verif_diff_hash(char *hash,int d) {
	for(int i=0;i<d;i++)
		if (hash[i] != '0')
			return false ;
	return true ;
}

void minage_naif(Block b,int d) {
	bool diffAttent = false ;
	while(!diffAttent) {
		calcul_hash_block(b) ;
		if (verif_diff_hash(b->hashCour,d))
			diffAttent = true ;
		else
			b->nonce++ ;
	}
}

bool block_empty(Block block){
	return (block->index == 0);
}

char *get_hash(Block block){
	assert(!block_empty(block));
	return block->hashCour;
}

char *get_timeStamp(Block block){
	assert(!block_empty(block));
	return block->timeStamp;
}

TransactionDeque get_transaction(Block block){
	assert(!block_empty(block));
	return block->transactions;
}
 

void remove_block(Block block) {
	delete_transaction_deque(block->transactions) ;
	free(block);
	block = NULL ;
}
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
    Block b = create_block(t,0,"",2) ;
    display_info_block(b) ;
    minage(b,4);
    printf("toto\n");
    display_info_block(b) ;
    printf("start remove\n");
    remove_block(b) ;
    printf("fin remove\n");
	return 0 ;
}*/

#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <stdbool.h>

#include "sha256_utils.h"
#include "sha256.h"
#include "Transaction.h"

/**
 * @brief description of a block
 */
typedef struct s_block {
	int index ;
	char timeStamp[128];
	char hashPrev[SHA256_BLOCK_SIZE*2 + 1] ;
	int nbTransaction ;
	TransactionDeque transactions ; 
	char hashTreeRoot[SHA256_BLOCK_SIZE*2 + 1] ;
	char hashCour[SHA256_BLOCK_SIZE*2 + 1] ;
	int nonce ;
	struct s_block *prev ;
	struct s_block *next ;
}*Block ;


void calcul_hash_block(Block block) ;
/**
 * @brief initialize a block 
 * 
 * @param transactionTree that must be stored in this block
 * @param idBlock the number to identify the position of the block 
 * @param hash of the previous block in the blockchain
 * @return block (type s_block *)
 */
Block create_block(TransactionDeque transaction,int idBlock, char *hash, int diff) ;

void minage(Block block, int difficulty) ;
/**
 * @return the current hash of a block
 * 
 * @param block [description]
 * @return hash (type char *)
 */
bool block_empty(Block block);

char *get_hash(Block block) ;
/**
 * @return timestamp of a block
 * 
 * @param block [description]
 * @return timestamp (type time_t)
 */
char * get_timeStamp(Block block) ;
/**
 * @return transactionTree of a block
 * 
 * @param block [description]
 * @return transaction Tree (type transationTree)
 */
TransactionDeque get_transaction(Block block) ;

void remove_block(Block block) ;

#endif

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
/* ******************************************************* */
/**
 * @brief hash hash calculation with block information
 * 
 * @param block regular block to calculate
 */
void calcul_hash_block(Block block) ;
/* ******************************************************* */
/**
 * @brief initialize a block 
 * 
 * @param transactionTree that must be stored in this block
 * @param idBlock the number to identify the position of the block 
 * @param hash of the previous block in the blockchain
 * @return block (type s_block *)
 */
Block create_block(TransactionDeque transaction,int idBlock, char *hash, int diff) ;
/* ******************************************************* */
/**
 * @brief new hash calcul with difficulty 
 * 
 * @param block regular block to recalculate hash 
 * @param difficulty difficulty in the hash calculation
 */
void minage(Block block, int difficulty) ;
/* ******************************************************* */
/**
 * @brief block has not transactions
 * 
 * @param block regular block
 * @return boolean 
 */
bool block_empty(Block block);
/* ******************************************************* */
/**
 * @return the current hash of a block
 * 
 * @param block regular block
 * @return hash (type char *)
 */
char *get_hash(Block block) ;
/* ******************************************************* */
/**
 * @return timestamp of a block
 * 
 * @param block regular block
 * @return timestamp (type time_t)
 */
char * get_timeStamp(Block block) ;
/* ******************************************************* */
/**
 * @return Transaction list of a block
 * 
 * @param block regular block
 * @return transaction Tree (type transationTree)
 */
TransactionDeque get_transaction(Block block) ;
/* ******************************************************* */
/**
 * @brief delete information from a  regular block
 * 
 * @param block regular block
 */
void remove_block(Block block) ;
/**
 *
 * @brief testing values into a block
 *
 */
//void display_info_block(Block block);
#endif

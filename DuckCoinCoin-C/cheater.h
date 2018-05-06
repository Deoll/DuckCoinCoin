#ifndef __CHEATER_H__
#define __CHEATER_H__
#include<stdbool.h>

#include "blockchain.h"

/**
 * @brief delete block at indexBlock and rebuild the blockchain
 * 
 * @param blockchain the Blockchain to modify
 * @param indexBlock the index of the block to delete
 */
void cheater_block(Blockchain blockchain, int indexBlock);
/**
 * @brief delete transaction at indexTransaction from a block and rebuild Blockchain
 * 
 * @param blockchain the Blockchain to modify
 * @param indexBlock the index of the block to delete the transaction
 * @param indexTransaction the index of the transaction to delete
 */
void cheater_transaction(Blockchain blockchain, int indexBlock, int indexTransaction);


#endif

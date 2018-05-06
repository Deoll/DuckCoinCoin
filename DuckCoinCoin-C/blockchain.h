#ifndef __PROJET_h__
#define __PROJET_h__
#include <stdbool.h>
#include "block.h"

/**
*@BlockChain structure
 */
typedef struct s_blockchain *Blockchain ;
/**
 * @brief initialization of the BlockChain's genesis
 *
 * @details create the genesis block and place it into a new Blockchain
 * 
 * @param  difficulty of the BlockChain
 */
void init_genesis(Blockchain) ;
/**
 * @brief create a new BlockChain
 * 
 * @return a new BlockChain with only the genesis block
 */
Blockchain create_blockchain(int dif) ;
/**
 * @brief push a new block into the BlobkChain
 *
 * @param block is the block to push
 */
void push_block(Blockchain blockchain,Block block) ;
/**
 * @brief remove the block numbre intBlock from the BlobkChain
 * 
 * @details after the remove from the BlockChain, we remove the block itself
 * 
 */
void remove_block_from_blockchain(Blockchain blockchain,int iBlock) ;
/**
 * @brief used to see if the BlockChain is empty
 *
 * @return true if the number of blocks into the BlockChain is 0 
 */
bool empty(Blockchain blockchain) ;
/**
 * @rebuild the BlockChain 
 *
 * @rebuild the BlockChain from block number iBlock
 * 
 * @param blockchain is the blockChain to rebuild
 */
void rebuild_Blockchain(Blockchain blockchain, int iBlock) ;
/**
 * @brief getter of block
 *
 * @details getter of the block numbre iBlock from the BlockChain blockchain
 * 
 * @return block iBlock
 */
Block get_block(Blockchain blockchain, int indexBlock) ;
/**
 * @brief free the entire BlockChain
 
 * @details remove the first element of the BlockChain until the number of blocks is 0,
 * then free the BlockChain's sentinel and the structure itself
 */
void delete_Blockchain(Blockchain blockchain) ;
/**
 * @brief return the difficulty of the BlockChain
 * 
 * @return int difficulty from BlockChain
 */
int get_difficulty(Blockchain b) ;
/**
 * @brief first verification of the BlockChain
 *
 * @details verify its integrity: if the genesis is the first block, and if the hashs are correct
 *
 * @return GENESIS_MANQUANT if the genesis is not the first block, ERR_CHAINAGE_HASH if somewhere in the BlockChain
 * a block->hashPrev is not the same as the actual hash of the previous block, and ERR_HASH if the hash from a block
 * is not correct
 */
int verification_1(Blockchain b) ;
/**
 * @brief second verification of the BlockChain
 *
 * @details verify the integrity of the Merkel Tree 
 *
 * @return ERR_MERKLE_ROOT if one HashTreeRoot reom a block of the BlockChain is not correct, return 0 if the integrity is ok
 */
int verification_2(Blockchain b) ;

#endif 


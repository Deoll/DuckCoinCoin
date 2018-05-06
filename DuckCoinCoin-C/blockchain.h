#ifndef __PROJET_h__
#define __PROJET_h__
#include <stdbool.h>
#include "block.h"
/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
typedef struct s_blockchain *Blockchain ;
/**
 * @brief [brief description]
 * @details [long description]
 * @return [description]
 */
Blockchain create_blockchain(int dif) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param  [description]
 */
void init_genesis(Blockchain) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param blockchain [description]
 * @param block [description]
 */
void push_block(Blockchain blockchain,Block block) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param blockchain [description]
 * @param iBlock [description]
 */
void remove_block_from_blockchain(Blockchain blockchain,int iBlock) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param blockchain [description]
 * @return [description]
 */
bool empty(Blockchain blockchain) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param blockchain [description]
 * @param iBlock [description]
 */
void rebuild_Blockchain(Blockchain blockchain, int iBlock) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param blockchain [description]
 * @param numBlock [description]
 * 
 * @return [description]
 */
Block get_block(Blockchain blockchain, int indexBlock) ;

void delete_Blockchain(Blockchain blockchain) ;

int get_difficulty(Blockchain b) ;

int verification_1(Blockchain b) ;

int verification_2(Blockchain b) ;

#endif 


#ifndef __CHEATER_H__
#define __CHEATER_H__
#include<stdbool.h>

#include "blockchain.h"


void cheater_block(Blockchain blockchain, int indexBlock);



void cheater_transaction(Blockchain blockchain, int indexBlock, int indexTransaction);


#endif
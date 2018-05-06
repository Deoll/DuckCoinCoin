#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#define MAX_VALUE 10 


char *getTimeStamp(void) ;
/**
 * @Transaction structure 
 * 
 */
typedef struct s_transaction *Transaction ;
typedef struct s_transactionDeque *TransactionDeque ;

TransactionDeque transaction_genesis() ;
/**
 * @ 
 */
void create_transaction() ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @return [description]
 */
 TransactionDeque init_transaction_deque() ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param transaction [description]
 * @return [description]
 */

void set_hash_transaction(Transaction  transaction) ;

char * getSrcDest(TransactionDeque t) ;

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param t [description]
 */
void add_transaction_to_transactionDeque(TransactionDeque t) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param transaction [description]
 */
void remove_transaction(TransactionDeque transaction, int index) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param t [description]
 */
void delete_transaction_deque(TransactionDeque t) ;
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param transaction [description]
 * @return [description]
 */
int get_index(Transaction transaction) ;

int get_nb_total_transactions(TransactionDeque transactions) ;

void hash_Merkle_tree(TransactionDeque transactions, char hash[]) ;

void display_info(TransactionDeque t) ;

#endif



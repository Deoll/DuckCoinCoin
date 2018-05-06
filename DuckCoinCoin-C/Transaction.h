#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#define MAX_VALUE 10 

/**
 * @Getter on the current Date
 * 
 */
char *getTimeStamp(void) ;
/**
 * @Transaction structure 
 * 
 */
typedef struct s_transaction *Transaction ;
/**
 * @Transaction structure 
 */
typedef struct s_transactionDeque *TransactionDeque ;
/**
 * @brief Initialisation of the genesis's block transactionDeque 
 * 
 * @return transactionDeque of genesis block
 */
TransactionDeque transaction_genesis() ;
/**
 * @brief Create a new random transaction
 * @details create a string "Source-Destination : "+ a random number and stock it into trans
 */
void create_transaction(char trans[512]) ;
/**
 * @brief initialisation of a transactionDeque struct
 * 
 * @return an empty transactionDeque
 */
 TransactionDeque init_transaction_deque() ;
/**
 * @brief Calculate the hash of transaction 
 * 
 * @param transaction the transaction to calcul
 */
void set_hash_transaction(Transaction  transaction) ;
/**
 * @brief getter on srcDest of the first Transaction of the transactionDeque
 * 
 */
char * getSrcDest(TransactionDeque t) ;
/**
 * @brief push a transaction to t
 * 
 * @param add a random transaction to this variable
 */
void add_transaction_to_transactionDeque(TransactionDeque t) ;
/**
 * @brief remove the transaction at index index from transactionDeque transation
 * 
 * @param transaction the transactionDeque to travel
 * @param intdex the index of transation to remove in transactionDeque transaction
 */
void remove_transaction(TransactionDeque transaction, int index) ;
/**
 * @brief delete the transactionDeque t
 * @details delete all the transactions of t then free memory allocated to the structure
 * 
 * @param t the transactionDeque to delete
 */
void delete_transaction_deque(TransactionDeque t) ;
/**
 * @brief getter on the index of transaction t
 */
int get_index(Transaction transaction) ;
/**
 * @brief getter on the number of transactions from transactionDeque transactions
 */
int get_nb_total_transactions(TransactionDeque transactions) ;
/**
 * @brief calculate the merkle tree root of transactions in hash
 * @details store the result of the hash merkle tree root in parameter hash
 * 
 * @param transactions permits to calculate the hash merkle tree root
 * @param hash storing the result
 */
void hash_Merkle_tree(TransactionDeque transactions, char hash[]) ;
/**
 * @brief display infos of transactionDeque t
 * @details only use for tests
 * 
 * @param t the transactionDeque to display
 */
void display_info(TransactionDeque t) ;

#endif



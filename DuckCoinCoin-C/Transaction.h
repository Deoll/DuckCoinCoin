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
 * @TransactionDeque structure 
 */
typedef struct s_transactionDeque *TransactionDeque ;
/**
 * @brief Initialisation of the genesis's block TransactionDeque 
 * 
 * @return transactionDeque of genesis block
 */
TransactionDeque transaction_genesis() ;
/**
 * @brief Create a new random Transaction
 * @details create a string "Source-Destination : "+ a random number and stock it into trans
 */
void create_transaction(char trans[512]) ;
/**
 * @brief initialisation of a TransactionDeque struct
 * 
 * @return an empty TransactionDeque
 */
 TransactionDeque init_transaction_deque() ;
/**
 * @brief Calculate the hash of transaction 
 * 
 * @param transaction the Transaction to calcul
 */
void set_hash_transaction(Transaction  transaction) ;
/**
 * @brief getter on srcDest of the first Transaction of the TransactionDeque
 * 
 * @return srcDest of the first Transaction of TransactionDeque t
 */
char * getSrcDest(TransactionDeque t) ;
/**
 * @brief push a random Transaction to t
 * 
 * @param t add a random Transaction to this TransactionDeque
 */
void add_transaction_to_transactionDeque(TransactionDeque t) ;
/**
 * @brief remove the Transaction at index index from TransactionDeque transation
 * 
 * @param transaction the TransactionDeque to parcour
 * @param index the index of Transation to remove in TransactionDeque transaction
 */
void remove_transaction(TransactionDeque transaction, int index) ;
/**
 * @brief delete the TransactionDeque t
 * @details delete all the Transactions of t then free memory allocated to the structure
 * 
 * @param t the TransactionDeque to delete
 */
void delete_transaction_deque(TransactionDeque t) ;
/**
 * @brief getter on the index of Transaction t
 */
int get_index(Transaction transaction) ;
/**
 * @brief getter on the number of transactions from TransactionDeque transactions
 *
 * @return size of transactions
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
 * @brief display infos of TransactionDeque t
 * @details only use for tests
 * 
 * @param t the TansactionDeque to display
 */
void display_info(TransactionDeque t) ;

#endif



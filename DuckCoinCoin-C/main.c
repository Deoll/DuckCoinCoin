#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cheater.h"

int main(int argc, char const *argv[]) {
	srand(time(NULL));
	// VERSION QUI NE MARCHE PAS : ./test 2 3 4 n
	if (argc<5 || argc>7){
		printf("Usage :%s difficulté nbr_block nbr_transaction y/n(cheater) [si cheater : num_block_delete [num_trans_delete] ] \n",argv[0]);
		exit(5) ;
	}

	int diff = atoi(argv[1]) ;
	int nb_b = atoi(argv[2]) ;
	int nb_t = atoi(argv[3]) ;
	char cheater = argv[4][0] ;
	int num_block ;
	int num_trans ;
	(void)num_trans ;
	(void)num_block ;
	if (cheater == 'y'){
		if (argc > 5){
			num_block = atoi(argv[5]) ;
			if (argc == 7){
				num_trans = atoi(argv[6]) ;
			}
		}
		else {
			printf("Argument pour cheater : num_block_delete [num_trans_delete]\n");
			exit(6) ;
		}
	}

	printf(" Création de la blockchain avec difficulté de %d...\n",diff ) ;
	Blockchain blockchain = create_blockchain(diff) ;
	printf(" Done.\n") ;

	printf("\n ------------------------------------------------\n\n") ;

	printf(" Ajout de %d blocks avec %d transactions max à la blockchain...\n",nb_b,nb_t) ;
	Block b = get_block(blockchain,0) ;
	Block b2 ;
	for (int i = 1; i <= nb_b; ++i) {
		int r = (rand()%nb_t)+1;
		printf(" Ajout bloc n°%d avec %d transactions\n",i,r);
		TransactionDeque t = init_transaction_deque();
		for (int j = 0; j < r; ++j)
			add_transaction_to_transactionDeque(t) ;
		b2 = create_block(t,i,get_hash(b),get_difficulty(blockchain)) ;
		push_block(blockchain,b2) ;
		b = b2 ;
	}
	printf(" Done.\n") ;
	
	if (cheater == 'y'){
		if (num_trans == NULL){
			printf("\n ------------------------------------------------\n\n") ;
			printf(" Cheater de bloc, activate... \n") ;
			cheater_block(blockchain,num_block) ;
		}
		else{
			printf("\n ------------------------------------------------\n\n") ;
			printf(" Cheater de transaction, activate... \n") ;
			cheater_transaction(blockchain,num_block,num_trans) ;
		}
	}
	printf("\n ------------------------------------------------\n\n") ;
	printf(" Vérifier l'integrité de la blockchain (y/n): \t");
	char verif ;
	int v1,v2 ;
	if (scanf("%s",&verif)) {} // pour eviter le warning 
	if (verif =='y') {
		printf("\n Vérification n°1...\n");
		v1 = verification_1(blockchain) ;
		printf(" Done. Result: %d\n",v1);
		printf("\n ------------------------------------------------\n\n") ;
		printf(" Vérification n°2...\n");
		v2 = verification_2(blockchain) ;
		printf(" Done. Result: %d\n",v2);

	}
	

	printf("\n ------------------------------------------------\n\n") ;

	printf(" Suppression de la blockchain...\n") ;
	delete_Blockchain(blockchain) ;
	printf(" Done.\n") ;

	return 0;
}
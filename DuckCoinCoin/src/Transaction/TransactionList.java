package Transaction ; 
import java.util.ArrayList ; 
import java.util.Random ; 
import Sha256.HashUtil ; 

/**
 * Last update on 06/05/2018
 * @version version 1.0
 */
public class TransactionList {
	protected int nbTransactionsMax ; 
	protected ArrayList<Transaction>transactions ; 

	/**
	 * Create an empty TransactionList
	 */
	public TransactionList() {
		this.transactions=new ArrayList<Transaction>() ; 
	}

	/**
	 * @return number of transactions currently in transactions
	 */
	public int get_nbTransactions() {
		return transactions.size() ; 
	}

	/**
	 * @preconditions i>0
	 * @modify nbTransactionsMax
	 * @param i
	 * @postconditions nbTransactionsMax=i
	 */
	public void set_nbTransactionsMax(int i) {
		assert(i>0) :"Nb Transactions max must be>0" ; 
		this.nbTransactionsMax=i ; 
	}

	/**
	 * Add a transaction at the end of the list
	 * @preconditions transactions.size ()<nbTransactionsMax
	 * @modify transactions
	 * @param transaction
	 * @postconditions out transactions.size ()=in transactions.size()+1
	 */
	public void add_transaction(Transaction transaction) {
		assert(transactions.size()<nbTransactionsMax) :"You cannot have more than "+nbTransactionsMax+" transactions \n" ; 
		transactions.add(transaction) ; 
	}

	/**
	 * Fill the list with a random number of random transactions
	 * @throws Exception 
	 * @modify transactions
	 * @postconditions 0<=transactions.size ()<=nbTransactionsMax
	 */
	public void complete_list() throws Exception {
		int i ; 
		Transaction t=new Transaction("") ; 
		Random r=new Random() ; 
		int valeur=r.nextInt(nbTransactionsMax) ; 
		for (i=-1 ;  i<valeur ; ++i) {
			add_transaction(t.random_Transaction() ) ; 
		}
	}

	/**
	 * Calculate the hash of the root of the MerkleTree made with transactions
	 * @preconditions transactions.size()>0
	 * @return MerkleTreeRootHash
	 */
	public String hash_MerkleTree() {
		assert (!transactions.isEmpty() ) :"You cannot get the hash of an empty TransactionList" ; 

		ArrayList<String>HashList=new ArrayList<String>() ; 
		boolean impair=transactions.size() %2==1 ; 
		int lastUsedHash ; 

		// Initialize HashList
		for (int i=0 ; i<transactions.size() /2 ; i++) {
			HashList.add(HashUtil.applySha256(transactions.get(i*2).toString()+transactions.get(i*2+1).toString() ) ) ; 
		}

		// Duplicate last transaction when impair
		if (impair) {
			HashList.add(HashUtil.applySha256(transactions.get (
					transactions.size() -1).toString()+transactions.get(transactions.size() -1).toString() ) ) ; 
		}

		// Process on HashList until HashList.size ()=1
		while (HashList.size() !=1) {
			impair=HashList.size() %2==1 ; 
			lastUsedHash=0 ; 

			// Store Hash of concatenation of a pair of Hash
			for (int i=0 ; i<HashList.size() /2 ; i++) {	
				String temp=HashUtil.applySha256(HashList.get(i*2)+HashList.get(i*2+1) ) ; 
				HashList.remove(i) ; 
				HashList.add(i, temp) ; 
				lastUsedHash++ ; 
			}

			// Store Hash of duplicated last transaction when impair
			if (impair) {
				String temp=HashUtil.applySha256(
						HashList.get(HashList.size() -1)+HashList.get(HashList.size() -1) ) ; 
				HashList.remove(lastUsedHash) ; 
				HashList.add(lastUsedHash, temp) ; 
				lastUsedHash++ ; 
			}

			// Delete already used hash and resize HashList 
			for (int j=lastUsedHash ; j<=HashList.size() -1 ; j++) {
				HashList.remove(j) ; 
				HashList.trimToSize() ; 
			}
		}
		return HashList.get(0) ; 
	}	

	/**
	 * @param i
	 * @return the content of transactions.get (i) 
	 */
	public String toString (int i) {
		return transactions.get(i).toString() ; 
	}

	/* (non-Javadoc) 
	 * @see java.lang.Object#toString () 
	 * return all transactions into a specific format
	 */
	public String toString() {
		String display="" ; 
		for (int i=0 ;  i<transactions.size() ; i++) {
			display=display+"Transaction N°"+i+" "+transactions.get(i)+"\n" ; 
		}
		return display ; 
	}
}

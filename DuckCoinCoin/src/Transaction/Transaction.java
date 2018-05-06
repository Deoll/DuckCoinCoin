package Transaction ; 
import java.util.Random ; 

/**
 * Last update on 06/05/2018
 * @version version 1.0, Transaction is a basic String
 * Made to be used with TransactionList from the same package
 */
public class Transaction {
	protected static int MAX_VALUE=10000 ;  // Maximal value of a transaction
	private String transaction ; 

	/**
	 * Create a transaction containing the String given in parameter
	 * @param trans
	 */
	public Transaction(String trans) {
		this.transaction=trans ; 
	}

	/**
	 * @modify transaction
	 * @return this
	 * @postconditions transaction="Source-Destination : [value]" with 0<=value<=MAX_VALUE
	 */
	public Transaction random_Transaction() {

		// Generate a random value between 0 and MAX_VALUE
		Random r=new Random() ; 
		int valeur=r.nextInt(MAX_VALUE) ; 

		// Change transaction into a transaction with random value
		transaction="Source-Destination : "+valeur ; 
		return this ; 
	}

	/* (non-Javadoc) 
	 * @see java.lang.Object#toString() 
	 */
	public String toString() {
		return this.transaction ; 
	}

}

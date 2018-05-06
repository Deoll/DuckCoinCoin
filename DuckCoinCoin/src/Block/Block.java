package Block ;
import java.util.Date ;
import Sha256.* ;
import Transaction.* ;
import java.text.SimpleDateFormat ;

/**
 * Last update on 06/05/2018
 * Made to be used in the blockChain from the same package
 */
public class Block { 
	private int index ;
	private String timeStamp ; 
	private String hashPrev ;
	private int nbTransactions ; 
	private TransactionList transactions ;
	private String hashTreeRoot ;
	private String hashBlock ;
	private int nonce ;
	
	// Date format used to store timeStamp in a Block
	private static final SimpleDateFormat sdf=new SimpleDateFormat("dd.mm.yyyy HH:mm:ss") ;

	/**
	 * Constructor of a Block with initialized values
	 * @param transactions
	 * @param difficulty 
	 * The higher it is, longer will be the creation of a Block
	 */
	public Block(final TransactionList transactions, final int difficulty) {
		// Generating timeStamp to a specific format
		this.timeStamp=sdf.format(new Date() ) ;

		this.index=0 ; // Block position in chain
		this.hashPrev="0" ; 

		// List of transactions and associated data
		this.transactions=transactions ;
		this.nbTransactions=transactions.get_nbTransactions() ;
		this.hashTreeRoot=transactions.hash_MerkleTree() ;

		this.nonce=0 ; // Value allowing the current hash to change if it doesn't fit difficulty
		this.hashBlock=calcul_hashBlock() ;

		// The first block of a blockChain is not mined
		if(index !=0) minage(difficulty) ;
	}

	/**
	 * @return transactions
	 */
	public TransactionList getTransactions() {
		return transactions ;
	}

	/**
	 * @return nonce 
	 */
	public int getNonce() {
		return nonce ;
	}

	/**
	 * @return hashBlock
	 */
	public String getHashBlock() {
		return hashBlock ;
	}	

	/**
	 * @return hashTreeRoot
	 */
	public String getHashTreeRoot() {
		return hashTreeRoot ;
	}

	/**
	 * @return hashPrev
	 */
	public String getHashPrev() {
		return hashPrev ;
	}
	
	/**
	 * @modify this.hashPrev
	 * @param hashPrev
	 */
	public void setHashPrev(final String hashPrev) {
		this.hashPrev=hashPrev ;
	}

	/**
	 * @return index
	 */
	public int getIndex() {
		return index ;
	}
	
	/**
	 * @modify this.index
	 * @param index
	 */
	public void setIndex(final int index) {
		this.index=index ;
	}

	/**
	 * Set the number of 0 in hashBlock
	 * @preconditions hashBlock is not empty
	 * @modify nonce
	 * @param difficulty
	 * @postconditions for any i<difficulty, hashBlock[i]=0
	 */
	public void minage(final int difficulty) {
		assert(!hashBlock.isEmpty() ) ;
		int i=0 ;
		while(i<difficulty) {
			// Check the number of 0 of current hash
			if(hashBlock.charAt(i) !='0') {
				// Increment nonce and reassign a corresponding hash to the block if it doesn't satisfy difficulty
				++nonce ;
				this.hashBlock=calcul_hashBlock() ;
				// Reset i when a hash didn't fit
				i=0 ;
			}
			else++i ;
		}
	}

	/**
	 * @return hashBlock that correspond to current block data
	 */
	public String calcul_hashBlock() {
		return HashUtil.applySha256(index+timeStamp.toString()+hashPrev+nbTransactions+hashTreeRoot+nonce) ;
	}

	/* (non-Javadoc) 
	 * @see java.lang.Object#toString() 
	 * return a formated String to display some informations concerning the current block
	 */
	public String toString() {
		return "Block n°"+index+" created on "+timeStamp+"\nList of "
				+nbTransactions+" transactions.\nHash of current Block: "+hashBlock+" \n" ;
	}
}

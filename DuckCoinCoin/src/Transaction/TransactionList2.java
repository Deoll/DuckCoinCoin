package Transaction ; 
import java.security.SignatureException ; 
import java.util.ArrayList ; 
import java.util.Random ; 

import org.bitcoinj.core.Address ; 
import org.bitcoinj.core.ECKey ; 
import org.bitcoinj.core.NetworkParameters ; 

/**
 * Last update on 06/05/2018
 * @version version 2.0
 */
public class TransactionList2 extends TransactionList{
	private ArrayList<Address>address ; 

	@SuppressWarnings("deprecation") 
	private final NetworkParameters netParams=NetworkParameters.testNet() ; 

	/**
	 * Create a TransactionList with nbAddress in address
	 * @param nbAddress
	 */
	public TransactionList2(int nbAddress) {
		super() ; 
		this.address=new ArrayList<Address>() ; 
		generate_n_address(nbAddress) ; 
	}   

	/**
	 * Add nbAdrress to address
	 * @modify address
	 * @param nbAddress
	 */
	private void generate_n_address(int nbAddress) {
		for(int i=0 ; i<nbAddress ; i++) {
			address.add((new ECKey() ).toAddress(netParams) ) ; 
		}
	}

	/*(non-Javadoc) 
	 * @see Transaction.TransactionList#complete_list() 
	 * @preconditions nbTransactionsMax>1
	 * @modify address
	 * fill transactions with random transaction, random src and random dest
	 */
	public void complete_list() throws SignatureException{
		assert(nbTransactionsMax>1) :"You can't complete a list if nbTransactionsMax>1" ; 
		int src, dest, nbTrans, i ; 
		Random r=new Random() ; 
		nbTrans=r.nextInt(nbTransactionsMax) ; 
		for(i=-1 ; i<nbTrans ; i++) {
			src=r.nextInt(address.size() ) ;  // Random Address
			dest=r.nextInt(address.size() ) ;  // Random Address
			Transaction2 t=new Transaction2(transactions.size(), address.get(src), address.get(dest) ) ;  // Random Transaction
			if(t.signature_verification() ) add_transaction(t.randomTransaction() ) ; 
		}
	}

	/*(non-Javadoc) 
	 * @see Transaction.TransactionList#toString() 
	 * return the content of TransactionList2 with a specific format
	 */
	public String toString() {
		String display="Address repertory : "+address.toString()+"\nAll transactions :\n" ; 
		for(int i=0 ;  i<transactions.size() ; i++) {
			display=display+"Transaction N°"+i+" "+transactions.get(i)+"\n" ; 
		}
		return display ; 
	}
}
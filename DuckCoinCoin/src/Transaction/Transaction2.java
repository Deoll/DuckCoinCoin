package Transaction ; 
import java.util.Date ; 
import java.util.Random ; 
import java.security.SignatureException ; 
import java.text.SimpleDateFormat ; 

import org.bitcoinj.core.ECKey ; 
import org.bitcoinj.core.Address ; 

/**
 * Last update on 06/05/2018
 * @version version 2.0, Transaction2 is a structure combining different types of data
 * Made to be used with TransactionList2 from the same package
 */
public class Transaction2 extends Transaction {
	private String timestamp ; 
	private int value ; 
	private int index ; 
	private Address src ; 
	private Address dest ; 
	private String signSrc ; 
	private ECKey key ; 

	// Date format used to store timeStamp in a Block
	private static final SimpleDateFormat sdf=new SimpleDateFormat("dd.mm.yyyy HH:mm:ss") ; 

	/**
	 * Create a Transaction of the corresponding version with initialized values
	 * @param index
	 * @param src
	 * @param dest
	 */
	public Transaction2(int index, Address src, Address dest) {
		super(src.toString()+'-'+dest.toString() ) ; 
		this.index=index ;  
		this.src=src ; 
		this.dest=dest ; 
		key=new ECKey() ; 
		signSrc= key.signMessage(src.toString() ) ; 
		this.timestamp=sdf.format(new Date() ) ; 
	}

	/**
	 * display informations of a transaction corresponding to a specific format
	 */
	public void affiche_transaction_infos() {
		System.out.println("Transaction n°"+index+" :\nSource : "+src+"\nDestination : "+dest+"\nAdresse signée : "+signSrc+"\nDate : "+timestamp+"\nMontant : "+value) ; 
	}

	/*(non-Javadoc) 
	 * @see Transaction.Transaction#randomTransaction() 
	 * generate a random Transaction
	 * @modify value
	 * return this
	 */
	public Transaction2 randomTransaction() {
		Random r=new Random() ; 
		value=r.nextInt(MAX_VALUE) ; 
		return this ; 
	}

	/*(non-Javadoc) 
	 * @see Transaction.Transaction#toString() 
	 * return a String chain containing some informations of a transaction
	 */
	public String toString() {
		return(src+" envoie "+value+" Dcc à "+dest) ; 
	}


	/**
	 * Check transaction signature integrity
	 * @return true if signature correspond
	 * @throws SignatureException
	 */
	public boolean signature_verification() throws SignatureException {
		new ECKey() ; 
		ECKey keyFromSign=ECKey.signedMessageToKey(src.toString(), signSrc) ; 
		if(keyFromSign.getPublicKeyAsHex().equals(key.getPublicKeyAsHex() ) ) 
			return true ; 
		else
			return false ; 
	}



}
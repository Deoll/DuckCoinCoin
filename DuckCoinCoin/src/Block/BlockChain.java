package Block ;
import java.util.ArrayList ;

import Transaction.* ;

/**
 * Last update on 06/05/2018
 */
public class BlockChain {
	private final int difficulty ;
	private ArrayList<Block>blocks ;
	private final int version ;
	

	/**
	 * Create an initialized BlockChain with its first Block
	 * @param difficulty
	 * @param version 
	 */
	public BlockChain(final int difficulty, final int version) {
		this.blocks=new ArrayList<Block>() ;
		this.difficulty=difficulty ;
		this.version=version ;
		init_genesis() ;
	}

	/**
	 * Create the first block depending on the version of the BlockChain
	 * @preconditions version must be 1 or 2
	 * @modify blocks
	 * @postconditions blocks.size()=1
	 */
	private void init_genesis() {
		assert(version ==1 || version ==2) : "Version must be 1 or 2" ;
		TransactionList L ;	
		if(version ==1) {
			L=new TransactionList() ;
		} else {
			// First block list of transactions doesn't contain any address
			L=new TransactionList2(0) ;
		}
		// First block list of transaction only contains the transaction "Genesis"
		Transaction t=new Transaction("Genesis") ;
		L.add_transaction(t) ;
		Block b=new Block(L, difficulty) ;
		
		blocks.add(b) ;
	}
	
	/**
	 * Add a block to the end of blocks
	 * @modify blocks
	 * @param b
	 */
	public void push_block(Block b) {
		// Modify index of a block to fit its position in the BlockChain
		b.setIndex(this.blocks.size() ) ;
		
		// Current block HashPrev=Last Block in BlockChain HashBlock
		b.setHashPrev(this.blocks.get(this.blocks.size()-1).getHashBlock() ) ;
		
		// Block has been altered, it needs to be mine
		b.minage(difficulty) ;
		
		blocks.add(b) ;
	}
	
	/**
	 * Delete the block at index and rebuild BlockChain
	 * @preconditions blocks is not empty, 0<index<blocks.size() 
	 * @modify blocks
	 * @param index
	 * @throws Exception 
	 * @postconditions out blocks.size()=in block.size()-1
	 */
	public void remove_block_at(int index) throws Exception {
		assert(!blocks.isEmpty() ) : "You can't remove a block from an empty BlockChain\n" ;
		assert(index>=0) : "You cannot alter or delete the first block\n" ;
		assert(index<this.blocks.size() ) : "No block corresponding to this index\n" ;
		blocks.remove(index) ;
		rebuild_blockChain(index) ;
	}
	

	
	/**
	 * Fill the loading bar with a dot, add a CR regularly 
	 * @param i
	 * @param loadingBar
	 * @return loadingBar
	 * @postconditions loadingBar is not empty
	 */
	public String loading(final int i, String loadingBar) {
	    	loadingBar+="." ;
	    	if(i%20 ==0) loadingBar+="\n" ;
	    	return loadingBar ;
	}
	
	/**
	 * Create a full BlockChain with random Blocks depending on the version of the BlockChain
	 * @preconditions version must be 1 or 2, nbBlocks>0, nbAdr>0, nbTransMax>0
	 * @modify blocks
	 * @param nbBlocks 
	 * @param nbAdr
	 * @param nbTransMax
	 * @throws Exception 
	 * @postconditions blocks.size()=nbBlocs
	 */
	public void creating_blockchain(int nbBlocks, int nbAdr, int nbTransMax) throws Exception {
		assert(version ==1 || version ==2) : "Version must be 1 or 2" ;
		assert(nbBlocks>0 && nbAdr>0 && nbTransMax>0) : "Parameters should be>0" ;
     
		System.out.println("Creating BlockChain ") ;
        TransactionList L ;
        String loadingBar="" ;
        

        for(int i=1 ;i<nbBlocks ;i++) {
        	
        	// Show the loading bar while creating the BlockChain
        	System.out.print(loading(i, loadingBar) ) ;
        	
        	// Create a TransactionList depending of the chosen version
    		if(version ==1) {
    			L=new TransactionList() ;
    		} else {
    			L=new TransactionList2(nbAdr) ;
    		}
    		
    		// Generating a random TransactionList
            L.set_nbTransactionsMax(nbTransMax) ;
        	L.complete_list() ;
        	
        	// Add a Block to the BlockChain
            Block b=new Block(L, difficulty) ;
            this.push_block(b) ;
            
            // Clock to make Blocks timeStamps different
            try { 
            	Thread.sleep(1000) ;
            }
            catch(InterruptedException exception) { 
            	exception.printStackTrace() ;
            }   
        }

		// Check BlockChain integrity
		if(verif_1() && verif_2() ) System.out.println("\nDone") ;
		else throw new Exception("BlockChain integrity compromised") ;

	}
	
	/**
	 * Rebuild the BlockChain from indexBlock
	 * @preconditions blocks is not empty, 0<index<blocks.size() 
	 * @modify blocks 
	 * @param indexBlock
	 */
	private void rebuild_blockChain(int indexBlock) throws Exception {
		assert(!blocks.isEmpty() ) : "You can't rebuild an empty BlockChain\n" ;
		assert(indexBlock>=0) : "You cannot rebuild the firstBlock\n" ;
		assert(indexBlock<this.blocks.size() ) : "No block corresponding to this index\n" ;
		
		Block b ;
		String l="" ;
		System.out.println("Processing Rebuild") ;
		
		for(;indexBlock<this.blocks.size() ;indexBlock++) {
			
			// Show the loading bar while creating the BlockChain
			System.out.print(loading(indexBlock, l) ) ;
			
			// Modifying the current block 
			b=this.blocks.get(indexBlock) ;
			b.setIndex(indexBlock) ;
			// Link the current block to the one that must be its previous
			b.setHashPrev(this.blocks.get(b.getIndex()-1).getHashBlock() ) ;
			
			// Altered block needs to be mined
			b.minage(difficulty) ;
		}
		
		// Check BlockChain integrity
		if(verif_1() && verif_2() ) System.out.println("\nDone") ;
		else throw new Exception("BlockChain integrity compromised") ;
		
	}
	
	/**
	 * Display information of the BlockChain respecting a specific format
	 */
	public void all_blocks_display() {
		System.out.println("Blockchain contains "+this.blocks.size()+" blocks\n") ;
		for(Block b : this.blocks) {
			System.out.println(b.toString() ) ;
			
			/* Display all transactions
			 * CAUTION : If you got a high number of transaction can generate a heavy display
			 * (Disable by default, uncomment the line below to display) 
			 */
			// System.out.println(b.getTransactions().toString() ) ;
		}
	} 

	/* Integrity verifications */
	/**
	 * Verify BlockChain integrity
	 */
	public boolean verif_1() {
		
		// Verify that the first block correspond to its generation conditions
		Block b=blocks.get(0) ;
		if((b.getHashPrev().equals(0) ) &&
			(b.getTransactions().toString(0).equals("Genesis") ) &&
			(b.getNonce() ==0) ) {
			System.out.println("No genesis \n") ;
			return false ;
		}
		
		// Verify that Hash are correct
		for(int i=blocks.size()-1 ;i>0 ;i-- ) {
			
			// Verify that hashPrev of current block correspond to previous block hashBlock
			if(!blocks.get(i).getHashPrev().equals(blocks.get(i-1).getHashBlock() ) ) {
				System.out.println("Wrong hashPrev for Block n°"+i) ;
				return false ;
			}
			
			// Verify that data of current Block correspond to hashBlock
			if(!blocks.get(i).getHashBlock().equals(blocks.get(i).calcul_hashBlock() ) ) {
				// Show both hash when they are different
				System.out.println("HashBlock : "+blocks.get(i).getHashBlock() ) ;
				System.out.println("Data corresponding Hash : "+blocks.get(i).calcul_hashBlock() ) ;
				System.out.println("HashBlock doesn't fit its data for Block n°"+i) ;
				return false ;
			}
		}
		return true ;
	}
	
	/**
	 * Verify each Block integrity
	 */
	public boolean verif_2() {
		for(Block b : blocks) {
			if(!b.getHashTreeRoot().equals(b.getTransactions().hash_MerkleTree() ) ) {
				System.out.println("hashTreeRoot of Block n°"+b.getIndex()+" doesn't match his transaction List") ;
				return false ;
			}
		}
		return true ;
	}

}

package Main ; 
import Block.* ; 
import java.util.Scanner ; 
import Gson.* ;

/**
 * Last update on 06/05/2018
 */
public class Main {

	private static Scanner sc ; // Used to get keyboard entries

	public static void main(String[] args) throws Exception {

		sc=new Scanner(System.in) ; 

		System.out.println("Do you want to export a blockchain with Json?(y/n) ") ; 
		String str=sc.nextLine() ; 

		// If using an existing BlockChain
		if(str.compareTo("y") ==0 || str.compareTo("Y") ==0) {

			System.out.print("Enter the name of an existing file containing a blockchain :") ; 
			str=sc.nextLine() ; 

			// Display the BlockChain
			BlockChain B=BCJsonUtils.BCJsonReader(str) ; 
			B.all_blocks_display() ; 

			// Check BlockChain integrity
			if(B.verif_1() && B.verif_2() ) System.out.println("BlockChain passed integrity tests") ;
			else throw new Exception("BlockChain integrity compromised") ;

		}
		// Not using an existing BlockChain
		else {

			// Asking for parameters
			System.out.print("Enter difficulty : ") ; 
			int diff=sc.nextInt() ; 
			System.out.print("Enter number of block : ") ; 
			int nb_bloc=sc.nextInt() ; 
			System.out.print("Enter maximal number of transactions : ") ; 
			int nb_trans_max=sc.nextInt() ; 
			System.out.print("Enter number of addresses : ") ; 
			int adr=sc.nextInt() ; 

			// Ask version while users doesn't put a valid entry
			int ver ; 
			do{				
				System.out.print("What version do you want to use(1 or 2) : ") ; 
				ver=sc.nextInt() ; 
			}	
			while(1>ver || ver>2) ; 

			// Generating a new BlockChain using user's parameters, and displaying it
			BlockChain B=new BlockChain(diff, ver) ; 
			B.creating_blockchain(nb_bloc, adr, nb_trans_max) ; 
			B.all_blocks_display() ; 

			if(ver==1){
				// Store BlockChain with Json if user wants to using the chosen name to save it
				System.out.println("Do you want to store your blockchain with Json ?(y/n) ") ; 
				sc.nextLine() ; 
				str=sc.nextLine() ; 
				if(str.compareTo("y") ==0 || str.compareTo("Y") ==0) {
					System.out.print("Enter the namefile wanted to save your blockchain : ") ; 
					str=sc.nextLine() ; 
					BCJsonUtils.BCJsonWriter(B, str) ; 
				}
			}

			// Test removal of a block and rebuilding(Equivalent of C cheater) (Disable by default, uncomment below to try it) 
			/* 
			 * int test=1 ; // Test Corresponding to the index of removedBlock, 1 is the worst case concerning rebuild time
			 * B.remove_block_at(test) ; // Automatically rebuild BlockChain after removing a block
			 * 
			 * // Check integrity after cheating(removing) and rebuilding
			 * B.verif_1() ; 
			 * B.verif_2() ;  
			 *
			 * B.all_blocks_display() ;        
			 */
		}
		System.out.println("Done.") ; 
	}
}


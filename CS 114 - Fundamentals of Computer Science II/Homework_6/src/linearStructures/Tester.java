package linearStructures;

import linearStructures.lists.*;
import linearStructures.queues.*;
import linearStructures.stacks.*;
//import linearStructures.queues.*;

public class Tester {
	
	/** Print list with position **/
	public static <E> void printList(ListADT<E> L) {
		// Save current position
		int curr = L.currPos();
		
		// String for list printout
		String out = new String("< ");
		int i = 0;
		for (L.moveToStart(); !L.isAtEnd(); L.next()) {	
			// If this is the current position, add position indicator
			if (curr == i) { out += "| "; }
			// Add current value to out string
			E it = L.getValue();
			out += (it + " ");
			++i;
		}
		// if position is at end 
		if (curr == L.length()) { out+="| "; }
		// End printout
		out += ">";
		
		//print
		System.out.println(out);
		
		// return list structure to previous state
		L.moveToPos(curr);
	}
    
    public static void main(String[] args) {
    	
    	System.out.println(Hw6.isPalindrome("pop"));
    	System.out.println(Hw6.isPalindrome("top"));
    	
    	StackADT<Integer> arrS = new AStack<Integer>(5);
    	arrS.push(1);
    	arrS.push(2);
    	arrS.push(3);
    	arrS.push(4);
    	arrS.pop();
    	System.out.println(arrS);
    	// Should print: 3 2 1
    	
    	
    	StackADT<Integer> listS = new LStack<Integer>(5);
    	listS.push(10);
    	listS.push(20);
    	listS.push(30);
    	listS.push(40);
    	listS.pop();
    	System.out.println(listS);
    	// Should print: 30 20 10
    	
    	QueueADT<Integer> listQ = new LQueue<Integer>(4);
    	listQ.enqueue(1);
    	listQ.enqueue(2);
    	listQ.enqueue(3);
    	listQ.enqueue(4);
    	listQ.dequeue();
    	listQ.dequeue();
    	listQ.enqueue(5);
    	System.out.println(listQ);
    	// Should print: 3 4 5
    	
    	QueueADT<Integer> arrQ = new AQueue<Integer>(4);
    	arrQ.enqueue(10);
    	arrQ.enqueue(20);
    	arrQ.enqueue(30);
    	arrQ.enqueue(40);
    	arrQ.dequeue();
    	arrQ.dequeue();
    	arrQ.enqueue(50);
    	arrQ.enqueue(60);
    	System.out.println(arrQ);
    	// Should print: 30 40 50 60
    	
    	
    }
    
    
    
}

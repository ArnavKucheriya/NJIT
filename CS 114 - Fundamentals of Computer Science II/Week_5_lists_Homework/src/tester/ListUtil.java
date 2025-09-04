package tester;

import lists.*;

public class ListUtil {
	
	/** Print list elements */
	public static <E> void simplePrint(ListADT<E> L) {
		String out = "";
		// Save current position
		int curr = L.currPos();
				
		for (L.moveToStart(); !L.isAtEnd(); L.next()) {	
			out += L.getValue() + " ";
		}
		
		System.out.println(out);
		
		// return list structure to previous state
		L.moveToPos(curr);
	}
	
	
	
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
}

package linearStructures;

import linearStructures.lists.*;
//import linearStructures.stacks.*;
//import linearStructures.queues.*;

public class Tester {

	public static void main(String[] args) {
		ListADT<Integer> l = new AList<Integer>();
		l.insert(10);
		l.insert(20);
		l.insert(30);
		System.out.println(l.currPos());
	}
}

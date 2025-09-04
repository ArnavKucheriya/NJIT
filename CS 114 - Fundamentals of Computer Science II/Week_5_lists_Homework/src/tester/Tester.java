package tester;

import lists.AList;
import lists.LList;
import lists.ListADT;

public class Tester {

	public static void main(String[] args) {
		
		listTests();
	}
	
	public static void listTests() {
		ListADT<Integer> l1 = new AList<>();
		l1.append(0);
		l1.append(1);
		l1.append(2);
		
		ListUtil.simplePrint(l1);
		ListUtil.printList(l1);
		
		ListADT<Integer> l2 = new AList<>();
		l2.append(1);
		l2.append(1);
		l2.append(2);
		l2.append(3);
		l2.append(5);
		l2.append(6);
		l2.next();
		l2.next();
		System.out.println(l2.currPos());
		System.out.println(ListMethods.isSorted(l2));
		System.out.println(l2.currPos()); // isSorted does not change the current position after call
	}
	
}

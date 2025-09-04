package dictionaries;

public class Tester {

	public static void bst_main(String[] args) {
		BSTDictionary<Integer, Integer> D = new BSTDictionary<>();
		
		D.insert(20, 20);
		D.insert(30, 30);
		D.insert(10, 10);
		D.insert(27, 27);
		D.insert(25, 25);
		D.insert(15, 15);
		D.insert(19, 19);
		D.insert(12, 12);
		D.insert(17, 17);
		D.insert(18, 18);
		D.insert(16, 16);
		
		D.printPreOrder();
		System.out.println();
		D.printInOrder();
		System.out.println();
		D.printPostOrder();
		System.out.println();
		
		D.remove(20);
		
		D.printPreOrder();
		System.out.println();
	}
	

}

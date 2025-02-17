package binaryTrees;

public class Tester {
	public static void main(String[] args) {
		// Creating the tree:
		/*
		 * 
		 *                   E
		 *                  / \ 
		 *                 B   C
		 *                / \   \
		 *               D   I   H
		 *                \     / \  
		 *                 A   F   J
		 *                    /
		 *                   G  
		 */
		
		BinNode<Integer> A = new TreeLink<>(8);
		BinNode<Integer> B = new TreeLink<>(12);
		BinNode<Integer> C = new TreeLink<>(10, A, B);
		BinNode<Integer> D = new TreeLink<>(7, C, null);
		BinNode<Integer> E = new TreeLink<>(1);
		BinNode<Integer> F = new TreeLink<>(50);
		BinNode<Integer> G = new TreeLink<>(5, E, D);
		BinNode<Integer> H = new TreeLink<>(30, null, F);
		BinNode<Integer> I = new TreeLink<>(20, G, H);

		// Construct a tree with preorder: 5, 7, 8, 20, 35, 31
		BinNode<Integer> root = new TreeLink<>(5);
		BinNode<Integer> left = new TreeLink<>(7);
		BinNode<Integer> right = new TreeLink<>(31);
		BinNode<Integer> leftLeft = new TreeLink<>(8);
		BinNode<Integer> rightLeft = new TreeLink<>(20);
		BinNode<Integer> rightRight = new TreeLink<>(35);
		root.setLeft(left);
		root.setright(right);
		left.setLeft(leftLeft);
		right.setLeft(rightLeft);
		right.setright(rightRight);

		// Construct a tree with postorder: 7, 35, 20, 31, 8, 5
		BinNode<Integer> root2 = new TreeLink<>(5);
		BinNode<Integer> left2 = new TreeLink<>(7);
		BinNode<Integer> right2 = new TreeLink<>(31);
		BinNode<Integer> leftLeft2 = new TreeLink<>(8);
		BinNode<Integer> rightLeft2 = new TreeLink<>(20);
		BinNode<Integer> rightRight2 = new TreeLink<>(35);
		root2.setLeft(left2);
		root2.setright(right2);
		left2.setLeft(leftLeft2);
		right2.setLeft(rightLeft2);
		right2.setright(rightRight2);

		// Construct a tree with inorder: 7, 8, 5, 20, 31, 35
		BinNode<Integer> root3 = new TreeLink<>(5);
		BinNode<Integer> left3 = new TreeLink<>(7);
		BinNode<Integer> right3 = new TreeLink<>(31);
		BinNode<Integer> leftLeft3 = new TreeLink<>(8);
		BinNode<Integer> rightLeft3 = new TreeLink<>(20);
		BinNode<Integer> rightRight3 = new TreeLink<>(35);
		root3.setLeft(left3);
		root3.setright(right3);
		left3.setLeft(leftLeft3);
		right3.setLeft(rightLeft3);
		right3.setright(rightRight3);

		/*
		 * Preorder: 20, 30, 5, 15, 40, 4, 24
		 * Postorder: 5, 15, 30, 24, 4, 40, 20
		 * Inorder: 5, 30, 15, 20, 4, 24, 40
		 */
	
		preOrder(E);
		System.out.println();
		inOrder(E);
		System.out.println();
		postOrder(E);
		System.out.println();
		
		System.out.println(countLevels(B));
	}
	
	
	
	
	public static <E> void preOrder(BinNode<E> rt) {
		
	}
	public static <E> void inOrder(BinNode<E> rt) {
		
	}
	public static <E> void postOrder(BinNode<E> rt) {
		
	}
	public static <T> int countLevels(BinNode<T> rt) {
		return 0;
	}
	

}

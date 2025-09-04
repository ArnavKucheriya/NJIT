package binaryTrees;

public class TreePrinter {
	public static <E> void preOrder(BinNode<E> rt) {
		if (rt!= null) {
			System.out.print(rt.value() + " ");
			preOrder(rt.left());
			preOrder(rt.right());
		}
	}
	
	public static <E> void postOrder(BinNode<E> rt) {
		if (rt!= null) {
			postOrder(rt.left());
			postOrder(rt.right());
			System.out.print(rt.value() + " ");
		}
	}
		
	public static <E> void inOrder(BinNode<E> rt) {
		if (rt != null) {
			inOrder(rt.left());
			System.out.print(rt.value() + " ");
			inOrder(rt.right());
		}
	}

	public static <T> int countLevels(BinNode<T> rt) {
		if (rt == null) {
			return 0;
		}
		int left = countLevels(rt.left());
		int right = countLevels(rt.right());
		return 1 + Math.max(left, right);
	}

	public static void main(String [] args){
		/*
		 * 5, 7 ,8, 20, 35, 31
		 * 7, 35 , 20, 31, 8, 5
		 * 7, 5, 20, 35, 8, 31
		 */
	}
}

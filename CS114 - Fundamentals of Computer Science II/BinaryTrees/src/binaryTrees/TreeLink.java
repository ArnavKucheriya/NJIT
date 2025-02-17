package binaryTrees;

public class TreeLink<E> implements BinNode<E>{

	E data;
	BinNode<E> leftChild;
	BinNode<E> rightChild;
	
	TreeLink(E value) {
		data = value;
	}
	
	TreeLink(E value, BinNode<E> left, BinNode<E> right) {
		data = value;
		leftChild = left;
		rightChild = right;
	}
	
	@Override
	public E value() {
		return data;
	}

	@Override
	public void setValue(E v) {
		data = v;
	}

	@Override
	public BinNode<E> left() {
		return leftChild;
	}

	@Override
	public BinNode<E> right() {
		return rightChild;
	}

	@Override
	public boolean isLeaf() {
		if (leftChild == null && rightChild == null) {
			return true;
		} else {
			return false;
		}
	}

	@Override
	public void setLeft(BinNode<E> l) {
		leftChild = l;
	}

	@Override
	public void setright(BinNode<E> r) {
		rightChild = r;
		
	}

}

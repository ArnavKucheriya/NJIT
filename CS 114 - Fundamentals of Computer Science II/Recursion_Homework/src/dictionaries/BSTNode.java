package dictionaries;

//Binary tree node implementation: supports comparable objects
/**
 * Binary tree node implementation: Pointers to children
 * 
 * @param E The data element
 * @param K The associated key for the record
 */
class BSTNode<K extends Comparable<K>, E> {
	private K key; // Key for this node
	private E element; // Element for this node
	private BSTNode<K, E> left; // Pointer to left child
	private BSTNode<K, E> right; // Pointer to right child

	/** Constructors */
	public BSTNode() {
		left = right = null;
	}

	public BSTNode(K key, E val) {
		left = right = null;
		this.key = key;
		element = val;
	}

	public BSTNode(K key, E val, BSTNode<K, E> l, BSTNode<K, E> r) {
		left = l;
		right = r;
		this.key = key;
		element = val;
	}

	/** Get and set the key value */
	public K key() {
		return key;
	}

	public void setKey(K key) {
		this.key = key;
	}

	/** Get and set the element value */
	public E element() {
		return element;
	}

	public void setElement(E v) {
		element = v;
	}

	/** Get and set the left child */
	public BSTNode<K, E> left() {
		return left;
	}

	public void setLeft(BSTNode<K, E> p) {
		left = p;
	}

	/** Get and set the right child */
	public BSTNode<K, E> right() {
		return right;
	}

	public void setRight(BSTNode<K, E> p) {
		right = p;
	}

	/** @return True if a leaf node, false otherwise */
	public boolean isLeaf() {
		return (left == null) && (right == null);
	}
}

package dictionaries;

//Dictionary implementation using BST
//This uses KVPair to manage the key/value pairs
public class BSTDictionary<K extends Comparable<K>,E> implements DictionaryADT<K,E> {
	private BSTNode<K, E> root; // Root of the BST
	private int nodecount; // Number of nodes in the BST

// constructor
	BSTDictionary() {
		root = null;
		nodecount = 0;
	}

// Reinitialize tree
	public void clear() {
		root = null;
		nodecount = 0;
	}

// Insert a record into the tree.
// Records can be anything, but they must be Comparable
// e: The record to insert.
	public void insert(K key, E val) {
		root = inserthelp(root, key, val);
		nodecount++;
	}

// Remove a record from the tree
// key: The key value of record to remove
// Returns the record removed, null if there is none.
	public E remove(K key) {
		E temp = findhelp(root, key); // First find it if (temp != null) { root =
		removehelp(root, key); // Now remove it
		nodecount--;
		return temp;
	}

// Return the record with key value k, null if none exists
// key: The key value to find
	public E find(K key) {
		return findhelp(root, key);
	}

// Return the number of records in the dictionary
	public int size() {
		return nodecount;
	}
	
	private E findhelp(BSTNode<K, E> rt, K key) {
		if (rt == null)
			return null;
		if (rt.key().compareTo(key) > 0)
			return findhelp(rt.left(), key);
		// found it
		else if (rt.key().compareTo(key) == 0)
			return rt.element();
		else
			return findhelp(rt.right(), key);
	}
	 

	/**
	 * @return The current subtree, modified to contain the new item
	 */
	private BSTNode<K, E> inserthelp(BSTNode<K, E> rt, K key, E val) {
		if (rt == null)
			return new BSTNode<K, E>(key, val);
		if (rt.key().compareTo(key) > 0)
			rt.setLeft(inserthelp(rt.left(), key, val));
		else
			rt.setRight(inserthelp(rt.right(), key, val));
		return rt;
	}
	
	/**
	 * Remove a node with key value k
	 * 
	 * @return The tree with the node removed
	 */
	private BSTNode<K, E> removehelp(BSTNode<K, E> rt, K key) {
		if (rt == null) {
			return null;
		}
		if (rt.key().compareTo(key) > 0)
			rt.setLeft(removehelp(rt.left(), key));
		else if (rt.key().compareTo(key) < 0)
			rt.setRight(removehelp(rt.right(), key));
		else { // Found it
			// only right child
			if (rt.left() == null) {
				return rt.right();
			}
			//only left child
			else if (rt.right() == null) {
				return rt.left();
			}
			else { // Two children
				BSTNode<K, E> temp = getmax(rt.left());
				rt.setElement(temp.element());
				rt.setKey(temp.key());
				rt.setLeft(deletemax(rt.left()));
			}
		}
		return rt;
	}
	
	private BSTNode<K, E> getmax(BSTNode<K, E> rt) {
		if (rt.right() == null) {
			return rt;
		}
		return getmax(rt.right());
	}

	private BSTNode<K, E> deletemax(BSTNode<K, E> rt) {
		if (rt.right() == null) {
			return rt.left();
		}
		rt.setRight(deletemax(rt.right()));
		return rt;
	}

	@Override
	public E removeAny() {
		return (remove(root.key()));
	}
	
	///////////////////////////////////
	// Print BST //////////////////////
	///////////////////////////////////
	public void printPreOrder() {
		preOrder(root);
	}
	
	public void printInOrder() {
		inOrder(root);
	}
	
	public void printPostOrder() {
		postOrder(root);
	}
	
	private void preOrder(BSTNode<K, E> rt) {
		if (rt != null) {
			System.out.print(rt.key() + " ");
			preOrder(rt.left());
			preOrder(rt.right());
		}
	}
	private void inOrder(BSTNode<K, E> rt) {
		if (rt != null) {
			inOrder(rt.left());
			System.out.print(rt.key() + " ");
			inOrder(rt.right());
		}
	}
	private void postOrder(BSTNode<K, E> rt) {
		if (rt != null) {
			postOrder(rt.left());
			postOrder(rt.right());
			System.out.print(rt.key() + " ");
		}
	}
}
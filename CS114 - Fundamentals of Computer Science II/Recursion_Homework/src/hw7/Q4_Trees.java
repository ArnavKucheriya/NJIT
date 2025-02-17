package hw7;

public class Q4_Trees {
    // Binary tree node interface
    interface BinNode<E> {
        // Get and set the element value
        E value();
        void setValue(E v);

        // Return the children
        BinNode<E> left();
        BinNode<E> right();

        // Set the children
        void setLeft(BinNode<E> l);
        void setright(BinNode<E> r);

        // Return TRUE if a leaf node, FALSE otherwise
        boolean isLeaf();
    }

    // Concrete implementation of BinNode
    static class BinNodeImpl<E> implements BinNode<E> {
        private E value;
        private BinNode<E> left;
        private BinNode<E> right;

        // Constructor
        public BinNodeImpl(E value) {
            this.value = value;
            this.left = null;
            this.right = null;
        }

        @Override
        public E value() {
            return value;
        }

        @Override
        public void setValue(E v) {
            this.value = v;
        }

        @Override
        public BinNode<E> left() {
            return left;
        }

        @Override
        public BinNode<E> right() {
            return right;
        }

        @Override
        public void setLeft(BinNode<E> l) {
            this.left = l;
        }

        @Override
        public void setright(BinNode<E> r) {
            this.right = r;
        }

        @Override
        public boolean isLeaf() {
            return left == null && right == null;
        }
    }

    // Static trees T1 and T2
    static BinNode<Integer> T1;
    static BinNode<Integer> T2;

    /**
     * Constructs the trees T1 and T2 and prints them out in preorder, inorder, and postorder.
     */
    public static void constructTrees() {
        // Construct T1
        T1 = new BinNodeImpl<>(10);
        T1.setLeft(new BinNodeImpl<>(5));
        T1.setright(new BinNodeImpl<>(12));
        T1.left().setLeft(new BinNodeImpl<>(3));
        T1.right().setLeft(new BinNodeImpl<>(40));
        T1.right().setright(new BinNodeImpl<>(1));

        // Construct T2
        T2 = new BinNodeImpl<>(6);
        T2.setLeft(new BinNodeImpl<>(30));
        T2.setright(new BinNodeImpl<>(12));
        T2.left().setLeft(new BinNodeImpl<>(9));
        T2.right().setLeft(new BinNodeImpl<>(40));
        T2.right().setright(new BinNodeImpl<>(1));

        // Print trees in different orders
        System.out.println("T1 Preorder:");
        preOrder(T1);
        System.out.println("\nT1 Inorder:");
        inOrder(T1);
        System.out.println("\nT1 Postorder:");
        postOrder(T1);

        System.out.println("\nT2 Preorder:");
        preOrder(T2);
        System.out.println("\nT2 Inorder:");
        inOrder(T2);
        System.out.println("\nT2 Postorder:");
        postOrder(T2);
    }

    // Preorder traversal
    public static void preOrder(BinNode<Integer> node) {
        if (node == null) return;
        System.out.print(node.value() + " ");
        preOrder(node.left());
        preOrder(node.right());
    }

    // Inorder traversal
    public static void inOrder(BinNode<Integer> node) {
        if (node == null) return;
        inOrder(node.left());
        System.out.print(node.value() + " ");
        inOrder(node.right());
    }

    // Postorder traversal
    public static void postOrder(BinNode<Integer> node) {
        if (node == null) return;
        postOrder(node.left());
        postOrder(node.right());
        System.out.print(node.value() + " ");
    }

    /**
     * Counts the number of leaf nodes in the tree with root `rt`.
     */
    public static int countLeafs(BinNode<Integer> rt) {
        if (rt == null) {
            return 0; // Base case: empty tree
        }
        if (rt.isLeaf()) {
            return 1; // Base case: leaf node
        }
        return countLeafs(rt.left()) + countLeafs(rt.right()); // Recursive case
    }

    /**
     * Returns the evil twin of the tree by swapping left and right subtrees recursively.
     */
    static BinNode<Integer> evilTwin(BinNode<Integer> root) {
        if (root == null) {
            return null;
        }

        // Create evil twin recursively
        BinNode<Integer> left = evilTwin(root.left());
        BinNode<Integer> right = evilTwin(root.right());

        // Swap the left and right subtrees
        root.setLeft(right);
        root.setright(left);

        return root;
    }

    /**
     * Main method for testing the implementations.
     */
    public static void main(String[] args) {
        // Construct and print trees
        constructTrees();

        // Count leaf nodes in T1 and T2
        System.out.println("\nNumber of leaf nodes in T1: " + countLeafs(T1));
        System.out.println("Number of leaf nodes in T2: " + countLeafs(T2));

        // Create and print evil twin trees
        BinNode<Integer> evilTwinT1 = evilTwin(T1);
        System.out.println("\nEvil Twin of T1 Preorder:");
        preOrder(evilTwinT1);

        BinNode<Integer> evilTwinT2 = evilTwin(T2);
        System.out.println("\nEvil Twin of T2 Preorder:");
        preOrder(evilTwinT2);
    }
}

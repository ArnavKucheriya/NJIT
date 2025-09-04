package heaps;

public class Tester {
    public static void main(String[] args) {
        // Task 1: Insert values into MaxHeap in different orders
        System.out.println("Task 1: Comparing Heaps from Two Insertion Orders");
        MaxHeap<Integer> heap1 = new MaxHeap<>(50);
        heap1.insert(30);
        heap1.insert(20);
        heap1.insert(80);
        heap1.insert(40);
        heap1.insert(50);
        System.out.println("Heap 1: " + heap1.stringHeap());

        MaxHeap<Integer> heap2 = new MaxHeap<>(50);
        heap2.insert(80);
        heap2.insert(50);
        heap2.insert(40);
        heap2.insert(30);
        heap2.insert(20);
        System.out.println("Heap 2: " + heap2.stringHeap());

        // Task 2: deleteMax called three times
        System.out.println("\nTask 2: deleteMax Three Times");
        MaxHeap<Integer> heap3 = new MaxHeap<>(50);
        heap3.insert(10);
        heap3.insert(40);
        heap3.insert(50);
        heap3.insert(5);
        heap3.insert(45);
        heap3.insert(30);
        heap3.insert(20);
        System.out.println("Initial Heap: " + heap3.stringHeap());
        heap3.removeMax();
        System.out.println("After 1st deleteMax: " + heap3.stringHeap());
        heap3.removeMax();
        System.out.println("After 2nd deleteMax: " + heap3.stringHeap());
        heap3.removeMax();
        System.out.println("After 3rd deleteMax: " + heap3.stringHeap());

        // Task 3: Leaf indices for a heap with 13 nodes
        System.out.println("\nTask 3: Leaf Indices for Heap with 13 Nodes");
        int[] leaves = getLeafIndices(13);
        System.out.print("Leaf Indices: ");
        for (int leaf : leaves) {
            System.out.print(leaf + " ");
        }
        System.out.println();

        // Task 4: Parent and child indices
        System.out.println("\nTask 4: Parent and Child Indices for Index 22");
        System.out.println("Parent Index: " + MaxHeap.parent(22));
        System.out.println("Left Child Index: " + MaxHeap.leftChild(22));
        System.out.println("Right Child Index: " + MaxHeap.rightChild(22));

        // Task 5: Check if array represents a MaxHeap
        System.out.println("\nTask 5: Is Array a MaxHeap?");
        int[] array = {100, 50, 80, 30, 20, 60, 70};
        System.out.println("Array: [100, 50, 80, 30, 20, 60, 70]");
        System.out.println("Is MaxHeap: " + isMaxHeap(array));

        // Task 6: BuildHeap demonstration
        System.out.println("\nTask 6: BuildHeap Demonstration");
        Integer[] buildArray = {100, 50, 7, 80, 5, 20, 30, 10, 70, 60};
        MaxHeap<Integer> buildHeap = new MaxHeap<>(buildArray, buildArray.length, 50);
        System.out.println("Heap after BuildHeap: " + buildHeap.stringHeap());
    }

    // Method to determine leaf indices for a given heap size
    public static int[] getLeafIndices(int size) {
        int firstLeaf = size / 2;
        int[] leaves = new int[size - firstLeaf];
        for (int i = firstLeaf; i < size; i++) {
            leaves[i - firstLeaf] = i;
        }
        return leaves;
    }

    // Method to check if an array represents a MaxHeap
    public static boolean isMaxHeap(int[] array) {
        for (int i = 0; i < array.length / 2; i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if ((left < array.length && array[i] < array[left]) ||
                (right < array.length && array[i] < array[right])) {
                return false;
            }
        }
        return true;
    }
}

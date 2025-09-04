package hw7;

public class Q3_RecList {
    Link head;

    public void append(int e) {
        if (head == null) {
            head = new Link(e);
        } else {
            recAppend(head, e);
        }
    }

    /**
     * Helper function for append
     */
    private void recAppend(Link curr, int e) {
        if (curr.next == null) {
            curr.next = new Link(e);
        } else {
            recAppend(curr.next, e);
        }
    }

    /**
     * Prints the list in format [ a0 a1 a2 a3 a4 ]
     * Where a0 is the integer at index 0, a1 is the integer at index 1 etc.
     */
    public void printList() {
        System.out.print("[ ");
        System.out.print(recPrint(head));
        System.out.println("]");
    }

    /**
     * Helper function for printList
     */
    private String recPrint(Link curr) {
        if (curr == null) {
            return ""; // Base case: empty list
        }
        if (curr.next == null) {
            return String.valueOf(curr.val); // Base case: last element
        }
        return curr.val + " " + recPrint(curr.next); // Recursive case
    }

    /*
     * Returns the index (0 based) of the first occurrence of e, if not found, return the size of the list
     * Example: find 4 in [ 2, 5, 4, 3, 4] returns 2
     * find 8 in [ 2, 5, 4, 3, 4] returns 5
     * find 4 in [] returns 0
     */
    public int find(int e) {
        if (head == null) {
            return 0; // Base case: empty list
        } else {
            return recFind(head, e, 0); // Recursive call
        }
    }

    /**
     * Helper function for find
     */
    private int recFind(Link curr, int e, int index) {
        if (curr == null) {
            return index; // Base case: end of list
        }
        if (curr.val == e) {
            return index; // Base case: element found
        }
        return recFind(curr.next, e, index + 1); // Recursive case
    }

    /**
     * Returns the sum of elements recursively
     * You cannot change this signature, however, you can use a helper recursive function
     */
    public int sumOfList() {
        return recSum(head); // Recursive helper function
    }

    private int recSum(Link curr) {
        if (curr == null) {
            return 0; // Base case: empty list
        }
        return curr.val + recSum(curr.next); // Recursive case
    }

    // Inner class Link
    class Link {
        int val = 0;
        Link next = null;

        Link(int n) {
            val = n;
        }

        Link(int n, Link next) {
            val = n;
            this.next = next;
        }
    }
	
/* 
    // Main method for testing
    public static void main(String[] args) {
        Q3_RecList list = new Q3_RecList();
        list.append(2);
        list.append(5);
        list.append(4);
        list.append(3);
        list.append(4);

        list.printList(); // [ 2 5 4 3 4 ]
        System.out.println("Find 4: " + list.find(4)); // 2
        System.out.println("Find 8: " + list.find(8)); // 5
        System.out.println("Sum of List: " + list.sumOfList()); // 18
    }
*/
}

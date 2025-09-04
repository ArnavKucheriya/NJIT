package tester;

import lists.ListADT;

public class ListMethods {

    /**
     * Returns the index of the first occurrence 'item' in l. If no such element, return -1.
     * @param <E> - Type of elements in ListADT
     * @param l - list to search
     * @param item - Item to find
     * @return index of first occurrence
     * 
     * THIS METHOD DOES NOT CHANGE THE LIST l
     * (so make sure currPos returns to its position before this method was called, 
     *  see printing methods)
     */
    public static <E> int find(ListADT<E> l, E item) {
        int initialPos = l.currPos();
        l.moveToStart();
        int index = 0;
        while (!l.isAtEnd()) {
            if (l.getValue().equals(item)) {
                l.moveToPos(initialPos);
                return index;
            }
            l.next();
            index++;
        }
        l.moveToPos(initialPos);
        return -1;
    }

    /**
     * Insert 'item' in position 'pos' of list l of type E
     * @return True if inserted, false if not. 
     * Position after insertion is at pos
     */
    public static <E> boolean insertIn(ListADT<E> l, E item, int pos) {
        if (pos < 0 || pos > l.length()) return false;
        int initialPos = l.currPos();
        l.moveToPos(pos);
        boolean result = l.insert(item);
        l.moveToPos(pos); // Move position to inserted position
        l.moveToPos(initialPos);
        return result;
    }

    /**
     * Return a list with all elements of l, in reverse order. 
     * If l is empty, returns empty list.
     * 
     * THIS METHOD DOES NOT CHANGE THE LIST l
     * 
     * This method runs in LINEAR time for BOTH implementations
     */
    public static <E> ListADT<E> getReversedList(ListADT<E> l) {
        ListADT<E> reversedList = new AList<>(l.length());
        int initialPos = l.currPos();
        l.moveToEnd();
        while (!l.isAtStart()) {
            l.prev();
            reversedList.append(l.getValue());
        }
        l.moveToPos(initialPos);
        return reversedList;
    }

    /**
     * Returns the first index of the first occurrence of sequence 'seq' in l. 
     * If not there, returns -1.  
     * 
     * THIS METHOD DOES NOT CHANGE THE LIST (including currPos)
     */
    public static int findSequence(ListADT<Integer> l, Integer[] seq) {
        int initialPos = l.currPos();
        int listSize = l.length();
        l.moveToStart();

        for (int i = 0; i <= listSize - seq.length; i++) {
            boolean match = true;
            for (int j = 0; j < seq.length; j++) {
                if (!l.getValue().equals(seq[j])) {
                    match = false;
                    break;
                }
                l.next();
            }
            if (match) {
                l.moveToPos(initialPos);
                return i;
            }
            l.moveToPos(i + 1);
        }

        l.moveToPos(initialPos);
        return -1;
    }

    /**
     * Returns true if the character 'first' appears before the character 'second' 
     * (there may be other characters in between)
     * 
     * THIS METHOD DOES NOT CHANGE THE LIST (including currPos) 
     */
    public static boolean isBefore(ListADT<Character> l, Character first, Character second) {
        int initialPos = l.currPos();
        boolean foundFirst = false;
        l.moveToStart();

        while (!l.isAtEnd()) {
            Character curr = l.getValue();
            if (curr.equals(first)) foundFirst = true;
            if (foundFirst && curr.equals(second)) {
                l.moveToPos(initialPos);
                return true;
            }
            l.next();
        }

        l.moveToPos(initialPos);
        return false;
    }

    /**
     * Returns true if the list is sorted in ascending order
     * 
     * THIS METHOD DOES NOT CHANGE THE LIST (including currPos)
     */
    public static <E extends Comparable<E>> boolean isSorted(ListADT<E> l) {
        int initialPos = l.currPos();

        if (l.isEmpty()) return true;

        l.moveToStart();
        E prev = l.getValue();
        l.next();

        while (!l.isAtEnd()) {
            E curr = l.getValue();
            if (prev.compareTo(curr) > 0) {
                l.moveToPos(initialPos);
                return false;
            }
            prev = curr;
            l.next();
        }

        l.moveToPos(initialPos);
        return true;
    }
}

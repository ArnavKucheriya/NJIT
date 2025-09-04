package linearStructures.stacks;

import java.util.LinkedList;

public class LStack<T> {
    private LinkedList<T> stack;

    /**
     * Constructor to initialize the linked list stack.
     */
    public LStack() {
        stack = new LinkedList<>();
    }

    /**
     * Adds an element to the top of the stack.
     * 
     * @param value the element to push onto the stack
     */
    public void push(T value) {
        stack.addFirst(value);
    }

    /**
     * Removes and returns the top element of the stack.
     * 
     * @return the top element, or null if the stack is empty
     */
    public T pop() {
        return stack.isEmpty() ? null : stack.removeFirst();
    }

    /**
     * Overrides toString() to print the stack with the top value on the left.
     * 
     * @return the string representation of the stack
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (T item : stack) {
            sb.append(item).append(" ");
        }
        return sb.toString().trim();
    }
}

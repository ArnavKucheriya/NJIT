package linearStructures.stacks;

import java.util.Arrays;

public class AStack<T> {
    private T[] data;
    private int size;

    /**
     * Constructor to initialize the stack with the given capacity.
     * 
     * @param capacity the maximum capacity of the stack
     */
    public AStack(int capacity) {
        data = (T[]) new Object[capacity];
        size = 0;
    }

    /**
     * Adds an element to the top of the stack.
     * 
     * @param value the element to push onto the stack
     */
    public void push(T value) {
        if (size < data.length) {
            data[size++] = value;
        }
    }

    /**
     * Removes and returns the top element of the stack.
     * 
     * @return the top element, or null if the stack is empty
     */
    public T pop() {
        if (size == 0) return null;
        return data[--size];
    }

    /**
     * Overrides toString() to print the stack with the top value on the left.
     * 
     * @return the string representation of the stack
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = size - 1; i >= 0; i--) {
            sb.append(data[i]).append(" ");
        }
        return sb.toString().trim();
    }
}

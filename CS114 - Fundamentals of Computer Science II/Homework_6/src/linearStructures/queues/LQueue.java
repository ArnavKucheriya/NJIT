package linearStructures.queues;

import java.util.LinkedList;

public class LQueue<T> {
    private LinkedList<T> queue;

    /**
     * Constructor to initialize the linked list queue.
     */
    public LQueue() {
        queue = new LinkedList<>();
    }

    /**
     * Adds an element to the rear of the queue.
     * 
     * @param value the element to add
     */
    public void enqueue(T value) {
        queue.addLast(value);
    }

    /**
     * Removes and returns the front element of the queue.
     * 
     * @return the front element, or null if the queue is empty
     */
    public T dequeue() {
        return queue.isEmpty() ? null : queue.removeFirst();
    }

    /**
     * Overrides toString() to print the queue with the front value on the left.
     * 
     * @return the string representation of the queue
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (T item : queue) {
            sb.append(item).append(" ");
        }
        return sb.toString().trim();
    }
}

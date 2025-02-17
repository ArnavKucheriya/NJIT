package linearStructures.queues;

public class AQueue<T> {
    private T[] data;
    private int front, rear, size, capacity;

    /**
     * Constructor to initialize the queue with the given capacity.
     * 
     * @param capacity the maximum capacity of the queue
     */
    public AQueue(int capacity) {
        this.capacity = capacity;
        data = (T[]) new Object[capacity];
        front = size = 0;
        rear = capacity - 1;
    }

    /**
     * Checks if the queue is full.
     * 
     * @return true if the queue is full, false otherwise
     */
    public boolean isFull() {
        return size == capacity;
    }

    /**
     * Checks if the queue is empty.
     * 
     * @return true if the queue is empty, false otherwise
     */
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * Adds an element to the rear of the queue.
     * 
     * @param value the element to add
     */
    public void enqueue(T value) {
        if (isFull()) return;
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
    }

    /**
     * Removes and returns the front element of the queue.
     * 
     * @return the front element, or null if the queue is empty
     */
    public T dequeue() {
        if (isEmpty()) return null;
        T item = data[front];
        front = (front + 1) % capacity;
        size--;
        return item;
    }

    /**
     * Overrides toString() to print the queue with the front value on the left.
     * 
     * @return the string representation of the queue
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size; i++) {
            sb.append(data[(front + i) % capacity]).append(" ");
        }
        return sb.toString().trim();
    }
}

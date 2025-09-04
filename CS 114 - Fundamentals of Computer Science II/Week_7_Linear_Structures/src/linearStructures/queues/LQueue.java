package linearStructures.queues;

//Linked queue implementation
class LQueue<E> implements QueueADT<E> {
	private Link<E> front; // Pointer to front queue node
	private Link<E> rear; // Pointer to rear queue node
	private int size; // Number of elements in queue

// Constructors
	LQueue() {
		init();
	}

	LQueue(int size) {
		init();
	} // Ignore size

// Initialize queue
	void init() {
		front = rear = new Link<E>(null);
		size = 0;
	}

// Put element on rear
	public boolean enqueue(E it) {
		rear.setNext(new Link<E>(it, null));
		rear = rear.next();
		size++;
		return true;
	}

// Remove and return element from front
	public E dequeue() {
		if (size == 0) {
			return null;
		}
		E it = front.next().element(); // Store the value
		front.setNext(front.next().next()); // Advance front
		if (front.next() == null) {
			rear = front;
		} // Last element
		size--;
		return it; // Return element
	}

// Return front element
	public E frontValue() {
		if (size == 0) {
			return null;
		}
		return front.next().element();
	}

// Return queue size
	public int length() {
		return size;
	}

//Tell if the queue is empty or not
	public boolean isEmpty() {
		return size == 0;
	}

	@Override
	public void clear() {
		init();
		
	}
}
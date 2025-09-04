package heaps;

public interface PriorityQueueADT<E extends Comparable <E>> {
	/**
	 * Returns top priority element and removes it
	 * If queue is empty returns null
	 *  */
	public E removeMax();
	
	/**
	 *  Insert an element to the queue, by priority
	 *  If queue is full element is not inserted, and  
	 *  */
	public boolean insert(E priority);
}

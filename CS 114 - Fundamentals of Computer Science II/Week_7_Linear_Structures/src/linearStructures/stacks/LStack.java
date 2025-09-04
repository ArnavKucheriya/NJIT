package linearStructures.stacks;

//Linked stack implementation
class LStack<E> implements StackADT<E> {
	private Link<E> top; // Pointer to first element
	private int size; // Number of elements

// Constructors
	LStack() {
		top = null;
		size = 0;
	}

	LStack(int size) {
		top = null;
		size = 0;
	}

// Reinitialize stack
	public void clear() {
		top = null;
		size = 0;
	}

//Put "it" on stack
	public boolean push(E it) {
		top = new Link<E>(it, top);
		size++;
		return true;
	}

//Remove "it" from stack
	public E pop() {
		if (top == null) {
			return null;
		}
		E it = top.element();
		top = top.next();
		size--;
		return it;
	}

	public E topValue() { // Return top value
		if (top == null) {
			return null;
		}
		return top.element();
	}

// Return stack length
	public int length() {
		return size;
	}

// Tell if the stack is empty
	public boolean isEmpty() {
		return size == 0;
	}
}
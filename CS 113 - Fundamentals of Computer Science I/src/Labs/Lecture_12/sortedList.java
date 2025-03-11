package Labs.Lecture_12;

public class sortedList extends IntList {
    public sortedList(int size) {
        super(size);
    }

    // Override the add method
    public void add(int value) {
        if (numElements == list.length)
            System.out.println("Can't add, list is full");
        else {
            int i = 0;
            // Index where the value should be inserted
            // Checks if the index value is less than length of the list
            // and if the value of the list at index i is less than the value
            while (i < numElements && list[i] < value)
                i++; // Incrementing the value of i (index value)

            // for loop decrementing the value of j to go through the list in a reverse order
            // Shift elements to the right
            int indexToInsert = i;
            for (int j = numElements; j > indexToInsert; j--)
                list[j] = list[j - 1]; // Shift elements to the right
            list[indexToInsert] = value; // Value of list at index i is set to the value
            numElements++; // Increasing the number of elements.
        }
    }
}

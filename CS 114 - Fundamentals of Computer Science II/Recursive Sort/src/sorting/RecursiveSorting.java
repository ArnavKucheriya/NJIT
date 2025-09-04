package sorting;

import java.util.ArrayList;

public class RecursiveSorting {
	/** This implementation uses (and reuses) temp as the auxiliary space */
	public static <T extends Comparable<T>> void mergesort
		(ArrayList<T> A, ArrayList<T> temp, int left, int right) {
		if (left == right) {
			return;
		} // List has one record
		int mid = (left + right) / 2; // Select midpoint
		mergesort(A, temp, left, mid); // Mergesort first half
		mergesort(A, temp, mid + 1, right); // Mergesort second half

		// copy array to temp, one element at a time
		for (int i = left; i <= right; i++) {
			temp.set(i, A.get(i));
		}
		// Do the merge operation back to A
		int i1 = left;
		int i2 = mid + 1;
		for (int curr = left; curr <= right; curr++) {
			if (i1 == mid + 1) { // Left sublist exhausted
				A.set(curr, temp.get(i2++));
			} else if (i2 > right) { // Right sublist exhausted
				A.set(curr, temp.get(i1++));
			} else if (temp.get(i1).compareTo(temp.get(i2)) <= 0) { // Get smaller value
				A.set(curr, temp.get(i1++));
			} else {
				A.set(curr, temp.get(i2++));
			}
		}
	}

	/**
	 * 
	 * @param <T>
	 * @param A
	 * @param left
	 * @param right
	 */
	public static <T extends Comparable<T>> void quicksort(ArrayList<T> A, int left, int right) { // Quicksort

		int pivotIndex = partition(A, left, right, A.get(right)); // return the index of the pivot after partition
		if ((pivotIndex - left) > 1) {
			quicksort(A, left, pivotIndex - 1);
		} // Sort left partition
		if ((right - pivotIndex) > 1) {
			quicksort(A, pivotIndex + 1, right);
		} // Sort right partition
	}

	/**
	 * Partition algorithm
	 * 
	 * @param <T>   - Comparable type
	 * @param A     - Array to partition
	 * @param l     - Left most index of array
	 * @param r     - Right most index of array
	 * @param pivot - Element to partition around
	 * @return index of pivot in partitioned array
	 */
	private static <T extends Comparable<T>> int partition(ArrayList<T> A, int l, int r, T pivot) {
		int pIndex = l;
		for (int i = l; i < r; i++) {
			if (A.get(i).compareTo(pivot) < 0) {
				swap(A, pIndex, i);
				++pIndex;
			}
		}
		swap(A, pIndex, r); // Put pivot in place
		return pIndex;
	}

	private static <T extends Comparable<T>> void swap(ArrayList<T> arr, int i1, int i2) {
		T temp = arr.get(i1);
		arr.set(i1, arr.get(i2));
		arr.set(i2, temp);
		
	}
}

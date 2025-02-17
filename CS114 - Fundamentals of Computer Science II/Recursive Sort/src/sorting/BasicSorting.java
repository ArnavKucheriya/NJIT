package sorting;

public class BasicSorting {
	/* Implementation on insertion sort*/
	public static <T extends Comparable<T>> void insertionSort(T[] arr) {
		for (int i = 1; i < arr.length; ++i) {
			for (int j = i; (j > 0) && (arr[j-1].compareTo(arr[j]) > 0); --j ) {
				swap(arr, j, j-1);
			}
		}
	}
	
	/* Implementation of bubble sort */
	public static <T extends Comparable<T>> void bubbleSort(T[] arr){
		for (int i = 0; i < arr.length; ++i) {
			for (int j = 1; j < arr.length - i; ++j ) {
				if (arr[j-1].compareTo(arr[j]) > 0) {
					swap(arr, j-1, j);
				}
			}
		}
	}	
	 /* Implementation of selection sort */
	public static <T extends Comparable<T>> void SelectionSort(T[] arr) {
		for (int i = 0; i < arr.length - 1; i++) {
			int maxInd = 0;
			for (int j = 1; j < arr.length - i; j++) {
				if (arr[j].compareTo(arr[maxInd]) > 0) {
					maxInd = j;
				}
			}
			swap(arr, maxInd, arr.length - i - 1);
		}
	}
	private static <T extends Comparable<T>> void swap(T[] arr, int i1, int i2) {
		T temp = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = temp;	
	}
}
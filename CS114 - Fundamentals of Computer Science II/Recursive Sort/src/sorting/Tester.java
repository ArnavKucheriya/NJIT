package sorting;

import java.util.ArrayList;
import java.util.Collections;

public class Tester {

	public static void main(String[] args) {
		
		// Create an array of cards
		ArrayList<Integer> arr1 = new ArrayList<Integer>();
		arr1.add(8);
		arr1.add(10);
		arr1.add(5);
		arr1.add(2);
		arr1.add(20);
		arr1.add(15);
		arr1.add(3);
		arr1.add(4);
		arr1.add(7);
		// temp space for merge sort
		ArrayList<Integer> temp = new ArrayList<Integer>(Collections.nCopies(arr1.size(), null));
		
		// print unsorted array
		System.out.println("Unsorted: " + arr1.toString());
		
		//Sort array in any method
		//RecursiveSorting.quicksort(arr1, 0, arr1.size()-1);
		RecursiveSorting.mergesort(arr1, temp, 0, arr1.size()-1); 
		//RecursiveSorting.quicksort(arr1, 0, arr1.size()-1);
		//BasicSortings.bubbleSort(arr1);
		// print sorted array
		System.out.println("Sorted: "+ arr1.toString());
		
	}
}
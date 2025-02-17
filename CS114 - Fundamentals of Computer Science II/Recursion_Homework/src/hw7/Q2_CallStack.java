package hw7;

import java.util.ArrayList;

public class Q2_CallStack {
	public static void A (int a) {
		int r = a + 4;
	}
	
	public static int B (int b) {
		b = b + 1;	
		B2(b);
		return b;
	}
	
	public static int B2 (int b) {
		return b + 1;
	}
	
	public static void C (ArrayList<Integer> arr) {
		arr.add(12);
	}
	
	public static ArrayList<Integer> D (ArrayList<Integer> arr) {
		arr.add(20);
		arr.add(30);
		return arr;
	}
	
	public static ArrayList<Integer> E (ArrayList<Integer> arr) {
		arr.add(40);
		arr = new ArrayList<>();
		arr.add(50);
		return arr;
	}
}

public class Triangular {

	public static void main(String[] args) {
		triangularRec(12);

	}
	/**
	 * Recursively prints all the triangular numbers 1 to n
	 */
	public static void triangularRec(int n) {
		triangularHelper(n);
	}
	
	/**
	 * Recursively computes the nth triangular number, by adding n to the previous triangular number.
	 */
	private static int triangularHelper(int n) {
		int nth_triangular;
		//Base case
		if (n == 1) {
			nth_triangular = 1;
		}
		//Recursive step
		else
		{
			nth_triangular = n + triangularHelper(n-1);
		}
		//Print out 
		System.out.print(nth_triangular + " ");
		// return
		return nth_triangular;
	}

}

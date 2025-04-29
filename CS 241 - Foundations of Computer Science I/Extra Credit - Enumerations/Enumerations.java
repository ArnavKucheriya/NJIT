public class Enumerations {

	public static void main(String[] args) {
		// test cases
		Enumerations.integers(17);
		System.out.println();
		Enumerations.integersRec(17);
		System.out.println();
		Enumerations.rationalsRec(10);
		System.out.println();
		Enumerations.rationalBijection(10);
	}

	/** ITERATIVE bijection N -> Z */
	public static void integers(int n) {
		for (int i = 0; i <= n; i++) {
			int val;
			if (i == 0) val = 0;
			else if (i % 2 == 1) val = (i + 1) / 2;
			else val = -(i / 2);
			System.out.print(val);
			if (i != n) System.out.print(" -> ");
		}
		System.out.println(" -> End");
	}

	/** RECURSIVE bijection N -> Z */
	public static void integersRec(int n) {
		integersRecHelper(0, n);
		System.out.println(" -> End");
	}

	private static void integersRecHelper(int current, int n) {
		if (current > n) return;
		int val;
		if (current == 0) val = 0;
		else if (current % 2 == 1) val = (current + 1) / 2;
		else val = -(current / 2);
		System.out.print(val);
		if (current != n) System.out.print(" -> ");
		integersRecHelper(current + 1, n);
	}

	/** RECURSIVE surjection N -> Q+ */
	public static void rationalsRec(int n) {
		rationalsRecHelper(2, 1, n, 1);
		System.out.println(" -> End");
	}

	private static void rationalsRecHelper(int sum, int i, int n, int count) {
		if (count > n) return;
		if (i <= sum) {
			System.out.print(new pair(sum - i + 1, i));
			if (count != n) System.out.print(" -> ");
			rationalsRecHelper(sum, i + 1, n, count + 1);
		} else {
			rationalsRecHelper(sum + 1, 1, n, count);
		}
	}

	/** RECURSIVE bijection N -> Q+ (reduced only) */
	public static void rationalBijection(int n) {
		rationalBijectionHelper(2, 1, 0, n);
		System.out.println(" -> End");
	}

	private static void rationalBijectionHelper(int sum, int i, int count, int n) {
		if (count >= n) return;
		if (i <= sum) {
			int a = sum - i + 1;
			int b = i;
			if (gcd(a, b) == 1) {
				System.out.print(new pair(a, b));
				count++;
				if (count != n) System.out.print(" -> ");
			}
			rationalBijectionHelper(sum, i + 1, count, n);
		} else {
			rationalBijectionHelper(sum + 1, 1, count, n);
		}
	}

	private static int gcd(int a, int b) {
		if (b == 0) return a;
		return gcd(b, a % b);
	}
}

/** Pair of integers */
class pair {
	int x_coord;
	int y_coord;
	public pair(int x, int y){
		x_coord = x;
		y_coord = y;
	}
	@Override
	public String toString() {
		return "("+ x_coord + "," + y_coord + ")";
	}
}
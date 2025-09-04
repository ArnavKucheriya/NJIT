import java.util.ArrayList;

public class App {
    public static void main(String[] args) throws Exception {
        int a=7;
        int b=3;
        System.out.println(a);
        
        int c = funcA(a);
        System.out.println(c);

        ArrayList<Integer> arr1 = new ArrayList<>();
        ArrayList<Integer> arr2 = new ArrayList<>();
        arr2.add(32);
        arr1.size();

        arr2 = funcD(arr1); //Adress of B referes to the new ArrayList

        arr2 = new ArrayList<Integer>(); //Creating a new ArrayList: Causing the ArrayList with value 17 to be lost in the Heap, where the Garbage Collector will remove it.

        ArrayList A = new ArrayList<Integer>();
        A.add(1);
        A.add(2);
        A.add(3);

        ArrayList B = A;
        B = func1(A);
        System.out.println(A);
        System.out.println(B);
    }
    public static int funcA(int x){
        int y = x+10;
        return y;
    }
    public static int funcB(ArrayList<Integer> arr){
        arr.add(3);
        arr.add(4);
        arr.add(5);
        return arr.size();
    }
    public static ArrayList<Integer> funcD(ArrayList<Integer> B){
        B.add(64); //Added into the old ArrayList
        B = new ArrayList<>(); //Created a new ArrayList
        B.add(17); //Added into the new ArrayList
        return B; //Reurning the Address of the New ArrayList
    }
    public static ArrayList<Integer> func1(ArrayList<Integer> L1){
        L1.remove(0);
        L1 = new ArrayList<>();

        ArrayList<Integer> C = new ArrayList<>();
        C.add(25);
        C.add(26);

        return L1;
    }
}

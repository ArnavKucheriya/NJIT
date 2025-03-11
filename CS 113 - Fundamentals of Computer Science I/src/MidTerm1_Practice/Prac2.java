package MidTerm1_Practice;

public class Prac2 {
    public static void main(String[] args) {
/*        int[] arr = {1, 2, 3, 4, 5};
        for (int i : arr){
            System.out.print(arr[i]);
            i--;
        }*/

        int[] list1 = {1, 0, 1};
        int[] list2 = {0, 1, 0};
        list2 = list1;
        list1[0] = 0; list1[1] = 1; list2[2] = 2;
        for (int i = 0; i < list1.length; i++)
            System.out.print(list1[i] + " ");
    }
}

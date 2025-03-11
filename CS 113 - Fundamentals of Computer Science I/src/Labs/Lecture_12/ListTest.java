package Labs.Lecture_12;
// ***************************************************************
// ListTest.java
//
// A simple test program that creates an IntList, puts some
// ints in it, and prints the list.
//
// ***************************************************************
public class ListTest
{
    public static void main(String[] args)
    {
        IntList myList = new IntList(10);
        myList.add(100);
        myList.add(50);
        myList.add(200);
        myList.add(25);
        System.out.println(myList);

        IntList yourList = new sortedList(10);
        yourList.add(100);
        yourList.add(50);
        yourList.add(35);
        yourList.add(200);
        yourList.add(25);
        yourList.add(75);
        yourList.add(125);
        yourList.add(5);
        yourList.add(2);
        yourList.add(122);
        System.out.println(yourList);
    }
}

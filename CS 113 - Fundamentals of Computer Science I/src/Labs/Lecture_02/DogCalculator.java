package Labs.Lecture_02;

// Calculate the age of the dog from input into human years.

import java.util.*;
public class DogCalculator {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the age of the dog: ");
        int dogAge = input.nextInt();

        int humanAge = dogAge * 7;
        System.out.println("The age of the dog is: "+dogAge+"\nThe age of the dog in human age is: "+humanAge+ " years.");
    }
}

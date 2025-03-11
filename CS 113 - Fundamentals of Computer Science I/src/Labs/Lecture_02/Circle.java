package Labs.Lecture_02;
// ************************************************************
// Circle.java
// Author: Arnav Kucheriya
// Lab: CS 113
// Print the area of a circle with two different radii
// ************************************************************
import java.util.*;
public class Circle
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter two values for the radii: ");
        int radius1 = input.nextInt();
        int radius2 = input.nextInt();

        areaCalculation(radius1, radius2);
        circumferenceCalculation(radius1, radius2);
    }
    public static void areaCalculation(int radius1, int radius2){
        final double PI = 3.14159; //Value of Pi is defined

        double area1 = PI * radius1 * radius1;
        System.out.println("The area of a circle with radius " + radius1 + " is " + area1);

        double area2 = PI * radius2 * radius2;
        System.out.println("The area of a circle with radius " + radius2 + " is " + area2);
    }
    public static void circumferenceCalculation(int radius1, int radius2){
        final double PI = 3.14159; //Value of Pi is defined

        double circumference1 = 2 * PI * radius1;
        System.out.println("The circumference of the circle with radius "+radius1+" is "+circumference1);

        double circumference2 = 2 * PI * radius2;
        System.out.println("The circumference of the circle with radius "+radius1+" is "+circumference2);
    }

}
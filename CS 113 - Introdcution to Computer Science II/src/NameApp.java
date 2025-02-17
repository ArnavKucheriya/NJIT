/**
 * @author Arnav Kucheriya
 */

import java.util.*;
public class NameApp {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter your First Name: "); // Prompt the User for their First Name
        String FirstName = input.next(); // Take Input from the user

        System.out.print("Enter your Last Name: "); // Prompt the User for thier Last Name
        String LastName = input.next(); // Take input from the user

        char FirstInitial = FirstName.charAt(0); // Finding the Character Value of FirstName at index 0
        char LastInitial = LastName.charAt(0); // Finding the Character Value of LastName at index 0
        String nameInitials = Character.toString(FirstInitial).toUpperCase() + Character.toString(LastInitial).toUpperCase(); // Casting the char values to string and toUppercase()
        System.out.println("Initials:" + nameInitials); // Printing the initials

        String nameFull = FirstName + LastName; // Concatinate the String to make 1 complete string
        double nameAverage = (double) nameFull.length() / 2; // Find the length of the string then take the average
        System.out.println("Average Length: " + nameAverage); // Printing the average value


    }
}

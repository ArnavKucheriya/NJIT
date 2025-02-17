package Labs.Lecture_02;
import java.util.*;
public class Lec_02_MPG {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the miles driven by the car: ");
        double miles = input.nextDouble();
        System.out.print("Enter the gallons of fuel in the car: ");
        double gallons = input.nextDouble();

        double mpg = (miles/gallons);
        System.out.println("The Miles per Gallon (MPG) is: "+mpg);
    }
}

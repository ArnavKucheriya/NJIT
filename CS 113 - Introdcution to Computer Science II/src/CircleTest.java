import java.util.Scanner;
public class CircleTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Create two Point objects
        Point point1 = new Point((int) (Math.random() * 20) + 1, (int) (Math.random() * 20) + 1);
        Point point2 = new Point(0, 0);

        // Instantiate two Circle objects
        System.out.print("Enter radius for Circle 1: ");
        int radius1 = scanner.nextInt();

        // Creating a new circle object and initializing its intake parameters
        Circle circle1 = new Circle(point1, radius1);

        // Creating a new Circle with radius of 5
        Circle circle2 = new Circle(point2, 5);

        // Print the summary of each circle
        System.out.println("Circle 1: " + circle1.toString());
        System.out.println("Circle 2: " + circle2.toString());

        // Check if circles are equal and print result
        if (circle1.equals(circle2)) {
            double distance = circle1.getCenter().distance(circle2.getCenter());
            System.out.println("The distance between their centers is: " + distance);
        } else {
            double averageCircumference = (circle1.circumference() + circle2.circumference()) / 2;
            System.out.println("The average circumference is: " + averageCircumference);
        }
        // Closing Scanner
        scanner.close();
    }
}

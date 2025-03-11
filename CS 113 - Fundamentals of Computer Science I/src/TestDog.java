import java.util.Scanner;

public class TestDog {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Number of dogs in the kennel: ");
        int numDogs = scanner.nextInt();
        scanner.nextLine(); // Consume the newline character

        double totalAge = 0;
        Dog oldestDog = null;

        for (int i = 1; i <= numDogs; i++) {
            System.out.print("Enter Dog breed for Dog " + i + ": ");
            String breed = scanner.nextLine();

            System.out.print("Enter age for Dog " + i + ": ");
            int age = scanner.nextInt();
            scanner.nextLine(); // Consume the newline character

            Dog currentDog = new Dog(age, breed);

            // Update statistics
            totalAge += age;

            if (oldestDog == null || currentDog.compareTo(oldestDog) > 0) {
                oldestDog = currentDog;
            }
        }

        // Calculate average age
        double averageAge = totalAge / numDogs;

        // Print statistics
        System.out.println("\nAverage age: " + averageAge);
        System.out.println("Oldest Dog -> " + oldestDog);
    }
}

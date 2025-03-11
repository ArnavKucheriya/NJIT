import java.util.*;

public class TestBook {
    public static void main(String[] args) {
        // Create two instances of the Book class
        Book book1 = new Book();
        Book book2 = new Book();

        // Modify titles and pages based on user input
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter title for book 1: ");
        book1.setTitle(scanner.nextLine());

        System.out.print("Enter number of pages for book 1: ");
        book1.setPages(scanner.nextInt());
        scanner.nextLine(); // Consume the newline character

        System.out.print("Enter title for book 2: ");
        book2.setTitle(scanner.nextLine());

        System.out.print("Enter number of pages for book 2: ");
        book2.setPages(scanner.nextInt());

        // Display information about each object using toString method
        System.out.println("\nInformation about Book 1: " + book1.toString());
        System.out.println("Information about Book 2: " + book2.toString());

        // Calculate and display the average number of pages
        double averagePages = (book1.getPages() + book2.getPages()) / 2.0;
        System.out.println("\nAverage number of pages: " + averagePages);
    }
}

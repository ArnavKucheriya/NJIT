package Labs.Lecture_12;
import java.util.*;
public class ShoppingCart_Checkout {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
/*
Write a program that simulates shopping. The program should have a loop that continues as long as the user wants to
shop. Each time through the loop read in the name, price, and quantity of the item the user wants to add to the cart. After
adding an item to the cart, the cart contents should be printed. After the loop print a “Please pay ...” message with the
total price of the items in the cart
*/
        ShoppingCart cart = new ShoppingCart();
        String itemName;
        double price;
        int quantity;
        char response;
        do {
            System.out.print("Enter the name of the item: ");
            itemName = input.next();
            System.out.print("Enter the price of the item: ");
            price = input.nextDouble();
            System.out.print("Enter the quantity of the item: ");
            quantity = input.nextInt();
            cart.addToCart(itemName, price, quantity);
            System.out.println(cart);
            System.out.print("Do you want to continue shopping? (Y/N): ");
            response = input.next().charAt(0);
        } while (response == 'Y' || response == 'y');
        System.out.println("Please pay: " + cart);
    }
}
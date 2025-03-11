import java.util.*;

public class HW01_ArnavKucheriya {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        double fahrenheit = 36.5;
        double celsius = ((fahrenheit - 32) * ((double) 5 / 9));
        System.out.println("The Temperature in Fahrenheit: " + fahrenheit + ", Temperature in Celsius: " + celsius);

        System.out.print("Enter the Number of Seconds: ");
        int sec = in.nextInt();

        /*
        sec / 60 = min
        min % 60 = (int) min
        min / 60 = hour
        Why is modulo operator used? -> Using the modulus operator allows us to find the (overflowing) remaining time

        int min = ((sec/60)%60);
        int hour = ((sec/3600)%60);
        */

        System.out.println(((sec / 3600) % 60) + " hour, " + ((sec / 60) % 60) + " minutes, " + (sec % 60) + " seconds");
    }
}

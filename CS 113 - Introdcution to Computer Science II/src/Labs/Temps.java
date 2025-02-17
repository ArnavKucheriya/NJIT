package Labs;
// ************************************************************
// Temps.java
//
// This program reads in a sequence of hourly temperature
// readings (beginning with midnight) and prints the maximum
// temperature (along with the hour, on a 24-hour clock, it
// occurred) and the minimum temperature (along with the hour
// it occurred).
// ************************************************************
import java.util.Scanner;
public class Temps
{
    // --------------------------------------------------
// Reads in a sequence of temperatures and finds the
// maximum and minimum read in.
// --------------------------------------------------
    public static void main (String[] args)
    {
        Scanner scan = new Scanner(System.in);

        final int HOURS_PER_DAY = 24;
        int temp; // a temperature reading
        int maxTemp = -1000; // the maximum temperature
        int minTemp = 1000; // the maximum and minimum temperatures
        int timeStampMax = 0, timeStampMin = 0; // the hour at which the max or min temperature occurred

        // print program heading
        System.out.println ();
        System.out.println ("Temperature Readings for 24 Hour Period");
        System.out.println ();
        for (int hour = 0; hour < HOURS_PER_DAY; hour++)
        {
            System.out.print ("Enter the temperature reading at " + hour +
                    " hours: ");
            temp = scan.nextInt();

            if (temp > maxTemp) {
                maxTemp = temp;
                timeStampMax = hour;
            }
            if (temp < minTemp) {
                minTemp = temp;
                timeStampMin = hour;
            }
        }
        System.out.println("The maximum temperature is: " + maxTemp + " at " + timeStampMax + " hours");
        System.out.println("The minimum temperature is: " + minTemp + " at " + timeStampMin + " hours");
    }
}

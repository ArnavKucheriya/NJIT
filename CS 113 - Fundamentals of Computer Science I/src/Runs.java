// ******************************************************************
// Runs.java
//
// Finds the length of the longest run of heads in 100 flips of a coin.
// *******************************************************************
public class Runs
{
    public static void main (String[] args)
    {
        final int FLIPS = 100; // number of coin flips
        int currentRun =0; // length of the current run of HEADS
        int maxRun =0; // length of the maximum run so far

        // Create a coin object
        Coin coin = new Coin();

        int headStreak =0;
        // Flip the coin FLIPS times
        for (int i = 0; i < FLIPS; i++)
        {
            if (coin.isHeads())
            {
                System.out.print("H");
                headStreak++;
                if (headStreak > maxRun)
                {
                    maxRun = headStreak;
                }
            }
            else
            {
                System.out.print("T");
                headStreak = 0;
            }

            coin.flip();
        // Flip the coin & print the result
        // Update the run information
        }
        // Print the results
        System.out.println();
        System.out.println("The longest run of heads is " + maxRun);
    }
}
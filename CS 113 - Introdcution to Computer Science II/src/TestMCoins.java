public class TestMCoins {
    public static void main(String[] args) {
        // Creating a 2x5 array of MonetaryCoin objects
        MonetaryCoin[][] coins = new MonetaryCoin[2][5];

        // Filling in the array with random monetary values
        for (int i = 0; i < coins.length; i++) {
            for (int j = 0; j < coins[i].length; j++) {
                int randomValue = (int) (Math.random() * 100) + 1; // Random value between 1 and 100 cents
                coins[i][j] = new MonetaryCoin(randomValue);
            }
        }

        // Flipping all coins and calculating total monetary value of coins with HEADS face
        for (int i = 0; i < coins.length; i++) {
            int totalHeadsValue = 0;
            for (int j = 0; j < coins[i].length; j++) {
                coins[i][j].flip(); // Flip the coin
                if (coins[i][j].isHeads()) { // If the face is HEADS
                    totalHeadsValue += coins[i][j].getValueInCents(); // Add the value to the total
                }
            }
            System.out.println("Total value of coins with HEADS in row " + (i + 1) + ": " + totalHeadsValue);
        }
    }
}

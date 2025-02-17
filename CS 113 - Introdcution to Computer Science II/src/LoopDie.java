public class LoopDie {
    public static void main(String[] args) {
        Die die1 = new Die();
        Die die2 = new Die();

/*
        System.out.println("Die1: " + die1 + "\nDie2: " + die2);
        System.out.println("Comparing facevalues of dies: "+ die1.equals(die2));

        if (die1.compareTo(die2) == 0) {
            System.out.println("Die1 and Die2 have the same face value");
        } else if (die1.compareTo(die2) == -1) {
            System.out.println("Die1 has a smaller face value than Die2");
        } else {
            System.out.println("Die1 has a larger face value than Die2");
        }
*/

        // Write a code to roll both dies 10 times. The program should calculate how many times the dies were equal.

        int equalCount = 0;

/*
        for (int i = 0; i < 10; i++) {
            die1.roll();
            die2.roll();
            System.out.println(die1 + " " + die2);
            if (die1.equals(die2)) {
                equalCount++;
            }
        }
        System.out.println("The dies were equal " + equalCount + " times.");
*/
        // Using a while loop
        int i = 0;
        while (i < 10) {
            die1.roll();
            die2.roll();
            System.out.println(die1 + " " + die2);
            if (die1.equals(die2)) {
                equalCount++;
            }
            i++;
        }
        System.out.println("The dies were equal " + equalCount + " times.");
    }
}

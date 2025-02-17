public class RollDie {
    public static void main(String[] args) {
        // Create 2 die objects
        Die die1, die2, die3;
        int sum;

        die1 = new Die();
        die2 = new Die();

        die1.roll();
        die2.roll();

        System.out.println("Die1: "+die1+" Die2: "+die2);

        sum = die1.getFaceValue()+die2.getFaceValue();
        System.out.println("Sum of both Dies: "+sum );

        die3 = die1;
        die1 = die2;
        die2 = die3;

        System.out.println("Swapped Die values- \nDie1: "+die1+"\nDie2: "+die2);

    }

}

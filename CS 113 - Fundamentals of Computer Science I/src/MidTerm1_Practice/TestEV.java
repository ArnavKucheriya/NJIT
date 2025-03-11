package MidTerm1_Practice;
import java.sql.SQLOutput;
import java.util.Random;
import java.util.Scanner;
public class TestEV {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        Random random = new Random();

        EV car1 = new EV("Tesla Model S", random.nextInt(250, 301));

        System.out.println("Enter the model and range of the second car: ");
        EV car2 = new EV(input.nextLine(), input.nextInt());

        if (car1.compareTo(car2) == 1) {
            System.out.println("Longst Range: " + car1);
        }
        else if(car1.compareTo(car2) == -1){
            System.out.println("Longst Range: " + car2);
        }
        else{
            System.out.println("Both cars have the same range");
        }

        if (car1.sameModel(car2)) {
            System.out.println("Both cars are the same model");
        }
        else{
            System.out.println("Both cars are different models");
        }

    }
}

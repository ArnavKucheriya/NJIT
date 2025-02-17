package Labs.Lecture_02;
import java.util.*;
public class AverageGrade {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter 3 different grades: ");
        double g1 = input.nextDouble();
        double g2 = input.nextDouble();
        double g3 = input.nextDouble();

        double gradeAverage = ((g1+g2+g3)/3);
        System.out.println("Average of the grades are: "+gradeAverage);
    }
}

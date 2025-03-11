package MidTerm1_Practice;

import java.util.Random;

public class ProjectApp {
    public static void main(String[] args) {
        Project obj = new Project("Research Project", 10);
        System.out.println(obj);

        Project obj2 = new Project("Big Data", 0);

        Random random = new Random();
        int i = 0;
        int pageAdded;

        do {
            i++;
            pageAdded = random.nextInt(0, 4);
            obj2.addPages(pageAdded);
            System.out.println("Day " + i + ": Pages added: " + pageAdded);
        } while (obj2.getPages() <= 10);

        System.out.println(obj2);
        System.out.println("Number of Days to Complete: " + i);

    }
}

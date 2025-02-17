import java.util.*;

public class ClientBandBooster {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the Name of booster1: ");
        String name1 = input.next();
        System.out.print("Enter the Name of booster2: ");
        String name2 = input.next();

        BandBooster booster1 = new BandBooster(name1);
        BandBooster booster2 = new BandBooster(name2);

        System.out.print("Enter sales for week 1 by " + name1 + ": ");
        int saleWeek1 = input.nextInt();
        booster1.updateSales(saleWeek1);

        System.out.print("Enter sales for week 1 by " + name2 + ": ");
        int saleb2_Week1 = input.nextInt();
        booster2.updateSales(saleb2_Week1);

        System.out.print("Enter sales for week 2 by " + name1 + ": ");
        int saleWeek2 = input.nextInt();
        booster1.updateSales(saleWeek2);

        System.out.print("Enter sales for week 2 by " + name2 + ": ");
        int saleb2_Week2 = input.nextInt();
        booster2.updateSales(saleb2_Week2);

        System.out.println(booster1);
        System.out.println(booster2);
    }
}



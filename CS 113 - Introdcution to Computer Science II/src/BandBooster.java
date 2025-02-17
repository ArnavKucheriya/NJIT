public class BandBooster {
    private String name;
    private int boxesSold;

    public BandBooster(String nameBooster) {
        name = nameBooster;
        boxesSold = 0;
    }

    public String getName() {
        return name;
    }

    public void updateSales(int sales) {
        boxesSold = boxesSold + sales;
    }

    public String toString() {
        return name + ": " + boxesSold + " boxes";
    }

}

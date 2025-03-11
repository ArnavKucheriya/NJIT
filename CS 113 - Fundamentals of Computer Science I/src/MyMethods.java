public class MyMethods {
    public MyMethods() {

    }
    public int Volume(int width, int length, int height) {
        return width * length * height;
    }
    public int avgFaceValue(Die die1, Die die2) {
        die1 = new Die();
        die2 = new Die();

        int oddCount = 0;
        while (!die1.equals(die2)) {
            System.out.println(die1 + " " + die2);
            if(die1.getFaceValue() % 2 != 0 && die2.getFaceValue() % 2 != 0) {
                oddCount++;
            }
            die1.roll();
            die2.roll();
        }
        return oddCount;
    }
}

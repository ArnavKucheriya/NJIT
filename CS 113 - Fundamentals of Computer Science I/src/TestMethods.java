public class TestMethods {
    public static void main(String[] args) {
        MyMethods newMethod = new MyMethods();

        System.out.println("Height: 16, Length: 2, Width: 9");
        System.out.println("Volume: " + newMethod.Volume(9, 2, 16));

        System.out.println();

        MyMethods newMethod2 = new MyMethods();
        System.out.println("Number of times facevalue is odd: "+newMethod2.avgFaceValue(new Die(), new Die()));
    }
}

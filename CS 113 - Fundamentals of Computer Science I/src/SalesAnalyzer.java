public class SalesAnalyzer {
    public static int[] salesRange(int[][] sales) {
        int lowest = Integer.MAX_VALUE;
        int highest = Integer.MIN_VALUE;

        for (int[] week : sales) {
            for (int sale : week) {
                lowest = Math.min(lowest, sale);
                highest = Math.max(highest, sale);
            }
        }

        int range = highest - lowest;

        return new int[]{lowest, highest, range};
    }
}

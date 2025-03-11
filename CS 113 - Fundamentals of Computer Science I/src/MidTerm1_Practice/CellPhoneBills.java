package MidTerm1_Practice;

public class CellPhoneBills {
    public static double[] bestInMonths(double[][] famCellBills) {
        int numMonths = famCellBills[0].length; // Number of months
        double[] bestBills = new double[numMonths]; // Array to store the best bill for each month

        // Iterate over each month
        for (int month = 0; month < numMonths; month++) {
            // Initialize the minimum bill for the month with the first family member's bill
            double minBill = famCellBills[0][month];

            // Iterate over each family member's bill for the current month
            for (int member = 1; member < famCellBills.length; member++) {
                // Update the minimum bill if a lower bill is found for the current month
                if (famCellBills[member][month] < minBill) {
                    minBill = famCellBills[member][month];
                }
            }

            // Store the minimum bill for the current month in the result array
            bestBills[month] = minBill;
        }

        return bestBills;
    }

    public static void main(String[] args) {
        // Sample data representing the cell phone bills of family members over three months
        double[][] famCellBills = {
                {34.56, 75.34, 23.87},
                {87.79, 32.05, 23.54},
                {89.78, 66.76, 87.99},
                {45.34, 56.45, 16.54}
        };

        // Get the best bill for each month
        double[] bestBills = bestInMonths(famCellBills);

        // Print the best bills for each month
        System.out.println("Best Bills:");
        for (int month = 0; month < bestBills.length; month++) {
            System.out.println("Month " + (month + 1) + ": " + bestBills[month]);
        }
    }
}


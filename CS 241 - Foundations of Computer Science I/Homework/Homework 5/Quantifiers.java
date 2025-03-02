public class Quantifiers {
    // Domain of discourse
    int[] A = new int[] {-2, -1, 0}; // First coordinate
    int[] B = new int[] {0, 1, 2}; // Second coordinate
    /** This predicate returns TRUE iff (x + y = 0) */
    boolean P(int x,int y) {
    return (x + y == 0);
    }
    /****************************************************************************
    * Compute statements:
    * Ax.Ay.P(x,y)
    * Ex.Ey.P(x,y)
    * Ax.Ey.P(x,y)
    * Ex.Ay.P(x,y)
    * with respect to domain of discourse A x B
    /****************************************************************************
    /**************************************************************************/
    /** This function computes the value of Ax.Ay.P(x,y) in the domain A x B */
    /**************************************************************************/
    boolean forAllPairs() {
    //TO DO
    return true;
    }
    /**************************************************************************/
    /** This function computes the value of Ex.Ey.P(x,y) in the domain A x B */
    /**************************************************************************/
    boolean existsPair() {
    // TO DO
    return true;
    }
    /**************************************************************************/
    /** This function computes the value of Ax.Ey.P(x,y) in the domain A x B */
    /**************************************************************************/
    boolean forAllExists() {
    //TO DO
    return true;
    }
    /**************************************************************************/
    /** This function computes the value of Ex.Ay.P(x,y) in the domain A x B */
    /**************************************************************************/
    boolean existsForAll() {
    for (int x : A) {
    if (forallY(x)) {
    return true;
    }
    }
    return false;
    }
    /************************************************************************
    ********Helper functions for Ax.Ey.P(x,y) and Ex.Ay.P(x,y)*************
    ************************************************************************/
    /**********************************************************************************
    */
    /** Helper function for existsForAll, check if a given x is true for all y's
    in Y */
    /**********************************************************************************
    */
    private boolean forallY(int currx) {
    for (int y : B) {
    if (!P(currx,y)) {
    return false;
    }
    }
    return true;
    }
    /*************************************************************
    *
    * Test Cases
    */
    public static void main(String[] args) {
    Quantifiers Q = new Quantifiers();
    System.out.println("'Ax.Ay.P(x,y)' is " + Q.forAllPairs());
    System.out.println("'Ex.Ey.P(x,y)' is " + Q.existsPair());
    System.out.println("'Ax.Ey.P(x,y)' is " + Q.forAllExists());
    System.out.println("'Ex.Ay.P(x,y)' is " + Q.existsForAll());
    }
    }
    
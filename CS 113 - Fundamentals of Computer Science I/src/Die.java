public class Die {

    //data declaration
    private int faceValue;

    //default constructor ( no parameters)
    public Die() {
        roll();
    }

    //method roll
    public Die(int newFaceValue) {
        faceValue = newFaceValue;
    }

    public int roll() {
        faceValue = (int) (Math.random() * 6) + 1;
        return faceValue;
    }

    //getter method
    public int getFaceValue() {
        return faceValue;
    }

    //equals method
    public boolean equals(Die otherDie) {
        //return true if the faceValue of this die is equal to the faceValue of the otherDie
        return faceValue == otherDie.faceValue;
    }

    //compareTo method
    public int compareTo(Die otherDie) {
        //return 0 if the faceValue of this die is equal to the faceValue of the otherDie
        if (faceValue == otherDie.faceValue) {
            return 0;
        }
        //return -1 if the faceValue of this die is less than the faceValue of the otherDie
        else if (faceValue < otherDie.faceValue) {
            return -1;
        }
        //return 1 if the faceValue of this die is greater than the faceValue of the otherDie
        else {
            return 1;
        }
    }

    //setter method
    public void setFaceValue(int num1) {
        faceValue = num1;
    }

    //toString method
    public String toString() {
        return " " + faceValue;
    }
}
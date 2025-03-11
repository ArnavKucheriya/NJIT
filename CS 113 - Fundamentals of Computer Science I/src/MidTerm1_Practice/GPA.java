package MidTerm1_Practice;

public class GPA
{
    private double value;
    public GPA(double value)
    { this.value =value;}
    public double getValue()
    { return value;}
    public int compareTo(GPA other){
        if (this.value <other.value)
            return -1;
        else if (this.value==other.value)
            return 0;
        else
            return 1;
    }
    public String toString()
    { return Double.toString(value);}
}

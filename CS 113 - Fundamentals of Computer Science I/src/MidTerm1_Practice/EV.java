package MidTerm1_Practice;

public class EV{
    private int range;
    private String model;

    public EV(String model, int range){
        this.range = range;
        this.model = model;
    }
    public int getRange(){
        return this.range;
    }
    public String getModel(){
        return this.model;
    }
    public void setRange(int range){
        this.range = range;
    }
    public String toString(){
        return "Model: "+model+", Range: "+range;
    }
    public int compareTo(EV otherEV){
        if (range == otherEV.range){
            return 0;
        }
        else if (range < otherEV.range) {
            return -1;
        }
        else {
            return 1;
        }
    }
    public boolean sameModel(EV otherEV){
        return model.equals(otherEV.model);
    }
}
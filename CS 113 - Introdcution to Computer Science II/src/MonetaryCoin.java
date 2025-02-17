public class MonetaryCoin extends Coin {
    private int valueInCents;

    public MonetaryCoin(int valueInCents) {
        super(); // Calls the constructor of the base class (Coin)
        setValueInCents(valueInCents);
    }

    public int getValueInCents() {
        return valueInCents;
    }

    public void setValueInCents(int valueInCents) {
        this.valueInCents = valueInCents;
    }

    @Override
    public String toString() {
        return super.toString() + " worth " + valueInCents + " cents";
    }
}

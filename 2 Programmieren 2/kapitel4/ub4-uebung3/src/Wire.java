public class Wire implements Mobile {
    protected final Mobile mobile1;
    protected final Mobile mobile2;
    protected final double length;
    protected double knotPosition;

    public Wire(Mobile mobile1, Mobile mobile2, double length) {
        this.mobile1 = mobile1;
        this.mobile2 = mobile2;
        this.length = length;
    }

    public Mobile getMobile1() {
        return mobile1;
    }

    public Mobile getMobile2() {
        return mobile2;
    }

    public double getLength() {
        return length;
    }

    public double getKnotPosition() {
        return knotPosition;
    }

    @Override
    public double weight() {
        return mobile1.weight() + mobile2.weight();
    }

    @Override
    public void balance() {
        mobile1.balance();
        mobile2.balance();
        knotPosition = mobile2.weight() * length / (weight());
    }

    @Override
    public String toString() {
        return "Mobile[%.1f:%s, %.1f:%s]".formatted(knotPosition, mobile1, length - knotPosition, mobile2);
    }
}

public class Star implements Mobile {
    protected double weight;

    public Star(double weight) {
        if (weight < 0) {
            throw new IllegalArgumentException("Weight must be positive!");
        }

        this.weight = weight;
    }

    @Override
    public double weight() {
        return weight;
    }

    @Override
    public void balance() {

    }

    @Override
    public String toString() {
        return "Star[%.1f]".formatted(weight);
    }
}

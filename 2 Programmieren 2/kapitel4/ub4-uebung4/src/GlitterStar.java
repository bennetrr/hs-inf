public class GlitterStar extends Star {
    protected double decoration;

    public GlitterStar(double weight) {
        super(weight);
    }

    public GlitterStar(double weight, double decoration) {
        super(weight);
        this.decoration = decoration;
    }

    public void decorate() {
        decoration += 1;
    }

    @Override
    public double weight() {
        return weight + decoration;
    }

    @Override
    public String toString() {
        return "GlitterStar[%.1f+%.1f]".formatted(weight, decoration);
    }
}

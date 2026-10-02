public class Ort<E> {
    private final int ortsId;
    private E eingelagertesElement;

    public Ort(int ortsId) {
        this.ortsId = ortsId;
    }

    public E entnehmen() {
        var temp = eingelagertesElement;
        eingelagertesElement = null;
        return temp;
    }

    public void hinzufügen(E e) {
        if (!istBelegt()) {
            eingelagertesElement = e;
        }
    }

    public E getEingelagertesElement() {
        return eingelagertesElement;
    }

    public boolean istBelegt() {
        return eingelagertesElement != null;
    }

    public int getOrtsId() {
        return ortsId;
    }

    @Override
    public String toString() {
        return "OrtId:%s %s".formatted(ortsId, eingelagertesElement);
    }
}

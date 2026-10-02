import java.util.*;

public class Pair <T1, T2> {
    private T1 first;
    private T2 second;

    public Pair(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }

    public T1 getFirst() {
        return first;
    }

    public void setFirst(T1 first) {
        this.first = first;
    }

    public T2 getSecond() {
        return second;
    }

    public void setSecond(T2 second) {
        this.second = second;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }

        if (getClass() != obj.getClass()) {
            return false;
        }

        if (super.equals(obj)) {
            return true;
        }

        var other = (Pair) obj;

        // First
        if (first == null && other.first != null) {
            return false;
        }

        if (first != null && other.first == null) {
            return false;
        }

        if (first == null || !first.equals(other.first)) {
            return false;
        }

        // Second
        if (second == null && other.second != null) {
            return false;
        }

        if (second != null && other.second == null) {
            return false;
        }

        if (second == null || !second.equals(other.second)) {
            return false;
        }

        return true;
    }

    @Override
    public int hashCode() {
        int hash = 42;

        hash = hash * 7 + first.hashCode();
        hash = hash * 13 + second.hashCode();

        return hash;
    }

    @Override
    public String toString() {
        return "(%s, %s)".formatted(first, second);
    }

    public static class FirstComparator <T extends Comparable <? super T> , U> implements Comparator<Pair<T, U>> {
        public int compare(final Pair<T, U> p0, final Pair<T, U> p1) {
            return p0.first.compareTo(p1.first);
        }
    }

    public static class SecondComparator <T, U extends Comparable <? super U>> implements Comparator<Pair<T, U>> {
        public int compare(final Pair<T, U> p0, final Pair<T, U> p1) {
            return p0.second.compareTo(p1.second);
        }
    }
}

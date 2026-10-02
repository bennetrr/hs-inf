import java.util.*;

public class CountList<E> extends ArrayList<E> {
    private final Map<E, Integer> counts;
    private final Set<E> uniques;

    public CountList(int initialCapacity) {
        super(initialCapacity);
        counts = new HashMap<>();
        uniques = new HashSet<>();
    }

    public CountList() {
        super();
        counts = new HashMap<>();
        uniques = new HashSet<>();
    }

    public CountList(Collection<? extends E> c) {
        super(c);
        counts = new HashMap<>();
        uniques = new HashSet<>();
    }

    private void register(E e) {
        counts.merge(e, 1, Integer::sum);
        uniques.add(e);
    }

    @Override
    public boolean add(E e) {
        register(e);
        return super.add(e);
    }

    public int count(E e) {
        return counts.getOrDefault(e, 0);
    }

    public int unique() {
        return uniques.size();
    }

    public Map<E, Integer> counts() {
        return counts;
    }
}

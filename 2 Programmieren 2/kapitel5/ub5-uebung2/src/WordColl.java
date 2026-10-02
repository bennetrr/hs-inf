import java.util.NoSuchElementException;
import java.util.Vector;

public class WordColl {
    private final Vector<Word> words;

    public WordColl(String[] sentences) {
        words = new Vector<>();
        append(sentences);
    }

    public static void main(String[] args) {
        String[] sentences = {"Thomas Mann , der jüngere", "Bruder von Heinrich Mann"};
        WordColl wColl = new WordColl(sentences);
        System.out.println(wColl.size());
    }

    public void append(String[] sentences) {
        for (String sentence : sentences) {
            for (String word : sentence.split(" ")) {
                Word wordObject;

                try {
                    wordObject = find(word);
                } catch (NoSuchElementException e) {
                    words.add(new Word(word));
                    continue;
                }

                wordObject.add();
            }
        }
    }

    /**
     * Return the number of words.
     */
    public int size() {
        return words.stream().mapToInt(w -> w.count).reduce(0, Integer::sum);
    }

    /**
     * Return the occurrence count of the given word.
     */
    public int count(String word) {
        return find(word).count;
    }

    private Word find(String word) {
        return words.stream().filter(w -> w.word.equalsIgnoreCase(word)).findFirst().orElseThrow();
    }

    /**
     * Return the word with the most occurrences.
     */
    public String top() {
        return words.stream().sorted().findFirst().orElseThrow().word;
    }

    public String toString() {
        var str = new StringBuilder();

        str.append("%-21s| count\n".formatted("Word"));
        str.append("-".repeat(41)).append("\n");
        words.forEach(str::append);
        str.append("-".repeat(41)).append("\n");
        str.append("Total: %s\n".formatted(size()));
        return str.toString();
    }

    class Word implements Comparable<Word> {
        private final String word;
        private int count;

        public Word(String word) {
            this.word = word;
            this.count = 1;
        }

        /**
         * Return the current word.
         */
        public String word() {
            return word;
        }

        /**
         * Return the occurrence count of the current word.
         */
        public int count() {
            return count;
        }

        /**
         * Add a number of occurrences to the counter.
         */
        public void add(int count) {
            this.count += count;
        }

        public void add() {
            this.count += 1;
        }

        @Override
        public int compareTo(Word o) {
            return Integer.compare(o.count, count);
        }

        @Override
        public String toString() {
            return "%-21s|  %s\n".formatted(word, count);
        }
    }
}

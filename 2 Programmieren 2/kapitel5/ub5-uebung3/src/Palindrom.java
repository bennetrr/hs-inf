import java.util.Stack;

public class Palindrom {
    public static boolean isPalindrom(String phrase) {
        // Add all chars excluding whitespaces to the stack
        var chars = new Stack<Character>();

        for (var character : phrase.toLowerCase().toCharArray()) {
            if (character == ' ') {
                continue;
            }

            chars.add(character);
        }

        // Reverse the stack
        var reversedChars = new Stack<Character>();

        for (int i = chars.size() - 1; i >= 0; i--) {
            reversedChars.add(chars.get(i));
        }


        for (int i = 0; i < chars.size(); i++) {
            var front = chars.pop();
            var back = reversedChars.pop();

            if (front != back) {
                return false;
            }
        }

        return true;
    }
}

package de.hsco.ads.uebung07;

import javax.naming.OperationNotSupportedException;
import java.io.IOException;
import java.io.StreamTokenizer;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class ExpressionParser {
    /**
     * Takes a postfix expression as String, evaluates it and returns the result
     *
     * @param expr a mathematical expression in postfix notation
     * @return the value of the given expression
     */
    public static double evaluatePostfixExpression(String expr) throws IOException, OperationNotSupportedException {
        var stack = new Stack<String>();
        stack.addAll(tokenizeExpression(expr).reversed());

        while (stack.size() > 1) {
            var num1 = Double.parseDouble(stack.pop());
            var num2 = Double.parseDouble(stack.pop());
            var opr = stack.pop();

            switch (opr) {
                case "+" -> stack.push(Double.toString(num1 + num2));
                case "-" -> stack.push(Double.toString(num1 - num2));
                case "*" -> stack.push(Double.toString(num1 * num2));
                case "/" -> stack.push(Double.toString(num1 / num2));
                default -> throw new OperationNotSupportedException(opr);
            }
        }

        return Double.parseDouble(stack.pop());
    }

    public static String convertInfixToPostfix(List<String> exprTokens) {
        var stack = new Stack<String>();
        var postfix = new StringBuilder();

        for (String token : exprTokens) {
            if (isDouble(token)) {  // 2. Ist Operant
                stack.push(token);
            } else if (token.equals("(")) {  // 3. Ist öffnende Klammer
                stack.push(token);
            } else if (token.equals(")")) {  // 4. Ist schließende Klammer
                while (stack.peek().equals("(")) {
                    postfix.append(stack.pop()).append(" ");
                }
                postfix.append(") ");
            } else if (token.equals("+") || token.equals("-") || token.equals("*") || token.equals("/")) {  // 5. Ist Operator
                if (((stack.peek().equals("*") || stack.peek().equals("/")) && (token.equals("+") || token.equals("-"))) // 5a. Priorität auf dem Stack höher
                        || stack.isEmpty() // 5a. Stack leer
                        || stack.peek().equals("(")) {  // 5a. Öffnende Klammer auf Stack
                    stack.push(token);
                } else {
                    while (!stack.isEmpty() &&
                            !((stack.peek().equals("+") || stack.peek().equals("-")) && (token.equals("*") || token.equals("/")))) {  // 5b. Priotät auf dem Stack nicht niedriger
                        postfix.append(stack.pop()).append(" ");
                    }
                    stack.push(token);
                }
            }
        }

        while (!stack.isEmpty()) {
            postfix.append(stack.pop()).append(" ");
        }

        return postfix.toString();
    }

    public static String convertInfixToPostfix(String expr) throws IOException {
        return String.join(" ", convertInfixToPostfix(tokenizeExpression(expr)));
    }

    /**
     * Tokenize expression as String into List of Strings.
     * Source:
     * https://stackoverflow.com/a/16502151/391338
     * https://creativecommons.org/licenses/by-sa/3.0/
     */
    public static List<String> tokenizeExpression(String expression) throws IOException {
        StreamTokenizer tokenizer = new StreamTokenizer(new StringReader(expression));
        tokenizer.ordinaryChar('-');  // Don't parse minus as part of numbers.
        tokenizer.ordinaryChar('/');  // Don't treat slash as a comment start.
        List<String> tokBuf = new ArrayList<>();
        while (tokenizer.nextToken() != StreamTokenizer.TT_EOF) {
            switch(tokenizer.ttype) {
                case StreamTokenizer.TT_NUMBER:
                    tokBuf.add(String.valueOf(tokenizer.nval));
                    break;
                case StreamTokenizer.TT_WORD:
                    tokBuf.add(tokenizer.sval);
                    break;
                default:  // operator
                    tokBuf.add(String.valueOf((char) tokenizer.ttype));
            }
        }
        return tokBuf;
    }

    public static boolean isDouble(String str) {
        try {
            Double.parseDouble(str);
        } catch (NumberFormatException e) {
            return false;
        }

        return true;
    }
}

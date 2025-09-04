package linearStructures;

import java.util.Stack;
import java.util.Queue;
import java.util.LinkedList;

public class Hw6 {

    /**
     * Checks if the given expression has balanced parentheses.
     * Only includes the characters {, }, [, ], (, ).
     * Ignores spaces and other characters.
     * 
     * @param expression the string to check for balanced parentheses
     * @return true if balanced, false otherwise
     */
    public static boolean isbalanced(String expression) {
        Stack<Character> stack = new Stack<>();
        for (char ch : expression.toCharArray()) {
            if (ch == '(' || ch == '{' || ch == '[') {
                stack.push(ch);
            } else if (ch == ')' || ch == '}' || ch == ']') {
                if (stack.isEmpty()) return false;
                char top = stack.pop();
                if ((ch == ')' && top != '(') || 
                    (ch == '}' && top != '{') || 
                    (ch == ']' && top != '[')) return false;
            }
        }
        return stack.isEmpty();
    }

    /**
     * Converts a decimal number to its binary representation using a stack.
     * 
     * @param decimal the decimal number as a string
     * @return the binary representation as a string
     */
    public static String inBinary(String decimal) {
        int num = Integer.parseInt(decimal);
        Stack<Integer> stack = new Stack<>();
        while (num > 0) {
            stack.push(num % 2);
            num /= 2;
        }
        StringBuilder binary = new StringBuilder();
        while (!stack.isEmpty()) {
            binary.append(stack.pop());
        }
        return binary.toString();
    }

    /**
     * Returns a queue of differences between consecutive elements of the input queue.
     * The original queue remains unmodified.
     * 
     * @param q the queue of integers
     * @return a new queue with differences between consecutive elements
     */
    public static Queue<Integer> differenceQueue(Queue<Integer> q) {
        Queue<Integer> result = new LinkedList<>();
        if (q.isEmpty()) return result;

        int prev = q.peek();
        for (int current : q) {
            result.add(current - prev);
            prev = current;
        }
        return result;
    }

    /**
     * Merges two sorted queues into a new sorted queue.
     * Both input queues remain unmodified.
     * 
     * @param q1 the first sorted queue
     * @param q2 the second sorted queue
     * @return a new queue containing all elements of q1 and q2 in sorted order
     */
    public static Queue<Integer> mergeQueues(Queue<Integer> q1, Queue<Integer> q2) {
        Queue<Integer> result = new LinkedList<>();
        Queue<Integer> temp1 = new LinkedList<>(q1);
        Queue<Integer> temp2 = new LinkedList<>(q2);

        while (!temp1.isEmpty() && !temp2.isEmpty()) {
            if (temp1.peek() < temp2.peek()) {
                result.add(temp1.poll());
            } else {
                result.add(temp2.poll());
            }
        }
        result.addAll(temp1);
        result.addAll(temp2);

        return result;
    }
}

import java.util.*;

public class BalancedBrackets {
    public static String isBalanced(String s) {
        Stack<Character> stack = new Stack<>();
        Map<Character, Character> map = Map.of(')', '(', '}', '{', ']', '[');
        for (char c : s.toCharArray()) {
            if (map.containsValue(c)) stack.push(c);
            else if (!stack.isEmpty() && stack.peek() == map.get(c)) stack.pop();
            else return "NO";
        }
        return stack.isEmpty() ? "YES" : "NO";
    }
}

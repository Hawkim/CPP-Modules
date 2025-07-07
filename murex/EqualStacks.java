import java.util.*;

public class EqualStacks {
    public static int equalStacks(List<Integer> h1, List<Integer> h2, List<Integer> h3) {
        Stack<Integer> s1 = buildStack(h1);
        Stack<Integer> s2 = buildStack(h2);
        Stack<Integer> s3 = buildStack(h3);

        int sum1 = stackSum(s1);
        int sum2 = stackSum(s2);
        int sum3 = stackSum(s3);

        while (!(sum1 == sum2 && sum2 == sum3)) {
            if (sum1 >= sum2 && sum1 >= sum3) sum1 -= s1.pop();
            else if (sum2 >= sum1 && sum2 >= sum3) sum2 -= s2.pop();
            else sum3 -= s3.pop();
        }
        return sum1;
    }

    private static Stack<Integer> buildStack(List<Integer> heights) {
        Stack<Integer> stack = new Stack<>();
        for (int i = heights.size() - 1; i >= 0; i--) stack.push(heights.get(i));
        return stack;
    }

    private static int stackSum(Stack<Integer> s) {
        return s.stream().mapToInt(Integer::intValue).sum();
    }
}

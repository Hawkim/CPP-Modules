import java.util.*;

public class PickingNumbers {
    public static int pickingNumbers(List<Integer> a) {
        int[] freq = new int[101];
        for (int num : a) freq[num]++;
        int maxLen = 0;
        for (int i = 1; i < 100; i++) {
            maxLen = Math.max(maxLen, freq[i] + freq[i + 1]);
        }
        return maxLen;
    }
}

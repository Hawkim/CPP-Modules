import java.util.*;

public class RotateLeft {
    public static List<Integer> rotateLeft(int d, List<Integer> arr) {
        int n = arr.size();
        List<Integer> rotated = new ArrayList<>();
        for (int i = d; i < n; i++)
            rotated.add(arr.get(i));
        for (int i = 0; i < d; i++)
            rotated.add(arr.get(i));
        return rotated;
    }

    public static void main(String[] args) {
        // Original list
        List<Integer> original = Arrays.asList(1, 2, 3, 4, 5);

        // Number of left rotations
        int d = 2;

        // Perform rotation
        List<Integer> result = rotateLeft(d, original);

        // Print result
        System.out.println("Original List: " + original);
        System.out.println("Rotated Left by " + d + ": " + result);
    }
}

import java.util.Scanner;

public class StrongPassword {

    public static int minimumNumber(int n, String password) {
        int required = 0;
        if (!password.matches(".*\\d.*")) required++;                 // digit
        if (!password.matches(".*[a-z].*")) required++;               // lowercase
        if (!password.matches(".*[A-Z].*")) required++;               // uppercase
        if (!password.matches(".*[!@#$%^&*()\\-+].*")) required++;    // special char
        return Math.max(required, 6 - n);  // ensures at least 6 characters total
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read input
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        int n = password.length();

        // Calculate and print result
        int result = minimumNumber(n, password);
        System.out.println("Characters to add: " + result);

        scanner.close();
    }
}

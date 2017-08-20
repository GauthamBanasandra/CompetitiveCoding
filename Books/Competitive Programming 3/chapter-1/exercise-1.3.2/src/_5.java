import java.util.Scanner;

public class _5 {
    public static void main(String[] args) {
        int a, b, c = 1;
        Scanner keyboard = new Scanner(System.in);
        while (keyboard.hasNextLine()) {
            a = keyboard.nextInt();
            b = keyboard.nextInt();
            if (c > 1) {
                System.out.println();
            }

            System.out.printf("Case %d: %d\n", c++, a + b);
        }
    }
}

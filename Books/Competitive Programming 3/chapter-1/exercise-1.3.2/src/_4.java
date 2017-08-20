import java.util.Scanner;

public class _4 {
    public static void main(String[] args) {
        int a, b, c = 1;
        Scanner keyboard = new Scanner(System.in);
        while (keyboard.hasNextLine()) {
            a = keyboard.nextInt();
            b = keyboard.nextInt();
            System.out.printf("Case %d: %d\n\n", c++, a + b);
        }
    }
}

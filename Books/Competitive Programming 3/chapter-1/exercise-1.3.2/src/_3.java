import java.util.Scanner;

public class _3 {
    public static void main(String[] args) {
        int a, b;
        Scanner keyboard = new Scanner(System.in);
        while (keyboard.hasNextLine()) {
            a = keyboard.nextInt();
            b = keyboard.nextInt();
            System.out.println(a + b);
        }
    }
}

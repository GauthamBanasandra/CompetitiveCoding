import java.util.Scanner;

public class _2 {
    public static void main(String[] args) {
        int a, b;
        Scanner keyboard = new Scanner(System.in);
        a = keyboard.nextInt();
        b = keyboard.nextInt();
        while (a != 0 || b != 0) {
            System.out.println(a + b);
            a = keyboard.nextInt();
            b = keyboard.nextInt();
        }
    }
}

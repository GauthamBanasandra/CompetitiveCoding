import java.util.Scanner;

public class _1 {
    public static void main(String[] args) {
        int TC, a, b;
        Scanner keyboard = new Scanner(System.in);
        TC = keyboard.nextInt();
        while (TC-- > 0) {
            a = keyboard.nextInt();
            b = keyboard.nextInt();
            System.out.println(a + b);
        }
    }
}

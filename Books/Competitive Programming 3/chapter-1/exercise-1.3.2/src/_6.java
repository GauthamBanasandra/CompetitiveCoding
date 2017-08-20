import java.util.Scanner;

public class _6 {
    public static void main(String[] args) {
        int k, ans, v;
        Scanner keyboard = new Scanner(System.in);
        while (keyboard.hasNextLine()) {
            k = keyboard.nextInt();
            ans = 0;
            while (k-- > 0) {
                v = keyboard.nextInt();
                ans += v;
            }

            System.out.println(ans);
        }
    }
}

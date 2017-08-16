import java.util.Scanner;

/**
 * Created by Gautham on 16-08-2017.
 */
public class PrintNum {
    public static void main(String args[]) {
        Scanner keyboard = new Scanner(System.in);
        double number = keyboard.nextDouble();
        System.out.printf("%7.3f", number);
    }
}

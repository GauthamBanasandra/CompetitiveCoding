import java.util.Calendar;
import java.util.Scanner;

/**
 * Created by Gautham on 18-08-2017.
 */
public class DayOfWeek {
    public static void main(String args[]) {
        Scanner keyboard = new Scanner(System.in);
        int date = keyboard.nextInt();
        int month = keyboard.nextInt();
        int year = keyboard.nextInt();
        Calendar calendar = Calendar.getInstance();
        calendar.set(year, month - 1, date);
        System.out.println(calendar.get(Calendar.DAY_OF_WEEK));
    }
}

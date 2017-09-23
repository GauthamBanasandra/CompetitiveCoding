import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        StringTokenizer tokenizer = new StringTokenizer(line);
        int n = Integer.parseInt(tokenizer.nextToken());
        int dd = Integer.parseInt(tokenizer.nextToken());
        int mm = Integer.parseInt(tokenizer.nextToken());
        int yy = Integer.parseInt(tokenizer.nextToken());
        while (true) {
            if (n == 0 && dd == 0 && mm == 0 && yy == 0) {
                break;
            }

            GregorianCalendar calendar = new GregorianCalendar(yy, mm - 1, dd);
            calendar.add(Calendar.DAY_OF_MONTH, n);
            dd = calendar.get(Calendar.DAY_OF_MONTH);
            mm = calendar.get(Calendar.MONTH) + 1;
            yy = calendar.get(Calendar.YEAR);
            System.out.printf("%d %d %d\n", dd, mm, yy);

            line = reader.readLine();
            tokenizer = new StringTokenizer(line);
            n = Integer.parseInt(tokenizer.nextToken());
            dd = Integer.parseInt(tokenizer.nextToken());
            mm = Integer.parseInt(tokenizer.nextToken());
            yy = Integer.parseInt(tokenizer.nextToken());
        }
    }
}

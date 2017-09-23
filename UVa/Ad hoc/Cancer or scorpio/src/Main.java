import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.Map;

class Astrologer {
    Map<String, String> zodiac;
    private SimpleDateFormat format;
    private GregorianCalendar calendar;

    private void addZodiac(int fromDate, int toDate, int month, String zodiacSign) {
        for (int i = fromDate; i <= toDate; i++) {
            calendar.set(2000, month, i);
            format.setCalendar(calendar);
            zodiac.put(format.format(calendar.getTime()), zodiacSign);
        }
    }

    Astrologer() {
        format = new SimpleDateFormat("MM/dd");
        calendar = new GregorianCalendar();
        zodiac = new HashMap<>();

        addZodiac(21, 31, Calendar.JANUARY, "aquarius");
        addZodiac(1, 19, Calendar.FEBRUARY, "aquarius");
        addZodiac(20, 31, Calendar.FEBRUARY, "pisces");
        addZodiac(1, 20, Calendar.MARCH, "pisces");
        addZodiac(21, 31, Calendar.MARCH, "aries");
        addZodiac(1, 20, Calendar.APRIL, "aries");
        addZodiac(21, 31, Calendar.APRIL, "taurus");
        addZodiac(1, 21, Calendar.MAY, "taurus");
        addZodiac(22, 31, Calendar.MAY, "gemini");
        addZodiac(1, 21, Calendar.JUNE, "gemini");
        addZodiac(22, 31, Calendar.JUNE, "cancer");
        addZodiac(1, 22, Calendar.JULY, "cancer");
        addZodiac(23, 31, Calendar.JULY, "leo");
        addZodiac(1, 21, Calendar.AUGUST, "leo");
        addZodiac(22, 31, Calendar.AUGUST, "virgo");
        addZodiac(1, 23, Calendar.SEPTEMBER, "virgo");
        addZodiac(24, 31, Calendar.SEPTEMBER, "libra");
        addZodiac(1, 23, Calendar.OCTOBER, "libra");
        addZodiac(24, 31, Calendar.OCTOBER, "scorpio");
        addZodiac(1, 22, Calendar.NOVEMBER, "scorpio");
        addZodiac(23, 31, Calendar.NOVEMBER, "sagittarius");
        addZodiac(1, 22, Calendar.DECEMBER, "sagittarius");
        addZodiac(23, 31, Calendar.DECEMBER, "capricorn");
        addZodiac(1, 20, Calendar.JANUARY, "capricorn");
    }
}

public class Main {
    private static final int GESTATION_PERIOD = 280;

    public static void main(String[] args) throws IOException {
        Astrologer astrologer = new Astrologer();
        GregorianCalendar calendar;
        SimpleDateFormat format = new SimpleDateFormat("MM/dd/yyyy");
        SimpleDateFormat keyFormat = new SimpleDateFormat("MM/dd");

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = reader.readLine();
        int c = 1;
        int n = Integer.parseInt(line);
        while (n-- > 0) {
            line = reader.readLine();
            int mm = Integer.parseInt(String.valueOf(line.charAt(0)) + String.valueOf(line.charAt(1)));
            int dd = Integer.parseInt(String.valueOf(line.charAt(2)) + String.valueOf(line.charAt(3)));
            int yy = Integer.parseInt(line.substring(4));

            calendar = new GregorianCalendar(yy, mm - 1, dd);
            calendar.add(Calendar.DAY_OF_MONTH, GESTATION_PERIOD);
            format.setCalendar(calendar);

            String zodiac = astrologer.zodiac.get(keyFormat.format(calendar.getTime()));
            assert zodiac != null;
            System.out.printf("%d %s %s\n", c++, format.format(calendar.getTime()), zodiac);
        }
    }
}

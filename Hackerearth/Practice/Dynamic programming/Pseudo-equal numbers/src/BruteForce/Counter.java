package BruteForce;

import java.util.Hashtable;
import java.util.Map;

public class Counter {
    public Counter(int n) {
        this.n = n;
        squares = new Hashtable<>();
    }

    public long Count() {
        for (int i = 0, len = (int) Math.pow(10, n); i <= len; i++) {
            final long iSum = SumDigitSquare(i);
            squares.put(iSum, squares.getOrDefault(iSum, 0L) + 1);
        }

        long count = 0;
        for (Map.Entry<Long, Long> entry :
                squares.entrySet()) {
            count += (entry.getValue() * entry.getValue());
            count %= maxNum;
        }

        System.out.printf("Brute force non-zero : %d\n", squares.size());
        return count;
    }

    private long SumDigitSquare(int n) {
        long sum = 0;
        while (n != 0) {
            int digit = n % 10;
            digit = digit * digit;
            sum += digit;
            n /= 10;
        }
        return sum;
    }

    private Hashtable<Long, Long> squares;
    private final int n;
    private static final int maxNum = 1000000007;
}

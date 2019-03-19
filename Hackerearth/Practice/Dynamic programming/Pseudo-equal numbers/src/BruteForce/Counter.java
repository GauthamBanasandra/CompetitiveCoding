package BruteForce;

public class Counter {
    public Counter(int n) {
        this.n = n;
    }

    public long Count() {
        long count = 0;
        for (int i = 0, len = (int) Math.pow(10, n); i <= len; i++) {
            final long iSum = SumDigitSquare(i);
            for (int j = 0; j <= len; j++) {
                if (iSum == SumDigitSquare(j)) {
                    ++count;
                    count = count % maxNum;
                }
            }
        }
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

    private final int n;
    private static final int maxNum = 1000000007;
}

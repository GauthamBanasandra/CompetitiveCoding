import java.math.BigInteger;
import java.util.Scanner;

class Counter {
    Counter(int n) {
        this.n = n;
        // Number of rows : n
        // Number of columns : n * 9^2 -> the maximum sum of squares of n-1 digits
        /*
            For example,
            n = 2
            We need to consider the numbers in the range [0, 100]
            The number which results in maximum sum of squares of digits is 99
            9^2 + 9^2 = 2 * 9^2 = n * 9^2
        */
        memo = new long[this.n][this.n * 9 * 9 + 1];
    }

    long Count() {
        // Special case
        if (n == 0) {
            return 2;
        }

        // Initial state
        // Squares of the possible numbers [0, 9] in first digit
        for (int i = 0; i < 10; i++) {
            memo[0][i * i] = 1;
        }

        // We then successively loop over the possible numbers in the subsequent digits
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < memo[i].length; j++) {
                final long prevCount = memo[i - 1][j];
                if (prevCount == 0) {
                    continue;
                }

                for (int k = 0; k < 10; k++) {
                    final int index = k * k + j;
                    memo[i][index] = (memo[i][index] + prevCount) % maxNum;
                }
            }
        }

        // The last number i.e. 10^n must be handled separately
        // For a given n, the above loops only account for numbers in the range [0, (10^n)-1]
        // For example, in the case of n = 2, the above logic runs only for [0, 99]
        // The last number 10^n is fairly easy to handle as the sum of squares of its digits is 1 always
        // Thus we increment the cell under column 1 of last row by 1
        ++memo[n - 1][1];

        BigInteger count = BigInteger.ZERO;
        for (long c : memo[n - 1]) {
            if (c == 0) {
                continue;
            }

            // Using BigInteger to avoid overflow during multiplication
            BigInteger bigC = BigInteger.valueOf(c);

            // Each cell in the last row of memo contains
            // the count of numbers whose sum of squares of digits
            // add up to the corresponding column number
            /*
            For n = 3
                 0 1 2 3 4 5 ...
                 -----------
               0|1|1| | |1| |
               1|1|2|1| |2|2|
               2|1|3|2| |2|2|
                 -----------

               In the above table the cell (2, 1) indicates that there were 3 numbers
               whose sum of squares of their digits added up to 1. They are -
               001, 010, 100.
               Note : The last number 1000 also adds up to 1 and needs to be handled separately

               Once we have the counts in the last row, which are nothing but the
               frequencies of the sum of squares of the digits, for each frequency 'f',
               we can pick the two numbers (i, j -> refer problem statement) in f*f ways
            */
            count = count.add(bigC.multiply(bigC)).mod(maxNumBigInt);
        }

        return count.longValue();
    }

    private final int n;
    private long[][] memo;

    private final static int maxNum = 1000000007;
    private final static BigInteger maxNumBigInt = BigInteger.valueOf(maxNum);
}

public class TestClass {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Counter counter = new Counter(scanner.nextInt());
        System.out.println(counter.Count());
    }
}

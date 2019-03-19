// WIP

import java.math.BigInteger;
import java.util.Scanner;

class Counter {
    Counter(int n) {
        this.n = n;
        memo = new long[this.n][this.n * 9 * 9 + 1];
    }

    long Count() {
        if (n == 0) {
            return 2;
        }

        for (int i = 0; i < 10; i++) {
            memo[0][i * i] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < memo[i].length; j++) {
                if (memo[i - 1][j] == 0) {
                    continue;
                }

                for (int k = 0; k < 10; k++) {
                    ++memo[i][(k * k) + j];
                }
            }
        }

        ++memo[n - 1][1];
        BigInteger count = BigInteger.ZERO;
        for (long c : memo[n - 1]) {
            BigInteger bigC = BigInteger.valueOf(c);
            count = count.add(bigC.multiply(bigC)).mod(maxNum);
        }
        return count.longValue();
    }

    private final int n;
    private long[][] memo;

    private final static BigInteger maxNum = BigInteger.valueOf(1000000007);
}

public class TestClass {
    public static void main(String[] args) {
        /*for (int n = 0; n < 5; n++) {
            Counter counter = new Counter(n);
            BruteForce.Counter bruteForceCounter = new BruteForce.Counter(n);
            System.out.printf("DP : %d\tBrute force : %d\n", counter.Count(), bruteForceCounter.Count());
        }*/

        Scanner scanner = new Scanner(System.in);
        Counter counter = new Counter(scanner.nextInt());
        System.out.println(counter.Count());
    }
}

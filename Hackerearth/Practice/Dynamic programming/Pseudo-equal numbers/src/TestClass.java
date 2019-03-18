// WIP

import java.math.BigInteger;

class Counter {
    Counter(int n) {
        this.n = n;
        memo = new long[this.n][this.n * 9 * 9 + 1];
    }

    long Count() {
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

        BigInteger count = BigInteger.ZERO;
        for (long c : memo[n - 1]) {
            BigInteger bigC = BigInteger.valueOf(c);
            count = count.add(bigC.subtract(BigInteger.ONE).multiply(bigC).divide(BigInteger.TWO)).mod(maxNum);
        }
        return count.longValue();
    }

    private final int n;
    private long[][] memo;

    private final static BigInteger maxNum = BigInteger.valueOf(1000000007);
}

public class TestClass {
    public static void main(String[] args) {
        Counter counter = new Counter(1);
        System.out.println(counter.Count());
    }
}

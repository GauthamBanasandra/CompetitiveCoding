// WA

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.Arrays;

class CountInfo {
    int numSame;
    int numNotSame;
}

class Distribution {
    Distribution(CountInfo left, CountInfo right) {
        numLeft = left.numNotSame;
        numRight = right.numNotSame;

        int same = left.numSame + right.numSame;
        int sameHalf = same / 2;
        numLeft += sameHalf;
        numRight += same - sameHalf;
    }

    int numLeft;
    int numRight;
}

class Combination {
    Combination() {
        max = BigInteger.valueOf(1000000007);
    }

    BigInteger Compute(int n, int r) {
        assert r <= n;

        if (n == r) {
            return BigInteger.valueOf(1);
        }

        if (r > (n / 2)) {
            r = n - r;
        }

        BigInteger numerator = Factorial(n);
        BigInteger denominator = Factorial(n - r).multiply(Factorial(r));
        return numerator.divide(denominator);
    }

    private BigInteger Factorial(int n) {
        BigInteger result = BigInteger.valueOf(1);
        for (int i = 2; i <= n; ++i) {
            result = result.multiply(BigInteger.valueOf(i));
        }
        return result;
    }

    static BigInteger max;
}

class Sequence {
    Sequence(int[] numbers) {
        this.numbers = numbers;
        Arrays.sort(this.numbers);
        combination = new Combination();
    }

    int CountGoodMedians() {
        assert numbers.length != 0;

        BigInteger count = CountInOddSequences(numbers.length);
        for (int i = 0; i < numbers.length - 1; i++) {
            int number = numbers[i];
            if (number != numbers[i + 1]) {
                continue;
            }

            CountInfo leftInfo = CountLeft(i, number);
            CountInfo rightInfo = CountRight(i + 1, number);
            Distribution distribution = new Distribution(leftInfo, rightInfo);

            count = count.add(CountInEvenSequences(distribution));
        }
        return count.mod(Combination.max).intValue();
    }

    private BigInteger CountInOddSequences(int length) {
        assert length != 0;

        BigInteger result = BigInteger.valueOf(2);
        result = result.pow(length - 1);
        return result;
    }

    private BigInteger CountInEvenSequences(Distribution distribution) {
        BigInteger count = BigInteger.valueOf(1);
        for (int i = 1; i <= Math.min(distribution.numLeft, distribution.numRight); i++) {
            count = count.add(combination.Compute(distribution.numLeft, i).multiply(combination.Compute(distribution.numRight, i)));
        }
        return count;
    }

    private CountInfo CountLeft(int i, int number) {
        assert i < numbers.length;

        CountInfo info = new CountInfo();
        for (--i; i > -1; --i) {
            if (number == numbers[i]) {
                ++info.numSame;
            } else {
                ++info.numNotSame;
            }
        }
        return info;
    }

    private CountInfo CountRight(int i, int number) {
        assert i < numbers.length;

        CountInfo info = new CountInfo();
        for (++i; i < numbers.length; ++i) {
            if (number == numbers[i]) {
                ++info.numSame;
            } else {
                ++info.numNotSame;
            }
        }
        return info;
    }

    private int[] numbers;
    private Combination combination;
}

public class Main {
    public static void main(String[] args) throws IOException {
        int t, n, a;
        int numbers[] = {2, 4, 2, 1};
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        t = Integer.parseInt(reader.readLine());
        while (t-- > 0) {
            n = Integer.parseInt(reader.readLine());
            numbers = new int[n];
            String[] strNumbers = reader.readLine().split("\\s");
            assert n == strNumbers.length;

            for (int i = 0; i < n; i++) {
                numbers[i] = Integer.parseInt(strNumbers[i]);
            }

            Sequence sequence = new Sequence(numbers);
            System.out.println(sequence.CountGoodMedians());
        }
    }
}

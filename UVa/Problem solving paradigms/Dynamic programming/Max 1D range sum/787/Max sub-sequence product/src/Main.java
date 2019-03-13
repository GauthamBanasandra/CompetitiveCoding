import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.StringTokenizer;

// Based on comment https://disq.us/url?url=https%3A%2F%2Fwww.ideone.com%2FHbu0ts%3A1u7LHC8flQQI--zjm4vUlO02rew&cuid=2480709 in https://www.geeksforgeeks.org/maximum-product-subarray/

public class Main {
    private static BigInteger MaxRangeProduct(int[] numbers) {
        assert numbers.length > 0;

        BigInteger result = BigInteger.valueOf(numbers[0]);
        BigInteger max = BigInteger.valueOf(numbers[0]);
        BigInteger min = BigInteger.valueOf(numbers[0]);

        for (int i = 1; i < numbers.length; i++) {
            BigInteger current = BigInteger.valueOf(numbers[i]);
            BigInteger maxTemp = current.max(max.multiply(current).max(min.multiply(current)));
            BigInteger minTemp = current.min(max.multiply(current).min(min.multiply(current)));
            max = maxTemp;
            min = minTemp;

            result = result.max(max);
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line;

        while ((line = reader.readLine()) != null) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            ArrayList<BigInteger> numbers = new ArrayList<>(105);
            while (tokenizer.hasMoreTokens()) {
                numbers.add(new BigInteger(tokenizer.nextToken()));
            }

            assert numbers.size() > 2;
            numbers.remove(numbers.size() - 1);

            int numbersInt[] = new int[numbers.size()];
            for (int i = 0; i < numbers.size(); i++) {
                numbersInt[i] = numbers.get(i).intValue();
            }
            System.out.println(Main.MaxRangeProduct(numbersInt));
        }
    }
}

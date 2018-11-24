import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Calculator {
    private EvenDigits mEvenDigits;

    private Calculator(long maxNumber) {
        this.mEvenDigits = new EvenDigits(maxNumber);
    }

    BigInteger GetNumKeyPress(BigInteger number) {
        return mEvenDigits.GetNearest(number).subtract(number).abs();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        Calculator calculator = new Calculator(10000000000000000L);

        for (int i = 1, t = Integer.parseInt(reader.readLine()); i <= t; i++) {
            System.out.printf("Case #%d: ", i);
            System.out.println(calculator.GetNumKeyPress(new BigInteger(reader.readLine())));
        }
    }
}

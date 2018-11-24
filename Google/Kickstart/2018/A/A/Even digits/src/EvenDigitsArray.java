import java.math.BigInteger;

class EvenDigitsArray {
    private static final int base = 5;

    BigInteger Get(long i) {
        StringBuilder i5 = new StringBuilder(16);
        for (char digit : BigInteger.valueOf(i).toString(base).toCharArray()) {
            i5.append(String.valueOf((digit - '0') * 2));
        }
        return new BigInteger(i5.toString());
    }

    int CompareIndex(long i, BigInteger key) {
        return Get(i).compareTo(key);
    }
}

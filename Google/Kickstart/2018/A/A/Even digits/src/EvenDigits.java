import java.math.BigInteger;

class EvenDigits {
    private long mMax;
    private EvenDigitsArray mArr;

    EvenDigits(long mMax) {
        this.mMax = mMax;
        this.mArr = new EvenDigitsArray();
    }

    BigInteger GetNearest(BigInteger key) {
        long l = 0L, h = mMax;

        boolean found = false;
        while (h - l > 1L) {
            long d = h - l + 1;
            long m = l + ((d & 1) == 1 ? d - 1 : d) / 2;
            int c = mArr.CompareIndex(m, key);
            if (c == -1) {
                l = m;
            } else if (c == 1) {
                h = m;
            } else {
                found = true;
                break;
            }
        }

        if (found) {
            return key;
        }

        return GetNearest(mArr.Get(l), key, mArr.Get(h));
    }

    private BigInteger GetNearest(BigInteger l, BigInteger key, BigInteger h) {
        assert l.compareTo(key) < 0 && key.compareTo(h) < 0;

        BigInteger distanceLKey = key.subtract(l);
        BigInteger distanceKeyH = h.subtract(key);

        if (distanceLKey.compareTo(distanceKeyH) < 0) {
            return l;
        }
        return h;
    }
}

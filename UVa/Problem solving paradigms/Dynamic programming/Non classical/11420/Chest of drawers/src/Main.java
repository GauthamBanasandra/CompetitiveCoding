import java.util.Scanner;

class Counter {
    Counter(int n, int s) {
        this.n = n;
        this.s = s;

        this.memo = new long[this.n][2][this.n + 1];
        for (int i = 0; i < this.memo.length; i++) {
            for (int j = 0; j < this.memo[i].length; j++) {
                for (int k = 0; k < this.memo[i][j].length; k++) {
                    this.memo[i][j][k] = -1;
                }
            }
        }
    }

    long Count() {
        return Count(0, true, 0);
    }

    private long Count(int i, boolean isPrevLock, int s) {
        if (i >= this.n || s > this.n) {
            if (s == this.s) {
                return 1;
            }
            return 0;
        }

        long memo = this.memo[i][isPrevLock ? 1 : 0][s];
        if (memo != -1) {
            return memo;
        }

        final long unlocked = Count(i + 1, false, s);
        final long locked = Count(i + 1, true, s + (isPrevLock ? 1 : 0));
        return this.memo[i][isPrevLock ? 1 : 0][s] = unlocked + locked;
    }

    private final int n;
    private final int s;
    private long[][][] memo;
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int s = scanner.nextInt();

        while (n != -1 && s != -1) {
            Counter counter = new Counter(n, s);
            System.out.println(counter.Count());

            n = scanner.nextInt();
            s = scanner.nextInt();
        }
    }
}

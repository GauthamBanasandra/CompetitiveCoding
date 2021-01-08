import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class FrequencyManager {
    private final Map<Integer, Integer> frequencies;
    private final Map<Integer, Integer> reverseFrequencies;

    public FrequencyManager() {
        frequencies = new HashMap<>();
        reverseFrequencies = new HashMap<>();
    }

    public void increment(int item) {
        Integer count = frequencies.getOrDefault(item, 0);

        frequencies.put(item, count + 1);
        updateReverseFrequency(count, count + 1);
    }

    public void decrement(int item) {
        Integer count = frequencies.getOrDefault(item, 0);
        if (count == 0) {
            return;
        }
        assert count > 0;

        frequencies.put(item, count - 1);
        updateReverseFrequency(count, count - 1);
    }

    public boolean frequencyExists(int frequency) {
        return reverseFrequencies.containsKey(frequency);
    }

    private void updateReverseFrequency(int oldValue, int newValue) {
        reverseFrequencies.put(newValue, reverseFrequencies.getOrDefault(newValue, 0) + 1);
        reverseFrequencies.put(oldValue, reverseFrequencies.getOrDefault(oldValue, 0) - 1);
        int oldRevFrequency = reverseFrequencies.get(oldValue);
        if (oldRevFrequency == -1 || oldRevFrequency == 0) {
            reverseFrequencies.remove(oldValue);
        }
    }
}

public class Solution {
    public static void main(String[] args) {
        FrequencyManager frequencyManager = new FrequencyManager();
        Scanner input = new Scanner(System.in);

        final int numQueries = input.nextInt();
        for (int i = 0; i < numQueries; i++) {
            final int operation = input.nextInt();
            final int value = input.nextInt();

            if (operation == 1) {
                frequencyManager.increment(value);
            } else if (operation == 2) {
                frequencyManager.decrement(value);
            } else if (operation == 3) {
                System.out.printf("%d\n", frequencyManager.frequencyExists(value) ? 1 : 0);
            } else {
                assert false;
            }
        }
    }
}

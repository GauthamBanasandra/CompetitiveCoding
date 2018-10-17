import java.util.HashMap;
import java.util.Scanner;

/**
 * Created by gautham on 18/9/16.
 */
public class MinimumIndexDifference
{
    public static void main(String[] args)
    {
        Scanner keyboard = new Scanner(System.in);
        int size = Integer.parseInt(keyboard.next().trim());
        int[] aArray = getInputArray(size, keyboard);

        HashMap<Integer, Integer> aDict = new HashMap<>();
        for (int i = 0; i < size; i++)
            aDict.put(aArray[i], i);

        int minValue = Integer.MAX_VALUE;
        int minDiff = Integer.MAX_VALUE;
        int[] bArray = getInputArray(size, keyboard);
        for (int i = 0; i < size; i++)
        {
            int idxDiff = Math.abs(i - aDict.get(bArray[i]));
            if (idxDiff < minDiff)
            {
                minValue = bArray[i];
                minDiff = idxDiff;
            } else if (idxDiff == minDiff)
            {
                if (bArray[i] < minValue)
                {
                    minValue = bArray[i];
                    minDiff = idxDiff;
                }
            }
        }

        System.out.println(minValue);
    }

    private static int[] getInputArray(int size, Scanner keyboard)
    {
        int[] numbers = new int[size];
        for (int i = 0; i < size; i++)
            numbers[i] = Integer.parseInt(keyboard.next().trim());

        return numbers;
    }
}

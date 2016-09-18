import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.Scanner;

/**
 * Created by gautham on 18/9/16.
 */
public class PointFiltering implements Comparable<PointFiltering>
{
    private int k;
    private double x, y, z;

    private PointFiltering(int k, double x, double y, double z)
    {
        this.k = k;
        this.x = x;
        this.y = y;
        this.z = z;
    }


    public static void main(String[] args) throws IOException
    {
        Scanner keyboard = new Scanner(System.in);
        int kSize = Integer.parseInt(keyboard.next().trim());
        int bSize = Integer.parseInt(keyboard.next().trim());

        PriorityQueue<PointFiltering> mainList = new PriorityQueue<>(kSize);
        for (int i = 0; i < kSize; i++)
            mainList.add(getInputPoint(keyboard));

        HashMap<Integer, PointFiltering> bucket = new HashMap<>(bSize);
        for (int i = 0; i < bSize; i++)
        {
            PointFiltering point = mainList.poll();
            bucket.put(point.k, point);
        }

        DecimalFormat decimalFormat = new DecimalFormat("0.000");

        while (keyboard.hasNext())
        {
            String query = keyboard.next().trim().toLowerCase();
            int k = Integer.parseInt(keyboard.next().trim());

            if (query.equals("f"))
            {
                System.out.println(bucket.containsKey(k) ? stringifyPoint(bucket.get(k), decimalFormat) : "Point doesn't exist in the bucket.");
            } else if (query.equals("r"))
            {
                if (bucket.containsKey(k))
                {
                    if (mainList.size() > 0)
                    {
                        bucket.remove(k);
                        System.out.println("Point id " + k + " removed.");
                        PointFiltering point = mainList.poll();
                        bucket.put(point.k, point);
                    } else
                    {
                        System.out.println("No more points can be deleted.");
                    }
                } else
                {
                    System.out.println("Point doesn't exist in the bucket.");
                }
            }
        }
    }

    private static String stringifyPoint(PointFiltering point, DecimalFormat decimalFormat)
    {
        return point.k + " = (" + decimalFormat.format(point.x) + "," + decimalFormat.format(point.y) + "," + decimalFormat.format(point.z) + ")";
    }

    private static PointFiltering getInputPoint(Scanner keyboard)
    {
        int k = Integer.parseInt(keyboard.next().trim());

        double[] numbers = new double[3];
        for (int i = 0; i < 3; i++)
            numbers[i] = Double.parseDouble(keyboard.next().trim());
        return new PointFiltering(k, numbers[0], numbers[1], numbers[2]);
    }

    @Override
    public int compareTo(PointFiltering o)
    {
        if (this.z > o.z)
        {
            return -1;
        } else if (this.z == o.z)
        {
            return 0;
        }

        return 1;
    }

    @Override
    public String toString()
    {
        return this.k + "=(" + Math.round(this.x * 1000.0) / 1000.0 + "," + Math.round(this.y * 1000.0) / 1000.0 + ","
                + Math.round(this.z * 1000.0) / 1000.0 + ")";
    }
}

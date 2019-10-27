import java.io.*;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter writer = new PrintWriter(new BufferedOutputStream(System.out));

        int numStudents = Integer.parseInt(reader.readLine());
        int[] redirects = new int[numStudents];
        StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
        for (int i = 0; i < numStudents; i++) {
            redirects[i] = Integer.parseInt(tokenizer.nextToken());
        }

        String separator = "";
        for (int student :
                (new Navigator(redirects)).getCycleVertices()) {
            writer.printf("%s%d", separator, student);
            separator = " ";
        }
        writer.println();
        writer.close();
    }
}

class Navigator {
    public Navigator(int[] graph) {
        mGraph = graph;
        for (int i = 0; i < mGraph.length; i++) {
            --mGraph[i];
        }
    }

    public int[] getCycleVertices() {
        int[] cycle = new int[mGraph.length];
        for (int i = 0; i < mGraph.length; i++) {
            cycle[i] = getCycle(i) + 1;
        }
        return cycle;
    }

    private int getCycle(int startNode) {
        HashSet<Integer> ancestors = new HashSet<>(mGraph.length);
        ancestors.add(startNode);

        int node = mGraph[startNode];
        while (!ancestors.contains(node)) {
            ancestors.add(node);
            node = mGraph[node];
        }
        return node;
    }

    private int[] mGraph;
}

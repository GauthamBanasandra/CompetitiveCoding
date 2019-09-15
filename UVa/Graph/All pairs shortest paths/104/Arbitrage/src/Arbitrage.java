// WIP

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Scanner;

public class Arbitrage {
    public Arbitrage(int numNodes, BigDecimal[][] adjacencyMatrix) {
        this.numNodes = numNodes;
        this.adjacencyMatrix = adjacencyMatrix;
    }

    public ArrayList<Integer> getProfitablePath() {
        int[][] parent = new int[numNodes][numNodes];
        for (int i = 1; i < numNodes; i++) {
            for (int j = 1; j < numNodes; j++) {
                parent[i][j] = i;
            }
        }

        int[][] hops = new int[numNodes][numNodes];
        for (int i = 1; i < numNodes; i++) {
            for (int j = 1; j < numNodes; j++) {
                hops[i][j] = Integer.MAX_VALUE;
            }
        }

        for (int k = 1; k < numNodes; k++) {
            for (int i = 1; i < numNodes; i++) {
                for (int j = 1; j < numNodes; j++) {
                    BigDecimal cost = adjacencyMatrix[i][k].multiply(adjacencyMatrix[k][j]);
                    if (cost.compareTo(BigDecimal.ONE) > 0) {
                        if (hops[k][j] != Integer.MAX_VALUE &&
                                (hops[k][j] >= hops[i][j] || hops[k][j] + 1 > numNodes)) {
                            continue;
                        }
                        adjacencyMatrix[i][j] = cost;
                        parent[i][j] = parent[k][j];
                        hops[i][j] = hops[k][j] == Integer.MAX_VALUE ? 1 : hops[k][j] + 1;
                    }
                }
            }
        }
        return getProfitablePath(parent);
    }

    private ArrayList<Integer> getProfitablePath(final int[][] parent) {
        ArrayList<Integer> minLengthPath = null;
        for (int i = 1; i < numNodes; i++) {
            if (adjacencyMatrix[i][i].compareTo(BigDecimal.ONE) <= 0) {
                continue;
            }
            ArrayList<Integer> path = new ArrayList<>();
            getPath(i, parent[i][i], parent, path, 0);
            if (minLengthPath == null) {
                minLengthPath = path;
            } else if (path.size() < minLengthPath.size()) {
                minLengthPath = path;
            }
        }
        return minLengthPath;
    }

    private void getPath(int u, int v, final int[][] parent, ArrayList<Integer> path, int depth) {
        if (depth > numNodes) {
            return;
        }

        if (u != v) {
            getPath(u, parent[u][v], parent, path, depth + 1);
        }
        path.add(v);
    }

    private final int numNodes;
    private BigDecimal[][] adjacencyMatrix;

    public static void main(String[] args) {
        int numNodes = 0;
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextInt()) {
            numNodes = scanner.nextInt();
            BigDecimal[][] adjacencyMatrix = new BigDecimal[numNodes + 1][numNodes + 1];
            for (int i = 1; i <= numNodes; i++) {
                for (int j = 1; j <= numNodes; j++) {
                    adjacencyMatrix[i][j] = i == j ? BigDecimal.ONE : scanner.nextBigDecimal();
                }
            }

            ArrayList<Integer> profitableMinLenPath = new Arbitrage(numNodes + 1,
                    adjacencyMatrix).getProfitablePath();
            if (profitableMinLenPath == null) {
                System.out.println("no arbitrage sequence exists");
            } else {
                String separator = "";
                for (Integer node : profitableMinLenPath) {
                    System.out.printf("%s%d", separator, node);
                    separator = " ";
                }
                System.out.println();
            }
        }
    }
}

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;

class Edge {
    public Edge(String from, BigDecimal cost, String to) {
        this.from = from;
        this.cost = cost;
        this.to = to;
    }

    public String getFrom() {
        return from;
    }

    public String getTo() {
        return to;
    }

    public BigDecimal getCost() {
        return cost;
    }

    private String from;
    private String to;
    private BigDecimal cost;
}

class Arbitrage {
    public Arbitrage(int numNodes, String[] nodes, Edge[] edgeList) {
        this.numNodes = numNodes;
        assert this.numNodes == nodes.length;

        adjacencyMatrix = new BigDecimal[this.numNodes][this.numNodes];

        HashMap<String, Integer> nodeIdx = new HashMap<>();
        for (int i = 0; i < nodes.length; i++) {
            nodeIdx.put(nodes[i], i);
        }

        for (int i = 0; i < this.numNodes; i++) {
            for (int j = 0; j < this.numNodes; j++) {
                if (i == j) {
                    adjacencyMatrix[i][j] = BigDecimal.ONE;
                } else if (adjacencyMatrix[i][j] == null) {
                    adjacencyMatrix[i][j] = BigDecimal.ZERO;
                }
            }
        }

        for (Edge edge : edgeList) {
            int u = nodeIdx.get(edge.getFrom());
            int v = nodeIdx.get(edge.getTo());

            adjacencyMatrix[u][v] = edge.getCost();
        }
    }

    public boolean IsPossible() {
        for (int k = 0; k < numNodes; k++) {
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    // We don't want to optimize self loops
                    if (i == k || k == j) {
                        continue;
                    }

                    BigDecimal cost = adjacencyMatrix[i][k].multiply(adjacencyMatrix[k][j]);
                    if (cost.compareTo(adjacencyMatrix[i][j]) > 0) {
                        adjacencyMatrix[i][j] = cost;
                    }
                }
            }
        }

        for (int i = 0; i < numNodes; i++) {
            if (adjacencyMatrix[i][i].compareTo(BigDecimal.ONE) > 0) {
                return true;
            }
        }
        return false;
    }

    private final int numNodes;
    private BigDecimal[][] adjacencyMatrix;
}

public class Main {
    public static void main(String[] args) throws IOException {
        int numNodes, numEdges, t = 0;
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        while ((numNodes = Integer.parseInt(reader.readLine())) != 0) {
            String[] nodes = new String[numNodes];
            for (int i = 0; i < numNodes; i++) {
                nodes[i] = reader.readLine();
            }

            numEdges = Integer.parseInt(reader.readLine());
            Edge[] edges = new Edge[numEdges];
            for (int i = 0; i < numEdges; i++) {
                StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
                edges[i] = new Edge(tokenizer.nextToken(), new BigDecimal(tokenizer.nextToken()),
                        tokenizer.nextToken());
            }
            reader.readLine();

            Arbitrage arbitrage = new Arbitrage(numNodes, nodes, edges);
            System.out.printf("Case %d: %s\n", ++t, (arbitrage.IsPossible() ? "Yes" : "No"));
        }
    }
}

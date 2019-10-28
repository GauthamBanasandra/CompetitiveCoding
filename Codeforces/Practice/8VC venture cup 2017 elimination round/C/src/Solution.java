import java.io.*;
import java.util.HashSet;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter writer = new PrintWriter(new BufferedOutputStream(System.out));

        int numNodes = Integer.parseInt(reader.readLine());
        int[] edges = new int[numNodes];
        StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
        for (int i = 0; i < numNodes; i++) {
            edges[i] = Integer.parseInt(tokenizer.nextToken());
        }

        writer.println((new Graph(numNodes, edges)).getNumComponents());
        writer.close();
    }
}

class Ufds {
    public Ufds(int numNodes) {
        mNumNodes = numNodes;
        mRank = new int[mNumNodes];
        mParentIndex = new int[mNumNodes];

        for (int i = 0; i < mNumNodes; i++) {
            mParentIndex[i] = i;
        }
    }

    public int findSet(int i) {
        if (mParentIndex[i] == i) {
            return i;
        }

        mParentIndex[i] = findSet(mParentIndex[i]);
        return mParentIndex[i];
    }

    public boolean isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    public void unionSet(int i, int j) {
        if (isSameSet(i, j)) {
            return;
        }

        int iParent = findSet(i);
        int jParent = findSet(j);
        if (mRank[iParent] > mRank[jParent]) {
            mParentIndex[jParent] = iParent;
        } else {
            mParentIndex[iParent] = jParent;
            if (mRank[iParent] == mRank[jParent]) {
                ++mRank[jParent];
            }
        }
    }

    public int getNumComponents() {
        HashSet<Integer> parents = new HashSet<>(mNumNodes);
        for (int i = 0; i < mNumNodes; i++) {
            parents.add(findSet(i));
        }
        return parents.size();
    }

    private final int mNumNodes;
    private int[] mParentIndex;
    private int[] mRank;
}

class Edge {
    public Edge(int u, int v) {
        this.mU = u;
        this.mV = v;
    }

    public int getU() {
        return mU;
    }

    public int getV() {
        return mV;
    }

    private final int mU;
    private final int mV;
}

class Graph {
    public Graph(int numNodes, int[] edges) {
        mNumNodes = numNodes;

        assert numNodes == edges.length;
        mEdges = new Edge[mNumNodes];

        for (int i = 0; i < edges.length; i++) {
            mEdges[i] = new Edge(i, edges[i] - 1);
        }
    }

    public int getNumComponents() {
        Ufds ufds = new Ufds(mNumNodes);
        for (Edge edge : mEdges) {
            ufds.unionSet(edge.getU(), edge.getV());
        }
        return ufds.getNumComponents();
    }

    private final int mNumNodes;
    private final Edge[] mEdges;
}

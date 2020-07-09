// WIP

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Constants {
    public static final int UNVISITED = Integer.MAX_VALUE;
}

class DictionaryEntry {
    String word;
    Set<String> description;

    public DictionaryEntry() {
        description = new HashSet<>();
    }
}

class Node {
    int visitIndex;
    int leastVisitIndex;
    boolean isExplored;

    public Node() {
        visitIndex = Constants.UNVISITED;
    }
}

class ObjectIndex<T> {
    private final Map<T, Integer> index;
    private final Map<Integer, T> reverseIndex;
    private int id;

    public ObjectIndex() {
        id = -1;
        index = new HashMap<>();
        reverseIndex = new HashMap<>();
    }

    public int add(T word) {
        id = Math.max(id, index.getOrDefault(word, id + 1));
        index.putIfAbsent(word, id);
        reverseIndex.putIfAbsent(id, word);
        return id;
    }

    public T get(int id) {
        return reverseIndex.get(id);
    }
}

class SubDictionaryFinder {
    private final List<List<Integer>> adjacencyList;
    private final ObjectIndex<String> wordIndex;

    public SubDictionaryFinder(List<DictionaryEntry> rawAdjacencyList) {
        wordIndex = new ObjectIndex<>();
        adjacencyList = new ArrayList<>(rawAdjacencyList.size());
        for (int i = 0; i < rawAdjacencyList.size(); i++) {
            adjacencyList.add(new ArrayList<>());
        }

        for (DictionaryEntry entry : rawAdjacencyList) {
            List<Integer> adjacentNodes = adjacencyList.get(wordIndex.add(entry.word));
            for (String value : entry.description) {
                adjacentNodes.add(wordIndex.add(value));
            }
        }
    }

    public List<String> find() {
        Integer currentVisitIndex = new Integer(0);
        Stack<Integer> visitOrder = new Stack<>();
        List<List<String>> components = new ArrayList<>();
        List<Node> nodes = new ArrayList<>(adjacencyList.size());
        for (int i = 0; i < adjacencyList.size(); i++) {
            nodes.add(new Node());
        }

        for (int nodeId = 0; nodeId < adjacencyList.size(); nodeId++) {
            findScc(nodeId, currentVisitIndex, nodes, visitOrder, components);
        }

        return components.get(0);
    }

    private void findScc(final int nodeId, Integer currentVisitIndex, List<Node> nodes,
                         Stack<Integer> visitOrder, List<List<String>> components) {
        Node node = nodes.get(nodeId);
        node.visitIndex = node.leastVisitIndex = currentVisitIndex++;
        node.isExplored = true;
        visitOrder.push(nodeId);

        for (final int adjacentNodeId : adjacencyList.get(nodeId)) {
            Node adjacentNode = nodes.get(adjacentNodeId);
            if (adjacentNode.visitIndex == Constants.UNVISITED) {
                findScc(adjacentNodeId, currentVisitIndex, nodes, visitOrder, components);
            }
            if (adjacentNode.isExplored) {
                node.leastVisitIndex = Math.min(node.leastVisitIndex, adjacentNode.leastVisitIndex);
            }
        }

        if (node.visitIndex == node.leastVisitIndex) {
            List<String> component = new ArrayList<>();
            while (true) {
                int adjacentNodeId = visitOrder.pop();
                nodes.get(adjacentNodeId).isExplored = false;
                component.add(wordIndex.get(adjacentNodeId));

                if (nodeId == adjacentNodeId) {
                    break;
                }
            }
            components.add(component);
        }
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        int numDictionaryWords;
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        while ((numDictionaryWords = Integer.parseInt(reader.readLine())) != 0) {
            List<DictionaryEntry> rawAdjacencyList = new ArrayList<>();
            for (int i = 0; i < numDictionaryWords; i++) {
                StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
                DictionaryEntry entry = new DictionaryEntry();

                entry.word = tokenizer.nextToken();
                while (tokenizer.hasMoreTokens()) {
                    entry.description.add(tokenizer.nextToken());
                }
                rawAdjacencyList.add(entry);
            }

            String separator = "";
            List<String> words = new SubDictionaryFinder(rawAdjacencyList).find();
            System.out.println(words.size());
            for (String word : words) {
                System.out.printf("%s%s", separator, word);
                separator = " ";
            }
        }
    }
}

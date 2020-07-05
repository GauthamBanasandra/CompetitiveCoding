// WIP

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

class SubDictionaryFinder {
    private final List<List<Integer>> adjacencyList;
    private final Map<Integer, String> reverseIndex;

    public SubDictionaryFinder(List<DictionaryEntry> rawAdjacencyList) {
        reverseIndex = new HashMap<>();
        adjacencyList = new ArrayList<>(rawAdjacencyList.size());
        for (int i = 0; i < rawAdjacencyList.size(); i++) {
            adjacencyList.add(new ArrayList<>());
        }

        int id = 0;
        Map<String, Integer> index = new HashMap<>();
        for (DictionaryEntry entry : rawAdjacencyList) {
            int keyId = index.getOrDefault(entry.word, id + 1);
            id = Math.max(id, keyId);
            index.putIfAbsent(entry.word, keyId);
            reverseIndex.putIfAbsent(keyId, entry.word);

            List<Integer> adjacentNodes = adjacencyList.get(keyId);
            for (String value : entry.description) {
                int valueId = index.getOrDefault(value, id + 1);
                id = Math.max(id, valueId);
                index.putIfAbsent(value, valueId);
                reverseIndex.putIfAbsent(valueId, value);
                adjacentNodes.add(valueId);
            }
        }
    }

    /*public List<String> find() {
        Integer currentVisitIndex = 0;
        List<Node> nodes = new ArrayList<>(adjacencyList.size());

    }*/

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
                component.add(reverseIndex.get(adjacentNodeId));

                if (nodeId == adjacentNodeId) {
                    break;
                }
            }
            components.add(component);
        }
    }
}

public class Main {
}

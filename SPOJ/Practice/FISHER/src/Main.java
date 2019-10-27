// WA

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;

class Item {
    public Item(long cost, int id, int fromId, long time) {
        this.cost = cost;
        this.id = id;
        this.fromId = fromId;
        this.time = time;
    }

    public long getCost() {
        return cost;
    }

    public int getId() {
        return id;
    }

    public int getFromId() {
        return fromId;
    }

    public long getTime() {
        return time;
    }

    private long cost, time;
    private int id, fromId;
}

class SortByCost implements Comparator<Item> {
    @Override
    public int compare(Item a, Item b) {
        return Long.compare(a.getCost(), b.getCost());
    }
}

class CostAndTime {
    public CostAndTime(long cost, long time) {
        this.cost = cost;
        this.time = time;
    }

    public long getCost() {
        return cost;
    }

    public long getTime() {
        return time;
    }

    private long cost, time;
}

class Scheduler {
    public Scheduler(long[][] costAdjMatrix, long[][] timeAdjMatrix, long timeLimit) {
        this.costAdjMatrix = costAdjMatrix;
        this.timeAdjMatrix = timeAdjMatrix;
        this.timeLimit = timeLimit;
        numNodes = costAdjMatrix.length;
        destination = numNodes - 1;
    }

    public CostAndTime getMinCostAndTime() {
        CostAndTime[][] min = getCostAndTimeCollection();
        PriorityQueue<Item> order = new PriorityQueue<>(costAdjMatrix.length * costAdjMatrix.length,
                new SortByCost());

        for (int i = 0; i < numNodes; i++) {
            min[i][source] = new CostAndTime(0, 0);
        }
        order.add(new Item(0, source, 0, 0));

        while (!order.isEmpty()) {
            Item node = order.remove();
            if (node.getCost() > min[node.getFromId()][node.getId()].getCost()) {
                continue;
            }

            for (int adjNodeId = 0; adjNodeId < numNodes; adjNodeId++) {
                if (adjNodeId == node.getId()) {
                    continue;
                }

                long adjCost = min[node.getFromId()][node.getId()].getCost() + costAdjMatrix[node.getId()][adjNodeId];
                long adjTime = min[node.getFromId()][node.getId()].getTime() + timeAdjMatrix[node.getId()][adjNodeId];
                if (adjCost < min[node.getId()][adjNodeId].getCost() && adjTime < timeLimit) {
                    min[node.getId()][adjNodeId] = new CostAndTime(adjCost, adjTime);
                    order.add(new Item(adjCost, adjNodeId, node.getId(), adjTime));
                } else if (adjCost == min[node.getId()][adjNodeId].getCost() &&
                        adjTime < min[node.getId()][adjNodeId].getTime()) {
                    min[node.getId()][adjNodeId] = new CostAndTime(adjCost, adjTime);
                }
            }
        }
        return getMinDestination(min);
    }

    private CostAndTime[][] getCostAndTimeCollection() {
        CostAndTime[][] items = new CostAndTime[numNodes][numNodes];
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                items[i][j] = new CostAndTime(Integer.MAX_VALUE, Integer.MAX_VALUE);
            }
        }
        return items;
    }

    private CostAndTime getMinDestination(CostAndTime[][] min) {
        CostAndTime minCostAndTime = null;
        for (int i = 0; i < numNodes; i++) {
            if (minCostAndTime == null) {
                minCostAndTime = min[i][destination];
                continue;
            }
            if (min[i][destination].getCost() < minCostAndTime.getCost()) {
                minCostAndTime = min[i][destination];
            }
        }
        return minCostAndTime;
    }

    private final long[][] costAdjMatrix, timeAdjMatrix;
    private final long timeLimit;
    private final int source = 0;
    private final int destination;
    private final int numNodes;
}

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            int numNodes = scanner.nextInt();
            int timeLimit = scanner.nextInt();
            if (numNodes == 0 && timeLimit == 0) {
                return;
            }

            long[][] timeAdjMatrix = new long[numNodes][numNodes];
            long[][] costAdjMatrix = new long[numNodes][numNodes];
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    timeAdjMatrix[i][j] = scanner.nextInt();
                }
            }
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    costAdjMatrix[i][j] = scanner.nextInt();
                }
            }

            CostAndTime min = (new Scheduler(costAdjMatrix, timeAdjMatrix, timeLimit)).getMinCostAndTime();
            System.out.printf("%d %d\n", min.getCost(), min.getTime());
        }
    }
}

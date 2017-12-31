import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

enum NodeType {
    LEFT_CHILD,
    RIGHT_CHILD,
    ROOT
}

interface AccessCollection<C, T> {
    T access(C collectionCookie, int index);
}

interface VisitAction<T> {
    void visit(Node<T> n);
}

interface MergeNodes<T> {
    T merge(T d1, T d2);
}

class Node<T> {
    public Node(T data, NodeType type) {
        this.type = type;
        this.data = data;
    }

    public void remove(Node<T> n) {
        n.leftChild = n.rightChild = null;
        Node<T> ancestor = n.ancestor;
        switch (n.type) {
            case LEFT_CHILD:
                ancestor.leftChild = null;
                break;

            case RIGHT_CHILD:
                ancestor.rightChild = null;
                break;

            case ROOT:
                break;

            default:
                // Unhandled node type
                assert false;
        }
    }

    public NodeType type;
    public Node<T> ancestor;
    public Node<T> leftChild;
    public Node<T> rightChild;
    public long height;
    public T data;
}

class BinaryTree<T> {
    public BinaryTree() {
        this.root = null;
    }

    // A utility function to get the height of the node
    public long height() {
        return height(root);
    }

    public static <U> long height(Node<U> n) {
        if (n == null) {
            return 0L;
        }

        long leftChildHeight = height(n.leftChild);
        long rightChildHeight = height(n.rightChild);
        return Math.max(leftChildHeight, rightChildHeight) + 1L;
    }

    // Traversal methods with visitAction as a lambda
    public void preOrder(VisitAction<T> visitAction) {
        preOrder(root, visitAction);
    }

    public void postOrder(VisitAction<T> visitAction) {
        postOrder(root, visitAction);
    }

    public void inOrder(VisitAction<T> visitAction) {
        inOrder(root, visitAction);
    }

    private void preOrder(Node<T> n, VisitAction<T> visitAction) {
        if (n == null) {
            return;
        }

        visitAction.visit(n);
        preOrder(n.leftChild, visitAction);
        preOrder(n.rightChild, visitAction);
    }

    private void postOrder(Node<T> n, VisitAction<T> visitAction) {
        if (n == null) {
            return;
        }

        postOrder(n.leftChild, visitAction);
        postOrder(n.rightChild, visitAction);
        visitAction.visit(n);
    }

    private void inOrder(Node<T> n, VisitAction<T> visitAction) {
        if (n == null) {
            return;
        }

        inOrder(n.leftChild, visitAction);
        visitAction.visit(n);
        inOrder(n.rightChild, visitAction);
    }

    // TODO : Add replace method to replace a node in the tree
    public Node<T> root;
}

class Range {
    public Range(int lowerBound, int upperBound) {
        this.lowerBound = lowerBound;
        this.upperBound = upperBound;
    }

    public int lowerBound;
    public int upperBound;
}

class Response<T> {
    public Response(boolean isValid, T data) {
        this.isValid = isValid;
        this.data = data;
    }

    public boolean isValid;
    public T data;
}

enum UpdateMode {
    MEMORY,
    MEMORYLESS
}

class SegmentTree<C, T> extends BinaryTree<T> {
    public SegmentTree(C collection, int size, AccessCollection<C, T> accessCollection, MergeNodes<T> mergeNodes) {
        this.collection = collection;
        this.size = size;
        this.accessCollection = accessCollection;
        this.mergeNodes = mergeNodes;
        lazyStore = new HashMap<>();

        Range segment = new Range(0, size - 1);
        super.root = buildTree(NodeType.ROOT, segment);
    }

    public Response<T> query(Range querySegment) {
        Range segment = new Range(0, size - 1);
        return query(super.root, segment, querySegment);
    }

    private Response<T> query(Node<T> n, Range segment, Range querySegment) {
        if ((querySegment.lowerBound > segment.upperBound) || (querySegment.upperBound < segment.lowerBound)) {
            return new Response<>(false, null);
        }

        if (lazyStore.containsKey(n)) {
            T lazyData = lazyStore.get(n);
            n.data = mergeNodes.merge(n.data, lazyData);
            propagateLaziness(n, lazyData);
            lazyStore.remove(n);
        }

        if ((segment.lowerBound >= querySegment.lowerBound) && (segment.upperBound <= querySegment.upperBound)) {
            return new Response<>(true, n.data);
        }

        Range leftSegment = new Range(segment.lowerBound, (segment.lowerBound + segment.upperBound) >> 1);
        Response<T> leftResponse = query(n.leftChild, leftSegment, querySegment);

        Range rightSegment = new Range(leftSegment.upperBound + 1, segment.upperBound);
        Response<T> rightResponse = query(n.rightChild, rightSegment, querySegment);

        if (!leftResponse.isValid) {
            return rightResponse;
        }

        if (!rightResponse.isValid) {
            return leftResponse;
        }

        return new Response<>(true, mergeNodes.merge(leftResponse.data, rightResponse.data));
    }

    private void propagateLaziness(Node<T> n, T data) {
        if (n.leftChild != null && n.rightChild != null) {
            return;
        }

        if (lazyStore.containsKey(n.leftChild)) {
            T lazyData = lazyStore.get(n.leftChild);
            lazyStore.put(n.leftChild, mergeNodes.merge(lazyData, data));
        } else {
            lazyStore.put(n.leftChild, data);
        }

        if (lazyStore.containsKey(n.rightChild)) {
            T lazyData = lazyStore.get(n.rightChild);
            lazyStore.put(n.rightChild, mergeNodes.merge(lazyData, data));
        } else {
            lazyStore.put(n.rightChild, data);
        }
    }

    private Node<T> buildTree(NodeType type, Range segment) {
        if (segment.lowerBound == segment.upperBound) {
            return new Node<>(accessCollection.access(collection, segment.lowerBound), type);
        }

        Range leftSegment = new Range(segment.lowerBound, (segment.lowerBound + segment.upperBound) >> 1);
        Node<T> leftChild = buildTree(NodeType.LEFT_CHILD, leftSegment);

        Range rightSegment = new Range(leftSegment.upperBound + 1, segment.upperBound);
        Node<T> rightChild = buildTree(NodeType.RIGHT_CHILD, rightSegment);

        Node<T> parent = new Node<>(mergeNodes.merge(leftChild.data, rightChild.data), type);
        parent.leftChild = leftChild;
        parent.rightChild = rightChild;
        leftChild.ancestor = rightChild.ancestor = parent;
        return parent;
    }

    public C collection;
    public int size;
    public MergeNodes<T> mergeNodes;
    public AccessCollection<C, T> accessCollection;

    private HashMap<Node<T>, T> lazyStore;
}

class Main {
    public static void main(String[] args) {
        int n, q;
        int[] data;
        Scanner in = new Scanner(System.in);

        while (true) {
            n = in.nextInt();
            if (n == 0) {
                break;
            }

            q = in.nextInt();

            data = new int[n];
            for (int i = 0; i < n; i++) {
                data[i] = in.nextInt();
            }

            SegmentTree<int[], HashMap<Integer, Integer>> segTree = new SegmentTree<>(data, data.length,
                    (collection, index) -> {
                        HashMap<Integer, Integer> f = new HashMap<>();
                        f.put(collection[index], 1);
                        return f;
                    },
                    (d1, d2) -> {
                        HashMap<Integer, Integer> f = new HashMap<>();
                        for (Map.Entry<Integer, Integer> entry : d1.entrySet()) {
                            f.put(entry.getKey(), entry.getValue());
                        }

                        for (Map.Entry<Integer, Integer> entry : d2.entrySet()) {
                            Integer key = entry.getKey();
                            f.put(key, f.getOrDefault(key, 0) + entry.getValue());
                        }

                        return f;
                    });

            while (q-- > 0) {
                Range querySegment = new Range(in.nextInt() - 1, in.nextInt() - 1);
                Response<HashMap<Integer, Integer>> response = segTree.query(querySegment);
                System.out.println(Collections.max(response.data.values()));
            }
        }
    }
}

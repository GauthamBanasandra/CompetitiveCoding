__author__ = 'gauth_000'

stack = []


def push(vertex):
    stack.append(vertex)


def pop():
    return stack.pop()


def find_edge(vertex, edges):
    for edge in edges:
        if edge[0] == vertex or edge[1] == vertex:
            return edge
    return None


def dfs(vertex, edges):
    vertices = 0
    push(vertex)
    while len(stack) > 0:
        edge = find_edge(stack[-1], edges)
        if edge:
            if edge[0] not in stack:
                push(edge[0])
            else:
                push(edge[1])
            edges.remove(edge)
        else:
            pop()
            vertices += 1
    return vertices


def get_edges():
    edges = []
    for i in range(int(str(input()).strip().split()[1])):
        vertices = str(input()).strip().split()
        edges.append((int(vertices[0]), int(vertices[1])))
    return edges


def main():
    edges_removed = 0
    edges = get_edges()
    for edge in edges:
        temp_edges = edges.copy()
        temp_edges.remove(edge)
        if dfs(edge[0], temp_edges) % 2 == 0 and dfs(edge[1], temp_edges) % 2 == 0:
            edges_removed += 1
    print(edges_removed)


if __name__ == '__main__':
    main()

#include <iostream>
#include <stack>
#include <queue>
#include <sstream>

int main(int argc, char *argv[]) {
    int op, k, n;
    std::string line;
    std::stack<int> stack;
    std::queue<int> queue;
    std::priority_queue<int> priority_queue;
    auto is_stack = true, is_queue = true, is_priority_queue = true;

    while (std::cin >> n) {
        std::cin.ignore();
        is_stack = is_queue = is_priority_queue = true;
        while (!stack.empty()) {
            stack.pop();
        }

        while (!queue.empty()) {
            queue.pop();
        }

        while (!priority_queue.empty()) {
            priority_queue.pop();
        }

        while (n--) {
            getline(std::cin, line);
            std::istringstream tokenizer(line);
            tokenizer >> op >> k;
            switch (op) {
                case 1:
                    if (is_stack) {
                        stack.push(k);
                    }

                    if (is_queue) {
                        queue.push(k);
                    }

                    if (is_priority_queue) {
                        priority_queue.push(k);
                    }
                    break;

                case 2:
                    if (is_stack) {
                        if (stack.empty()) {
                            is_stack = false;
                        } else {
                            is_stack = stack.top() == k;
                            stack.pop();
                        }
                    }

                    if (is_queue) {
                        if (queue.empty()) {
                            is_queue = false;
                        } else {
                            is_queue = queue.front() == k;
                            queue.pop();
                        }
                    }

                    if (is_priority_queue) {
                        if (priority_queue.empty()) {
                            is_priority_queue = false;
                        } else {
                            is_priority_queue = priority_queue.top() == k;
                            priority_queue.pop();
                        }
                    }
                    break;

                default:;
            }
        }

        if (is_stack && is_queue && is_priority_queue || is_stack && is_queue || is_stack && is_priority_queue ||
            is_queue && is_priority_queue) {
            std::cout << "not sure" << std::endl;
        } else if (is_stack) {
            std::cout << "stack" << std::endl;
        } else if (is_queue) {
            std::cout << "queue" << std::endl;
        } else if (is_priority_queue) {
            std::cout << "priority queue" << std::endl;
        } else {
            std::cout << "impossible" << std::endl;
        }

        if (std::cin.eof()) {
            break;
        }
    }

    return 0;
}

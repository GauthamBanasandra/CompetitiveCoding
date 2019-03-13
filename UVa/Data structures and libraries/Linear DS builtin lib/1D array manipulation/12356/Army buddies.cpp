#include <stdio.h>
#include <ios>
#include <unordered_map>

struct Soldier {
    int n;
    Soldier *left;
    Soldier *right;
};

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    int s, b, l, r;
    std::unordered_map<int, Soldier> at_ln;
    while (scanf("%d %d\n", &s, &b), s || b) {
        for (auto i = 1; i <= s; ++i) {
            at_ln[i].n = i;
            if (i > 1) {
                at_ln[i].left = &at_ln[i - 1];
                at_ln[i - 1].right = &at_ln[i];
            }
        }

        for (auto i = 0; i < b; ++i) {
            scanf("%d %d\n", &l, &r);
            const auto lb = at_ln[l].left;
            const auto rb = at_ln[r].right;
            if (lb == nullptr && rb == nullptr) {
                printf("* *\n");
            } else if (lb == nullptr && rb != nullptr) {
                printf("* %d\n", rb->n);
                rb->left = nullptr;
            } else if (lb != nullptr && rb == nullptr) {
                printf("%d *\n", lb->n);
                lb->right = nullptr;
            } else {
                printf("%d %d\n", lb->n, rb->n);
                lb->right = rb;
                rb->left = lb;
            }

            at_ln[l].left = at_ln[r].right = nullptr;
        }

        printf("-\n");
    }

    return 0;
}

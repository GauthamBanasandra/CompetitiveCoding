#include <stdio.h>
#include <ios>
#include <string>
#include <math.h>

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);

    int n;
    while (scanf("%d", &n), n != 0) {
        const auto s = static_cast<int>(ceil(n / 4.0));
        auto r = 4 * s, l = 1, b = 0;
        auto front = true;
        std::string l_label, r_label;
        printf("Printing order for %d pages:\n", n);
        for (auto i = 0; i < 2 * s; ++i) {
            b = 0;
            const char *face = front ? "front" : "back";
            if (l <= n) {
                l_label = std::to_string(l);
            } else {
                l_label = "Blank";
                ++b;
            }

            if (r <= n) {
                r_label = std::to_string(r);
            } else {
                r_label = "Blank";
                ++b;
            }

            if (b > 1) {
                continue;
            }

            printf("Sheet %d, %-5s: %s, %s\n", static_cast<int>(ceil((i + 1) / 2.0)), front ? "front" : "back",
                   (front ? r_label : l_label).c_str(), (front ? l_label : r_label).c_str());
            front = !front;
            --r;
            ++l;
        }
    }

    return 0;
}

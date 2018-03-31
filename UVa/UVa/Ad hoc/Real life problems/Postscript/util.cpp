#include <stdio.h>

#define PAGE_ROW 60
#define PAGE_COL 60

extern char page[PAGE_ROW + 10][PAGE_COL + 10];

void PrintPage() {
    for (auto i = 0; i < PAGE_ROW; ++i) {
        for (auto j = 0; j < PAGE_COL; ++j) {
            printf("%c", page[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    for (auto i = 0; i < PAGE_ROW; ++i) {
        printf("-");
    }

    printf("\n\n");
}

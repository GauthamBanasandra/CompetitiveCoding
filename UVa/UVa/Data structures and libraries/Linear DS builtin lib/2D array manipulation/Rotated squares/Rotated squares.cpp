#include <iostream>
#include <vector>

using big_int = unsigned long long;

inline void Swap(char *a, char *b) {
    const auto t = *a;
    *a = *b;
    *b = t;
}

class SqMatrix {
private:
    big_int dim;
    std::vector<std::string> m;

    bool MatchSubMatrix(const SqMatrix &n, big_int m_i, big_int m_j) const;

public:
    SqMatrix(big_int dim);

    ~SqMatrix();

    void PrintMatrix();

    void Rotate90Clk();

    big_int FindMatchF(const SqMatrix &n) const;

    auto operator[](big_int i) const -> decltype(m[i]) { return m[i]; }
};

SqMatrix::SqMatrix(big_int dim) {
    this->dim = dim;
    m.reserve(dim);
    for (auto i = 0; i < dim; i++) {
        m.push_back("");
        getline(std::cin, m[i]);
    }
}

SqMatrix::~SqMatrix() {
}

void SqMatrix::PrintMatrix() {
    for (auto i = 0; i < dim; i++) {
        std::cout << m[i] << std::endl;
    }
}

void SqMatrix::Rotate90Clk() {
    for (auto i = 0; i < dim >> 1; i++) {
        for (auto j = 0; j < (dim + 1) >> 1; j++) {
            auto &a = m[i][j];
            auto &b = m[j][dim - i - 1];
            auto &c = m[dim - i - 1][dim - j - 1];
            auto &d = m[dim - j - 1][i];

            auto t = a;
            Swap(&b, &t);
            Swap(&c, &t);
            Swap(&d, &t);
            Swap(&a, &t);
        }
    }
}

big_int SqMatrix::FindMatchF(const SqMatrix &n) const {
    big_int f = 0;
    if (dim < n.dim) {
        return f;
    }

    for (auto i = 0; i <= dim - n.dim; ++i) {
        for (auto j = 0; j <= dim - n.dim; ++j) {
            if (MatchSubMatrix(n, i, j)) {
                ++f;
            }
        }
    }

    return f;
}

bool SqMatrix::MatchSubMatrix(const SqMatrix &n, big_int m_i, big_int m_j) const {
    for (auto n_i = 0; n_i < n.dim; ++n_i) {
        for (auto n_j = 0; n_j < n.dim; ++n_j) {
            if (m[m_i + n_i][m_j + n_j] != n[n_i][n_j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    big_int N, n;
    while (scanf("%llu %llu\n", &N, &n), N || n) {
        SqMatrix Nm(N);
        SqMatrix nm(n);

        const auto r0 = Nm.FindMatchF(nm);
        nm.Rotate90Clk();

        const auto r90 = Nm.FindMatchF(nm);
        nm.Rotate90Clk();

        const auto r180 = Nm.FindMatchF(nm);
        nm.Rotate90Clk();

        const auto r270 = Nm.FindMatchF(nm);

        printf("%llu %llu %llu %llu\n", r0, r90, r180, r270);
    }

    return 0;
}

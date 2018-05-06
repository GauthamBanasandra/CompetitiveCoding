//
// Created by gauth on 06-05-2018.
//

#include <utility>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>

struct Piece {
public:
    Piece() = default;

    explicit Piece(std::pair<int, int> patterns_) : patterns(std::move(patterns_)) {}

    bool IsSame(const Piece &other) const {
        return (patterns.first == other.patterns.first && patterns.second == other.patterns.second) ||
               (patterns.first == other.patterns.second && patterns.second == other.patterns.first);
    }

    bool IsValidNeighbour(const Piece &other) const {
        return patterns.second == other.patterns.first;
    }

    std::pair<int, int> patterns;
};

class Deck {
public:
    explicit Deck(const std::vector<Piece> &pieces);

    std::list<Piece> GetPieces(int pattern) const;

    void AddPiece(const Piece &piece);

    void RemovePiece(const Piece &piece);

private:
    void RemovePiece(int pattern, const Piece &piece);

    std::unordered_multimap<int, int> pieces_;
};

Deck::Deck(const std::vector<Piece> &pieces) {
    for (const auto &piece : pieces) {
        AddPiece(piece);
    }
}

std::list<Piece> Deck::GetPieces(int pattern) const {
    const auto eq = pieces_.equal_range(pattern);
    return std::list<Piece>(eq.first, eq.second);
}

void Deck::AddPiece(const Piece &piece) {
    pieces_.insert({piece.patterns.first, piece.patterns.second});
    pieces_.insert({piece.patterns.second, piece.patterns.first});
}

void Deck::RemovePiece(const Piece &piece) {
    RemovePiece(piece.patterns.first, piece);
    RemovePiece(piece.patterns.second, piece);
}

void Deck::RemovePiece(int pattern, const Piece &piece) {
    const auto eq = pieces_.equal_range(pattern);
    for (auto it = eq.first; it != eq.second; ++it) {
        if (Piece(std::make_pair(it->first, it->second)).IsSame(piece)) {
            pieces_.erase(it);
            break;
        }
    }
}

class DominoesSolitaire {
public:
    DominoesSolitaire(const int n, std::pair<Piece, Piece> extremes, std::vector<Piece> pieces) : n_(
            n), extremes_(std::move(extremes)), pieces_(std::move(pieces)) {}

    bool IsPossible() const;

private:
    bool IsPossible(std::size_t i_place, std::vector<Piece> &combination, Deck &deck) const;

    const int n_;
    const std::pair<Piece, Piece> extremes_;
    const std::vector<Piece> pieces_;
};

bool DominoesSolitaire::IsPossible(std::size_t i_place, std::vector<Piece> &combination, Deck &deck) const {
    const auto previous = combination[i_place - 1];
    if (i_place + 1 == combination.size()) {
        return previous.IsValidNeighbour(combination[i_place]);
    }

    for (const auto piece : deck.GetPieces(previous.patterns.second)) {
        deck.RemovePiece(piece);
        combination[i_place] = piece;
        if (IsPossible(i_place + 1, combination, deck)) {
            return true;
        }

        deck.AddPiece(piece);
    }

    return false;
}

bool DominoesSolitaire::IsPossible() const {
    std::vector<Piece> combination(n_ + 2);
    Deck deck(pieces_);

    combination[0] = extremes_.first;
    combination[combination.size() - 1] = extremes_.second;

    return IsPossible(1, combination, deck);
}

int main() {
    std::pair<Piece, Piece> extremes;
    std::vector<Piece> pieces{};

    int n, m, i, j;

    while (std::cin >> n >> m, n) {
        std::cin >> i >> j;
        extremes.first = Piece(std::make_pair(i, j));
        std::cin >> i >> j;
        extremes.second = Piece(std::make_pair(i, j));

        pieces.clear();
        pieces.reserve(m);
        for (int k = 0; k < m; ++k) {
            std::cin >> i >> j;
            pieces.emplace_back(std::make_pair(i, j));
        }

        std::cout << (DominoesSolitaire(n, extremes, pieces).IsPossible() ? "YES" : "NO") << std::endl;
    }

    return 0;
}
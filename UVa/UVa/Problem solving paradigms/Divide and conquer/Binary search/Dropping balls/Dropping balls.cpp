//
// Created by gauth on 02-06-2018.
//

#include <cmath>
#include <iostream>

struct LeafInfo {
    explicit LeafInfo(int depth);

    bool IsLeafNode(int index) const {
        return (index >= i_begin) && (index <= i_end);
    }

private:
    int i_begin;
    int i_end;
};

LeafInfo::LeafInfo(int depth) {
    i_begin = 1 << (depth - 1);
    i_end = (1 << depth) - 1;
}

class DroppingBalls {
public:
    DroppingBalls(int depth, int i_ball) : depth_(depth), i_ball_(i_ball), leaf_info_(LeafInfo(depth)) {}

    int GetLeafNodeIndex();

private:
    int NextNode(int i_node, int i_virtual_ball);

    int depth_, i_ball_;
    LeafInfo leaf_info_;
};

int DroppingBalls::NextNode(int i_node, int i_virtual_ball) {
    if (leaf_info_.IsLeafNode(i_node)) {
        return i_node;
    }

    auto i_virtual_next_ball = static_cast<int>(std::ceil(i_virtual_ball / 2.0));
    if (i_virtual_next_ball & 1) {
        return NextNode(i_node * 2, i_virtual_next_ball);
    }

    return NextNode((i_node * 2) + 1, i_virtual_next_ball);
}

int DroppingBalls::GetLeafNodeIndex() {
    return NextNode(1, i_ball_ * 2);
}

int main() {
    int l, d, k;

    std::cin >> l;
    for (int i = 0; i < l; ++i) {
        std::cin >> d >> k;
        std::cout << DroppingBalls(d, k).GetLeafNodeIndex() << std::endl;
    }

    return 0;
}
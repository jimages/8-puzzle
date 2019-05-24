#include <utility>
#include <utility>
#include <cstring>
#include <cassert>
#include <cmath>
#include <initializer_list>
/**
 * Author: Zachray Wang (jimages123@gmail.com)
 * Desc:
 *  The base borad.
 */

class Board {

    int b[3*3] = {0};
public:
    std::pair<size_t, size_t> zero_loc = {0,0};
    Board *parent = nullptr;
    Board() = default;
    Board(const Board &a): zero_loc(a.zero_loc) {
        std::memcpy(b, a.b, sizeof b);
        parent = a.parent;
    }
    // 直接复制数组
    explicit Board(const int a[3*3]) {
        std::memcpy(b, a, sizeof b);
    }

    // 棋盘的初始化方法，接受花括号的方法
    explicit Board(std::initializer_list<int> a) {
        assert(a.size() == 9);
        // 用于计数棋盘中0的棋子的个数
        int zero_count = 0;
        for (auto n = 0; a.begin() + n != a.end(); ++n) {
            b[n] = *(a.begin() + n);
            if (b[n] == 0) {
                zero_loc.second = (n / 3);
                zero_loc.first = n % 3;
                ++zero_count;
            }
        }
        assert(zero_count == 1);
    }

    int& operator()(size_t x, size_t y) {
        assert(x < 3 && y < 3);
        return b[ x + 3 * y];
    }
    int& operator[](std::pair<size_t, size_t> l) {
        return (*this)(l.first, l.second);
    }

    // 交换两个棋子
    Board exchange(std::pair<size_t, size_t> A, std::pair<size_t, size_t> B) const {
        Board n(*this);
        // 检查有一个位置必须为0
        assert(A == zero_loc || B == zero_loc);
        // 检查A B的边界位于[0:3) 之间
        assert(A.first < 3 && A.second < 3 && B.first >= 0 && B.second >= 0);
        // 检查A，B位置不能相同
        assert(A != B);
        // 检查A，B的位置必须相邻
        assert((std::abs((long)(A.first - B.first)) + std::abs((long)(A.second - B.second))) == 1);

        std::swap(n[A], n[B]);
        n.zero_loc = A == zero_loc? B: A;
        return n;
    }

    bool operator==(const Board &t) const {
        for (size_t n = 0; n < (sizeof(b) / sizeof(b[0])) ; ++n) {
            if (b[n] != t.b[n])
                return false;
        }
        return true;
    }

    size_t same(const Board &t) const {
        size_t count = 0;
        for (size_t n = 0; n < (sizeof(b) / sizeof(b[0])); ++n) {
            if (b[n] == t.b[n] && b[n] != 0)
                ++count;
        }
        return count;
    }
    bool operator<(const Board &b) const;
};

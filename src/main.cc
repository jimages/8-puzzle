#include <iostream>
#include <algorithm>
#include <utility>
#include <deque>
#include <vector>
#include <queue>
#include "board.h"
#include <functional>

/**
 * Author: Zachary Wang
 * Desc:
 *  八数码难题游戏问题
 */
Board target{7,6,5,8,0,4,1,2,3};
bool Board::operator<(const Board &b) const {
    return this->same(target) < b.same(target);
}

int main(void) {
    Board b{8,1,0,6,4,2,7,5,3};
    // 计数工作
    size_t count = 0;
    std::deque<Board> path;
    std::priority_queue<Board, std::deque<Board>> search_tree;
    search_tree.push(b);
    std::vector<std::pair<int, int> > mov_vec = {
        {1,0},{-1,0},{0,1},{0,-1}
    };

    // 然后采用深度优先搜索
    while (!search_tree.empty()) {
        auto p = search_tree.top();
        auto zero_loc = p.zero_loc;

        path.push_back(p);
        search_tree.pop();
        // 性能估计
        ++count;
        // 检查是否满足要求
        if (p == target)
            goto good;

        // 找到可行的搜索区域
        for (auto mov = mov_vec.cbegin(); mov != mov_vec.cend(); ++mov) {
            auto tartloc = std::make_pair(zero_loc.first + mov->first, zero_loc.second + mov->second);
            // 位置必须符合要求
            if (tartloc.first < 3 && tartloc.first >= 0 && tartloc.second < 3 && tartloc.second >= 0) {
                auto tart = p.exchange(zero_loc, tartloc);
                if (std::find(path.cbegin(), path.cend(), tart) == path.cend()) {
                    tart.parent = &path.back();
                    search_tree.push(tart);
                }
            }
        }
    }
    std::cout << "不存在解" << std::endl;
    return 0;

good:
    // 输出结果
    for (auto n = path.cbegin(); n != path.cend(); ++n)
        std::cout << "x=" << n->zero_loc.first << "\ty=" << n->zero_loc.second << std::endl;

    // 计算步数
    auto s = 0;
    for (auto n = path.back(); !(n == b); n = *n.parent)
        ++s;
    std::cout << s << std::endl;
    std::cout << count << std::endl;
    return 0;
}

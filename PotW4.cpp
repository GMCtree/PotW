#include <iostream>
#include <vector>
#include <algorithm>

struct sub_rect {
    int sum;
    int left;
    int right;
    int start;
    int end;

    sub_rect(int a, int b, int c) : sum(a), start(b), end(c) { }
};

sub_rect kadane(const std::vector<int>& v) {
    int cur = v[0], max_sum = v[0];
    int cur_start = 0, cur_end = 0;
    int max_start = 0, max_end = 0;

    for (unsigned i = 1; i < v.size(); ++i) {
        if (cur < 0) {
            cur = v[i];
            cur_start = i;
        } else {
            cur += v[i];
            cur_end = i;
        }

        if (cur > max_sum) {
            max_sum = cur;
            max_start = cur_start;
            max_end = cur_end;
        }
    }
    return {max_sum, max_start, max_end};
}

std::ostream& operator <<(std::ostream& os, sub_rect& rect) {
    os << "(" << rect.start << ", " << rect.left << ") ";
    os << "(" << rect.end << ", " << rect.right << ") ";
    os << rect.sum;
    return os;
}

// maximum sub rectangle for a 2d array
sub_rect two_d_kadane(const std::vector<std::vector<int>>& m) {
    sub_rect ret(m[0][0], 0, 0);
    for (unsigned left = 0; left < m[0].size(); ++left) {
        std::vector<int> tmp(m.size(), 0);
        for (unsigned right = left; right < m[0].size(); ++right) {
            for (unsigned i = 0; i < m.size(); ++i)
                tmp[i] += m[i][right];

            auto rect = kadane(tmp);
            if (rect.sum > ret.sum) {
                ret = rect;
                ret.left = left;
                ret.right = right;
            }
        }
    }

    return ret;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n);
    for (int i = 0; i < n; ++i) {
        std::vector<int> v(m);
        for (int j = 0; j < m; ++j) {
            std::cin >> v[j];
        }
        matrix[i] = v;
    }

    sub_rect rect = two_d_kadane(matrix);
    std::cout << rect << std::endl;

    return 0;
}
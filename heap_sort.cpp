//
// Created by lzs on 11/22/20.
//

#include <vector>
#include <iostream>
#include <cstdlib>


static int left(const int i) {
    return 2 * i + 1;
}

static int right(const int i) {
    return 2 * i + 2;
}

static void heapify(std::vector<int> &array, const int sz, const int i) {
    int min = i;
    for (;;) {
        const int p = min;
        const int l = left(min);
        const int r = right(min);

        if (l < sz && array[min] < array[l]) {
            min = l;
        }
        if (r < sz && array[min] < array[r]) {
            min = r;
        }
        if (min == p) {
            break;
        }
        std::swap(array[min], array[p]);
    }

}

static void build_heap(std::vector<int> &array) {
    const ssize_t sz = array.size();
    for (ssize_t i = sz / 2 - 1; i >= 0; i--) {
        heapify(array, sz, i);
    }
}


static void heap_sort(std::vector<int> &array) {
    build_heap(array);

    for (auto sz = array.size(); sz >= 2; sz--) {
        std::swap(array[0], array[sz - 1]);
        heapify(array, sz - 1, 0);
    }
}

int main(int argc, char **argv) {
    int len = 10;
    if (argc >= 2) {
        len = std::atoi(argv[1]);
    }

    srandom(time(nullptr));

    std::vector<int> array;
    for (int i = 0; i < len; i++) {
        array.push_back(random() % 100);
    }

    for (const auto &it: array) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    heap_sort(array);
    for (const auto &it: array) {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    return 0;
}
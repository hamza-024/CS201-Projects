#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

template <class RandomIt>
void print(RandomIt start, RandomIt end) {
    while (start != end) {
        std::cout << *start << " ";
        ++start;
    }
    std::cout << std::endl;
}

template< class RandomIt >
RandomIt partition(RandomIt first, RandomIt last) {
    // Choose the middle value as the pivot
    auto pivot = *(first + std::distance(first, last) / 2);
    
    // Move the pivot to the end for simpler comparison
    std::iter_swap(first + std::distance(first, last) / 2, last - 1);
    
    auto i = first - 1;
    for(auto j = first; j != last - 1; ++j) {
        if(*j <= pivot) {
            ++i;
            std::iter_swap(i, j);
        }
    }
    
    // Move the pivot back to its final place
    std::iter_swap(i + 1, last - 1);
    return i + 1;
}

template< class RandomIt >
void quicksort(RandomIt first, RandomIt last) {
    if(first < last) {
        auto pi = partition(first, last);
        quicksort(first, pi);
        quicksort(pi + 1, last);
    }
}


/*template< class RandomIt >
void heapify(RandomIt first, RandomIt last, RandomIt root) {
    auto heapSize = std::distance(first, last);
    auto distRoot = std::distance(first, root);
    auto largest = root;
    auto left = first + distRoot*2 + 1;
    auto right = left + 1;

    if(left < last && *left > *largest) {
        largest = left;
    }
    if(right < last && *right > *largest) {
        largest = right;
    }
    if(largest != root) {
        std::iter_swap(largest, root);
        heapify(first, last, largest);
    }
}

template< class RandomIt >
void heapsort(RandomIt first, RandomIt last) {
    for(auto it = first + std::distance(first, last)/2 - 1; it != first - 1; --it) {
        heapify(first, last, it);
    }
    for(auto it = last - 1; it != first; --it) {
        std::iter_swap(first, it);
        heapify(first, it, first);
    }
}*/

int main() {
    int a0[] = {56, 23, 11, 64, 43};
    std::array<int, 5> a1 = {5, 4, 3, 2, 1};
    std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
    std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

    // Perform heap sort on arrays
    quicksort(std::begin(a0), std::end(a0));
    print(std::begin(a0), std::end(a0));

    quicksort(a1.begin(), a1.end());
    print(a1.begin(), a1.end());

    // Convert std::array of strings to a vector for sorting
    std::vector<std::string> v2(a2.begin(), a2.end());
    quicksort(v2.begin(), v2.end());
    print(v2.begin(), v2.end());

    quicksort(v.begin(), v.end());
    print(v.begin(), v.end());

    return 0;
}

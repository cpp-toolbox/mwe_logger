#include "utility/logger/logger.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Logger instance
Logger logger("logger");

// Helper to join vector contents into a string
template <typename T> std::string join_vector(const std::vector<T> &vec, const std::string &sep = ", ") {
    std::string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += std::to_string(vec[i]);
        if (i + 1 < vec.size())
            result += sep;
    }
    return result;
}

void merge(std::vector<int> &arr, int left, int mid, int right) {
    LogSection ls(logger, "merge");

    logger.debug("Merging subarrays: left={}, mid={}, right={}", left, mid, right);

    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    logger.debug("Left part: {}", join_vector(L));
    logger.debug("Right part: {}", join_vector(R));

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    logger.debug("Merged result: {}", join_vector(std::vector<int>(arr.begin() + left, arr.begin() + right + 1)));
}

void merge_sort(std::vector<int> &arr, int left, int right) {
    LogSection ls(logger, "merge_sort");

    logger.debug("merge_sort called with left={}, right={}", left, right);

    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    } else {
        logger.debug("Base case reached for left={}, right={}", left, right);
    }
}

// Assuming logger, LogSection, join_vector, and merge_sort are already defined

int main() {
    logger.add_file_sink("logs.txt", true);

    LogSection ls(logger, "main");

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int num_vecs_to_produce = 1;
    std::vector<std::vector<int>> list_of_vectors;
    for (int i = 0; i < num_vecs_to_produce; ++i) {
        int vec_size = 10 + std::rand() % 21; // size between 10 and 30
        vec_size = 10;
        std::vector<int> vec;
        vec.reserve(vec_size);

        for (int j = 0; j < vec_size; ++j) {
            vec.push_back(std::rand() % 100); // values between 0 and 99
        }

        list_of_vectors.push_back(std::move(vec));
    }

    // Sort each vector
    for (size_t i = 0; i < list_of_vectors.size(); ++i) {
        LogSection vec_ls(logger, "Sorting vector {}", i + 1);

        logger.debug("Original array: {}", join_vector(list_of_vectors[i]));

        merge_sort(list_of_vectors[i], 0, list_of_vectors[i].size() - 1);

        logger.debug("Sorted array: {}", join_vector(list_of_vectors[i]));
    }

    {
        LogSection _(logger, "indentation_test");
        logger.debug("debug");
        logger.info("info");
        logger.error("error");
        logger.trace("trace");
        logger.warn("warn");
        logger.critical("critical");
    }

    {
        LogSection _(logger, "multiline logging test");
        logger.debug("line_one\nline_two");
    }

    return 0;
}

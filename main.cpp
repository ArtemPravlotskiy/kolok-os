#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>
#include <stdexcept>
#include <gtest/gtest.h>

// Function to compute the first n factorials
std::vector<unsigned long long> computeFactorials(size_t n) {
    if (n == 0) throw std::invalid_argument("n must be a natural number");
    std::vector<unsigned long long> factorials(n);
    factorials[0] = 1;
    for (size_t i = 1; i < n; ++i) {
        if (factorials[i - 1] > ULLONG_MAX / (i + 1)) 
            throw std::overflow_error("Factorial overflow");
        factorials[i] = factorials[i - 1] * (i + 1);
    }
    return factorials;
}

// Function to remove duplicates from a container
std::vector<int> removeDuplicates(const std::vector<int>& input) {
    std::unordered_set<int> unique_elements;
    std::vector<int> result;
    for (int num : input) {
        if (unique_elements.insert(num).second) {
            result.push_back(num);
        }
    }
    return result;
}

// Structure for linked list node
struct ListNode {
    int value;
    std::unique_ptr<ListNode> next;
    ListNode(int val) : value(val), next(nullptr) {}
};

// Function to reverse a linked list (recursive)
std::unique_ptr<ListNode> reverseList(std::unique_ptr<ListNode> head) {
    if (!head || !head->next) return std::move(head);
    std::unique_ptr<ListNode> new_head = reverseList(std::move(head->next));
    head->next->next = std::move(head);
    return new_head;
}

// Tests for factorial function
TEST(FactorialTest, SmallNumbers) {
    std::vector<unsigned long long> result = computeFactorials(5);
    EXPECT_EQ(result, (std::vector<unsigned long long>{1, 2, 6, 24, 120}));
}

TEST(FactorialTest, ZeroInput) {
    EXPECT_THROW(computeFactorials(0), std::invalid_argument);
}

// Tests for duplicate removal function
TEST(RemoveDuplicatesTest, GeneralCase) {
    std::vector<int> result = removeDuplicates({1, 2, 2, 3, 4, 4, 5});
    EXPECT_EQ(result, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(RemoveDuplicatesTest, EmptyInput) {
    std::vector<int> result = removeDuplicates({});
    EXPECT_TRUE(result.empty());
}

// Test for linked list reversal
TEST(ReverseListTest, GeneralCase) {
    auto head = std::make_unique<ListNode>(1);
    head->next = std::make_unique<ListNode>(2);
    head->next->next = std::make_unique<ListNode>(3);
    
    auto reversed = reverseList(std::move(head));
    EXPECT_EQ(reversed->value, 3);
    EXPECT_EQ(reversed->next->value, 2);
    EXPECT_EQ(reversed->next->next->value, 1);
    EXPECT_EQ(reversed->next->next->next, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

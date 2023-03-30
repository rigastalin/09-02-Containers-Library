#include <gtest/gtest.h>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "s21_array.cpp"
#include "s21_list.cpp"
#include "s21_map.cpp"
#include "s21_multiset.cpp"
#include "s21_queue.cpp"
#include "s21_set.cpp"
#include "s21_stack.cpp"
#include "s21_vector.cpp"

// <------------------------ QUEUE TESTS ------------------------>

TEST(s21_queue, test1) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  ASSERT_TRUE(s21_queue.size() == std_queue.size());
  ASSERT_TRUE(s21_queue.empty() == std_queue.empty());
}

TEST(s21_queue, test2) {
  s21::queue<int> s21_queue{18, 3, 1993};
  std::queue<int> std_queue;
  std_queue.push(18);
  std_queue.push(3);
  std_queue.push(1993);
  ASSERT_TRUE(s21_queue.size() == std_queue.size());
  ASSERT_TRUE(s21_queue.back() == std_queue.back());
  ASSERT_TRUE(s21_queue.front() == std_queue.front());
}

TEST(s21_queue, test3) {
  s21::queue<double> s21_queue{18.0, 3.0, 1993.12};
  std::queue<double> std_queue;
  std_queue.push(18.0);
  std_queue.push(3.0);
  std_queue.push(1993.12);
  ASSERT_TRUE(s21_queue.size() == std_queue.size());
  ASSERT_TRUE(s21_queue.back() == std_queue.back());
  ASSERT_TRUE(s21_queue.front() == std_queue.front());
}

TEST(s21_queue, test4) {
  s21::queue<std::pair<int, double>> s21_queue{{4, 20.0}, {18.0, 1993.12}};
  std::queue<std::pair<int, double>> std_queue;
  std_queue.push({4, 20});
  std_queue.push({18.0, 1993.12});
  ASSERT_TRUE(s21_queue.size() == std_queue.size());
  ASSERT_TRUE(s21_queue.back() == std_queue.back());
  ASSERT_TRUE(s21_queue.front() == std_queue.front());
}

TEST(s21_queue, test5) {
  s21::queue<std::string> s21_queue{"fuck", "your", "ethnicity"};
  std::queue<std::string> std_queue;
  std_queue.push("fuck");
  std_queue.push("your");
  std_queue.push("ethnicity");
  ASSERT_TRUE(s21_queue.size() == std_queue.size());
  ASSERT_TRUE(s21_queue.back() == std_queue.back());
  ASSERT_TRUE(s21_queue.front() == std_queue.front());
}

TEST(s21_queue, test6) {
  s21::queue<std::string> s21_queue_1{"kanye", "west"};
  s21::queue<std::string> s21_queue_2{"kendrick", "lamar"};
  std::queue<std::string> std_queue_1;
  std::queue<std::string> std_queue_2;
  std_queue_1.push("kanye");
  std_queue_1.push("west");
  std_queue_2.push("kendrick");
  std_queue_2.push("lamar");
  s21_queue_1.swap(s21_queue_2);
  std_queue_1.swap(std_queue_2);
  ASSERT_TRUE(s21_queue_1.size() == std_queue_1.size());
  ASSERT_TRUE(s21_queue_1.back() == std_queue_1.back());
  ASSERT_TRUE(s21_queue_1.front() == std_queue_1.front());
  ASSERT_TRUE(s21_queue_2.size() == std_queue_2.size());
  ASSERT_TRUE(s21_queue_2.back() == std_queue_2.back());
  ASSERT_TRUE(s21_queue_2.front() == std_queue_2.front());
}

TEST(s21_queue_copy, test7) {
  s21::queue<char> s21_queue{'f', 'u', 'c', 'k'};
  std::queue<char> std_queue;
  std_queue.push('f');
  std_queue.push('u');
  std_queue.push('c');
  std_queue.push('k');
  s21::queue<char> s21_queue_copy(s21_queue);
  std::queue<char> std_queue_copy(std_queue);
  ASSERT_TRUE(s21_queue.size() == std_queue.size());
  ASSERT_TRUE(s21_queue.back() == std_queue.back());
  ASSERT_TRUE(s21_queue.front() == std_queue.front());
  ASSERT_TRUE(s21_queue_copy.size() == std_queue_copy.size());
  ASSERT_TRUE(s21_queue_copy.front() == std_queue_copy.front());
  ASSERT_TRUE(s21_queue_copy.back() == std_queue_copy.back());
}

TEST(s21_queue, test8) {
  s21::queue<char> s21_queue{'f', 'u', 'c', 'k'};
  std::queue<char> std_queue;
  std_queue.push('f');
  std_queue.push('u');
  std_queue.push('c');
  std_queue.push('k');
  s21::queue<char> s21_queue_move(std::move(s21_queue));
  std::queue<char> std_queue_move(std::move(std_queue));
  ASSERT_TRUE(s21_queue_move.size() == std_queue_move.size());
  ASSERT_TRUE(s21_queue_move.front() == std_queue_move.front());
  ASSERT_TRUE(s21_queue_move.back() == std_queue_move.back());
}

TEST(s21_queue, test9) {
  s21::queue<char> s21_queue;
  s21_queue.emplace_back('a');
  s21_queue.emplace_back('a', 'b', 'c');
  s21_queue.emplace_back('f', 'u', 'c', 'k', 'k');
  ASSERT_TRUE(s21_queue.size() == 9);
}

// <------------------------ STACK TESTS ------------------------>
template <class T>
bool equal_stacks(s21::stack<T> s21_stack, std::stack<T> std_stack) {
  bool result = true;
  if (s21_stack.size() != std_stack.size()) {
    result = false;
  } else {
    for (size_t i = 0; i < s21_stack.size(); i++) {
      if (s21_stack.top() != s21_stack.top()) result = false;
      s21_stack.pop();
      std_stack.pop();
    }
  }
  return result;
}

TEST(s21_stack, test1) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_TRUE(equal_stacks(s21_stack, std_stack));

  s21::stack<double> s21_stack_double;
  std::stack<double> std_stack_double;
  EXPECT_TRUE(equal_stacks(s21_stack_double, std_stack_double));

  s21::stack<char> s21_stack_char;
  std::stack<char> std_stack_char;
  EXPECT_TRUE(equal_stacks(s21_stack_char, std_stack_char));

  s21::stack<std::string> s21_stack_string;
  std::stack<std::string> std_stack_string;
  EXPECT_TRUE(equal_stacks(s21_stack_string, std_stack_string));

  s21::stack<std::pair<int, double>> s21_stack_pair;
  std::stack<std::pair<int, double>> std_stack_pair;
  EXPECT_TRUE(equal_stacks(s21_stack_pair, std_stack_pair));
}

TEST(s21_stack, test2) {
  s21::stack<int> s21_stack{18, 3, 1993};
  std::stack<int> std_stack;
  std_stack.push(18);
  std_stack.push(3);
  std_stack.push(1993);
  EXPECT_TRUE(equal_stacks(s21_stack, std_stack));
}

TEST(s21_stack, test3) {
  s21::stack<double> s21_stack{4.0, 20.0, 420.0};
  std::stack<double> std_stack;
  std_stack.push(4.0);
  std_stack.push(20.0);
  std_stack.push(420.0);
  EXPECT_TRUE(equal_stacks(s21_stack, std_stack));
}

TEST(s21_stack, test4) {
  s21::stack<char> s21_stack{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::stack<char> std_stack;
  std_stack.push('l');
  std_stack.push('a');
  std_stack.push('r');
  std_stack.push('o');
  std_stack.push('n');
  std_stack.push('d');
  std_stack.push('a');
  EXPECT_TRUE(equal_stacks(s21_stack, std_stack));
}

TEST(s21_stack, test5) {
  s21::stack<char> s21_stack{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::stack<char> std_stack;
  std_stack.push('l');
  std_stack.push('a');
  std_stack.push('r');
  std_stack.push('o');
  std_stack.push('n');
  std_stack.push('d');
  std_stack.push('a');
  s21::stack<char> s21_stack_copy(s21_stack);
  std::stack<char> std_stack_copy(std_stack);
  EXPECT_TRUE(equal_stacks(s21_stack_copy, std_stack_copy));
}

TEST(s21_stack, test6) {
  s21::stack<char> s21_stack{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::stack<char> std_stack;
  std_stack.push('l');
  std_stack.push('a');
  std_stack.push('r');
  std_stack.push('o');
  std_stack.push('n');
  std_stack.push('d');
  std_stack.push('a');
  s21::stack<char> s21_stack_move(std::move(s21_stack));
  std::stack<char> std_stack_move(std::move(std_stack));
  EXPECT_TRUE(equal_stacks(s21_stack_move, std_stack_move));
}

TEST(s21_stack, test7) {
  s21::stack<char> s21_stack{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21::stack<char> s21_stack_swap;
  std::stack<char> std_stack;
  std::stack<char> std_stack_swap;
  std_stack.push('l');
  std_stack.push('a');
  std_stack.push('r');
  std_stack.push('o');
  std_stack.push('n');
  std_stack.push('d');
  std_stack.push('a');
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);
  EXPECT_TRUE(equal_stacks(s21_stack, std_stack));
  EXPECT_TRUE(equal_stacks(s21_stack_swap, std_stack_swap));
}

TEST(s21_stack, test8) {
  s21::stack<int> s21_stack;
  s21_stack.emplace_front(3);
  s21_stack.emplace_front(3, 3, 3);
  s21_stack.emplace_front(3, 3, 3, 3, 3);
  ASSERT_TRUE(s21_stack.size() == 9);
}

// <------------------------ ARRAY TESTS ------------------------>
template <class T, std::size_t N>
bool equal_arr(s21::array<T, N> s21_array, std::array<T, N> std_array) {
  bool result = true;
  if (s21_array.size() != std_array.size()) {
    result = false;
  } else {
    for (size_t i = 0; i < s21_array.size(); i++) {
      if (s21_array[i] != std_array[i]) {
        result = false;
      }
    }
  }
  return result;
}

TEST(s21_array, test1) {
  s21::array<int, 4> s21_array;
  std::array<int, 4> std_array;
  ASSERT_TRUE(s21_array.size() == std_array.size());
  ASSERT_TRUE(s21_array.empty() == std_array.empty());

  s21::array<double, 20> s21_array_2;
  std::array<double, 20> std_array_2;
  ASSERT_TRUE(s21_array_2.size() == std_array_2.size());
  ASSERT_TRUE(s21_array_2.empty() == std_array_2.empty());

  s21::array<char, 420> s21_array_3;
  std::array<char, 420> std_array_3;
  ASSERT_TRUE(s21_array_3.size() == std_array_3.size());
  ASSERT_TRUE(s21_array_3.empty() == std_array_3.empty());
}

TEST(s21_array, test2) {
  s21::array<int, 3> s21_array{4, 20, 420};
  std::array<int, 3> std_array{4, 20, 420};
  ASSERT_TRUE(s21_array.size() == std_array.size());
  ASSERT_TRUE(s21_array.empty() == std_array.empty());
  EXPECT_TRUE(equal_arr(s21_array, std_array));

  s21::array<double, 20> s21_array_2{4.0, 20.0, 420.0};
  std::array<double, 20> std_array_2{4.0, 20.0, 420.0};
  ASSERT_TRUE(s21_array_2.size() == std_array_2.size());
  ASSERT_TRUE(s21_array_2.empty() == std_array_2.empty());
  EXPECT_TRUE(equal_arr(s21_array_2, std_array_2));

  s21::array<char, 420> s21_array_3{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::array<char, 420> std_array_3{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  ASSERT_TRUE(s21_array_3.size() == std_array_3.size());
  ASSERT_TRUE(s21_array_3.empty() == std_array_3.empty());
  EXPECT_TRUE(equal_arr(s21_array_3, std_array_3));

  s21::array<char, 420> s21_array_4{'l', 'a', 's', 'h', 'o', 'n', 'd', 'a'};
  std::array<char, 420> std_array_4{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  ASSERT_FALSE(s21_array_4.size() != std_array_4.size());
  ASSERT_FALSE(s21_array_4.empty() != std_array_4.empty());
  EXPECT_FALSE(equal_arr(s21_array_4, std_array_4));
}

TEST(s21_array, test3) {
  s21::array<int, 3> s21_array{4, 20, 420};
  std::array<int, 3> std_array{4, 20, 420};
  s21::array<int, 3> s21_array_cp(s21_array);
  std::array<int, 3> std_array_cp(std_array);
  ASSERT_TRUE(s21_array.size() == std_array.size());
  ASSERT_TRUE(s21_array.empty() == std_array.empty());
  ASSERT_TRUE(s21_array_cp.size() == std_array_cp.size());
  ASSERT_TRUE(s21_array_cp.empty() == std_array_cp.empty());
  EXPECT_TRUE(equal_arr(s21_array, std_array));
  EXPECT_TRUE(equal_arr(s21_array_cp, std_array_cp));
}

TEST(s21_array, test4) {
  s21::array<int, 3> s21_array{4, 20, 420};
  std::array<int, 3> std_array{4, 20, 420};
  s21::array<int, 3> s21_array_mv(std::move(s21_array));
  std::array<int, 3> std_array_mv(std::move(std_array));
  ASSERT_TRUE(s21_array.size() == std_array.size());
  ASSERT_TRUE(s21_array.empty() == std_array.empty());
  ASSERT_TRUE(s21_array_mv.size() == std_array_mv.size());
  ASSERT_TRUE(s21_array_mv.empty() == std_array_mv.empty());
  EXPECT_TRUE(equal_arr(s21_array, std_array));
  EXPECT_TRUE(equal_arr(s21_array_mv, std_array_mv));
}

TEST(s21_array, test5) {
  s21::array<char, 42> s21_array{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::array<char, 42> std_array{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  ASSERT_TRUE(s21_array.max_size() == std_array.max_size());
  ASSERT_TRUE(s21_array.front() == std_array.front());
  ASSERT_TRUE(s21_array.back() == std_array.back());
  ASSERT_TRUE(s21_array.at(0) == std_array.at(0));
  ASSERT_TRUE(s21_array.at(3) == std_array.at(3));
  ASSERT_TRUE(s21_array.at(6) == std_array.at(6));
  ASSERT_TRUE(s21_array[0] == std_array[0]);
  ASSERT_TRUE(s21_array[3] == std_array[3]);
  ASSERT_TRUE(s21_array[6] == std_array[6]);
}

TEST(s21_array, test6) {
  s21::array<char, 7> s21_array{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::array<char, 7> std_array{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21::array<char, 7>::const_iterator s21_array_it_start = s21_array.begin();
  std::array<char, 7>::const_iterator std_array_it_start = std_array.begin();
  ASSERT_TRUE(*s21_array_it_start == *std_array_it_start);
}

TEST(s21_array, test7) {
  s21::array<int, 3> s21_array{4, 20, 420};
  std::array<int, 3> std_array{4, 20, 420};
  s21::array<int, 3> s21_array_swap;
  std::array<int, 3> std_array_swap;
  s21_array.swap(s21_array_swap);
  std_array.swap(std_array_swap);
  EXPECT_TRUE(equal_arr(s21_array_swap, std_array_swap));
}

TEST(s21_array, test8) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  s21_array.fill(420);
  std_array.fill(420);
  EXPECT_TRUE(equal_arr(s21_array, std_array));
}

TEST(s21_array, test9) {
  s21::array<int, 3> s21_array{420};
  std::array<int, 3> std_array{420};
  s21::array<int, 3>::const_iterator s21_array_it_data = s21_array.data();
  std::array<int, 3>::const_iterator std_array_it_data = std_array.data();
  ASSERT_TRUE(*s21_array_it_data == *std_array_it_data);
}

// <------------------------ LIST TESTS ------------------------>
template <class T>
bool equal_list(s21::list<T> s21_list, std::list<T> std_list) {
  typename s21::list<T>::iterator s21_it = s21_list.begin();
  typename std::list<T>::iterator std_it = std_list.begin();
  bool result = true;
  if (s21_list.size() != std_list.size()) result = false;
  while (std_it != std_list.end()) {
    if (*s21_it != *std_it) {
      result = false;
    }
    ++s21_it;
    ++std_it;
  }
  return result;
}

TEST(s21_list, test1) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  EXPECT_TRUE(equal_list(s21_list, std_list));

  s21::list<int> s21_list_1(5);
  std::list<int> std_list_1(5);
  ASSERT_TRUE(s21_list_1.size() == std_list_1.size());
  ASSERT_TRUE(s21_list_1.empty() == std_list_1.empty());
  EXPECT_TRUE(equal_list(s21_list_1, std_list_1));

  s21::list<double> s21_list1;
  std::list<double> std_list1;
  ASSERT_TRUE(s21_list1.size() == std_list1.size());
  ASSERT_TRUE(s21_list1.max_size() == std_list1.max_size());
  ASSERT_TRUE(s21_list1.empty() == std_list1.empty());
  EXPECT_TRUE(equal_list(s21_list1, std_list1));

  s21::list<char> s21_list2;
  std::list<char> std_list2;
  ASSERT_TRUE(s21_list2.size() == std_list2.size());
  ASSERT_TRUE(s21_list2.max_size() == std_list2.max_size());
  ASSERT_TRUE(s21_list2.empty() == std_list2.empty());
  EXPECT_TRUE(equal_list(s21_list2, std_list2));

  s21::list<std::string> s21_list3;
  std::list<std::string> std_list3;
  ASSERT_TRUE(s21_list3.size() == std_list3.size());
  ASSERT_TRUE(s21_list3.max_size() == std_list3.max_size());
  ASSERT_TRUE(s21_list3.empty() == std_list3.empty());
  EXPECT_TRUE(equal_list(s21_list3, std_list3));

  s21::list<std::pair<double, int>> s21_list4;
  std::list<std::pair<double, int>> std_list4;
  ASSERT_TRUE(s21_list4.size() == std_list4.size());
  ASSERT_TRUE(s21_list4.empty() == std_list4.empty());
  EXPECT_TRUE(equal_list(s21_list4, std_list4));
}

TEST(s21_list, test2) {
  s21::list<int> s21_list_1{4, 20, 420};
  std::list<int> std_list_1{4, 20, 420};
  ASSERT_TRUE(s21_list_1.size() == std_list_1.size());
  ASSERT_TRUE(s21_list_1.empty() == std_list_1.empty());
  ASSERT_TRUE(s21_list_1.back() == std_list_1.back());
  ASSERT_TRUE(s21_list_1.front() == std_list_1.front());
  EXPECT_TRUE(equal_list(s21_list_1, std_list_1));

  s21::list<double> s21_list_2{4.0, 20.0, 420.0};
  std::list<double> std_list_2{4.0, 20.0, 420.0};
  ASSERT_TRUE(s21_list_2.size() == std_list_2.size());
  ASSERT_TRUE(s21_list_2.empty() == std_list_2.empty());
  ASSERT_TRUE(s21_list_2.back() == std_list_2.back());
  ASSERT_TRUE(s21_list_2.front() == std_list_2.front());
  EXPECT_TRUE(equal_list(s21_list_2, std_list_2));

  s21::list<char> s21_list_3{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::list<char> std_list_3{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  ASSERT_TRUE(s21_list_3.size() == std_list_3.size());
  ASSERT_TRUE(s21_list_3.empty() == std_list_3.empty());
  ASSERT_TRUE(s21_list_3.back() == std_list_3.back());
  ASSERT_TRUE(s21_list_3.front() == std_list_3.front());
  EXPECT_TRUE(equal_list(s21_list_3, std_list_3));

  s21::list<std::string> s21_list_4{
      "Feelin on a girls ass with a troubled past"};
  std::list<std::string> std_list_4{
      "Feelin on a girls ass with a troubled past"};
  ASSERT_TRUE(s21_list_4.size() == std_list_4.size());
  ASSERT_TRUE(s21_list_4.empty() == std_list_4.empty());
  ASSERT_TRUE(s21_list_4.back() == std_list_4.back());
  ASSERT_TRUE(s21_list_4.front() == std_list_4.front());
  EXPECT_TRUE(equal_list(s21_list_4, std_list_4));

  s21::list<std::pair<double, int>> s21_list_5{{420.0, 4}, {4, 20}};
  std::list<std::pair<double, int>> std_list_5{{420.0, 4}, {4, 20}};
  ASSERT_TRUE(s21_list_5.size() == std_list_5.size());
  ASSERT_TRUE(s21_list_5.empty() == std_list_5.empty());
  ASSERT_TRUE(s21_list_5.back() == std_list_5.back());
  ASSERT_TRUE(s21_list_5.front() == std_list_5.front());
  EXPECT_TRUE(equal_list(s21_list_5, std_list_5));
}

TEST(s21_list, test3) {
  s21::list<double> s21_list{4.0, 20.0, 420.0};
  s21::list<double> s21_list_2 = s21_list;
  std::list<double> std_list{4.0, 20.0, 420.0};
  std::list<double> std_list_2 = std_list;
  ASSERT_TRUE(s21_list_2.size() == std_list_2.size());
  ASSERT_TRUE(s21_list_2.empty() == std_list_2.empty());
  ASSERT_TRUE(s21_list_2.back() == std_list_2.back());
  ASSERT_TRUE(s21_list_2.front() == std_list_2.front());
  EXPECT_TRUE(equal_list(s21_list_2, std_list_2));
}

TEST(s21_list, test4) {
  s21::list<int> s21_list{4, 20, 420};
  std::list<int> std_list{4, 20, 420};
  s21::list<int> s21_list_2(std::move(s21_list));
  std::list<int> std_list_2(std::move(std_list));
  ASSERT_TRUE(s21_list_2.size() == std_list_2.size());
  ASSERT_TRUE(s21_list_2.empty() == std_list_2.empty());
  ASSERT_TRUE(s21_list_2.back() == std_list_2.back());
  ASSERT_TRUE(s21_list_2.front() == std_list_2.front());
  EXPECT_TRUE(equal_list(s21_list_2, std_list_2));
}

TEST(s21_list, test5) {
  s21::list<char> s21_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::list<char> std_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21_list.clear();
  std_list.clear();
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test6) {
  s21::list<std::string> s21_list{"laronda"};
  std::list<std::string> std_list{"laronda"};
  ;
  s21::list<std::string>::iterator s21_it = s21_list.begin();
  std::list<std::string>::iterator std_it = std_list.begin();

  s21_list.insert(s21_it, "keylight");
  std_list.insert(std_it, "keylight");
  s21_list.insert(s21_it, "flossie");
  std_list.insert(std_it, "flossie");
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test7) {
  s21::list<char> s21_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::list<char> std_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21_list.pop_front();
  std_list.pop_front();
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test8) {
  s21::list<char> s21_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21::list<char> s21_list2;
  std::list<char> std_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::list<char> std_list2;
  s21_list.swap(s21_list2);
  std_list.swap(std_list2);
  ASSERT_TRUE(s21_list2.size() == std_list2.size());
  ASSERT_TRUE(s21_list2.empty() == std_list2.empty());
  ASSERT_TRUE(s21_list2.back() == std_list2.back());
  ASSERT_TRUE(s21_list2.front() == std_list2.front());
  EXPECT_TRUE(equal_list(s21_list2, std_list2));
}

TEST(s21_list, test9) {
  s21::list<char> s21_list{'l', 'a', 'r', 'o', 'n', 'd', 'a', 'g'};
  std::list<char> std_list{'l', 'a', 'r', 'o', 'n', 'd', 'a', 'g'};
  s21_list.reverse();
  std_list.reverse();
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  s21::list<char>::iterator s21_it = s21_list.begin();
  std::list<char>::iterator std_it = std_list.begin();
  while (s21_it != s21_list.end()) {
    ASSERT_TRUE(*s21_it == *std_it);
    ++s21_it;
    ++std_it;
  }
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test10) {
  s21::list<char> s21_list{'l', 'a', 'a', 'a', 'a', 'r', 'o',
                           'o', 'o', 'n', 'd', 'o', 'a', 'g'};
  std::list<char> std_list{'l', 'a', 'a', 'a', 'a', 'r', 'o',
                           'o', 'o', 'n', 'd', 'o', 'a', 'g'};
  s21_list.unique();
  std_list.unique();
  s21::list<char>::iterator s21_it = s21_list.begin();
  std::list<char>::iterator std_it = std_list.begin();
  while (s21_it != s21_list.end()) {
    ASSERT_TRUE(*s21_it == *std_it);
    ++s21_it;
    ++std_it;
  }
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test11) {
  s21::list<int> s21_list{420, 20, 2, 4, 840};
  std::list<int> std_list{420, 20, 2, 4, 840};
  s21_list.sort();
  std_list.sort();
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test12) {
  s21::list<char> s21_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21::list<char> s21_splice{'l', 'a', 's', 'h', 'o', 'n', 'd', 'a'};
  std::list<char> std_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::list<char> std_splice{'l', 'a', 's', 'h', 'o', 'n', 'd', 'a'};
  s21::list<char>::const_iterator s21_const_it = s21_list.cbegin();
  std::list<char>::const_iterator std_const_it = std_list.cbegin();
  s21_list.splice(s21_const_it, s21_splice);
  std_list.splice(std_const_it, std_splice);
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test13) {
  s21::list<char> s21_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  s21::list<char> s21_merge{'l', 'a', 's', 'h', 'o', 'n', 'd', 'a'};
  std::list<char> std_list{'l', 'a', 'r', 'o', 'n', 'd', 'a'};
  std::list<char> std_merge{'l', 'a', 's', 'h', 'o', 'n', 'd', 'a'};
  s21_list.merge(s21_merge);
  std_list.merge(std_merge);
  s21_list.sort();
  std_list.sort();
  ASSERT_TRUE(s21_list.size() == std_list.size());
  ASSERT_TRUE(s21_list.empty() == std_list.empty());
  ASSERT_TRUE(s21_list.back() == std_list.back());
  ASSERT_TRUE(s21_list.front() == std_list.front());
  EXPECT_TRUE(equal_list(s21_list, std_list));
}

TEST(s21_list, test14) {
  s21::list<int> s21_list{1, 2, 3, 5, 6, 9, 50, 99};
  s21_list.emplace_back(33);
  s21_list.emplace_back(44, 55, 66);
  s21_list.emplace_back(44, 55, 66, 77, 88);

  s21_list.emplace_front(0);
  s21_list.emplace_front(12, 13, 14);
  s21_list.emplace_front(15, 16, 17, 18, 19);

  s21::list<int>::const_iterator s21_it = s21_list.cbegin();
  s21_list.emplace(s21_it, 4);
  s21_list.emplace(s21_it, 4, 5, 8);
  s21_list.emplace(s21_it, 4, 5, 6, 7, 8);
  ASSERT_TRUE(s21_list.size() == 35);
}

//<------------------------ SET TESTS ------------------------>
TEST(s21_set, test1) {
  s21::set<int> s21_set_int;
  std::set<int> std_set_int;
  ASSERT_TRUE(s21_set_int.size() == std_set_int.size());
  ASSERT_TRUE(s21_set_int.empty() == std_set_int.empty());

  s21::set<char> s21_set_char;
  std::set<char> std_set_char;
  ASSERT_TRUE(s21_set_char.size() == std_set_char.size());
  ASSERT_TRUE(s21_set_char.empty() == std_set_char.empty());

  s21::set<double> s21_set_double;
  std::set<double> std_set_double;
  ASSERT_TRUE(s21_set_double.size() == std_set_double.size());
  ASSERT_TRUE(s21_set_double.empty() == std_set_double.empty());

  s21::set<int> s21_set_int1({4, 20, 420});
  std::set<int> std_set_int1({4, 20, 420});
  ;
  ASSERT_TRUE(s21_set_int1.size() == std_set_int1.size());

  s21::set<int> s21_set_int2(s21_set_int1);
  std::set<int> std_set_int2(std_set_int1);
  ;
  s21::set<int> s21_set_int3(std::move(s21_set_int2));
  ASSERT_TRUE(s21_set_int1.size() == std_set_int1.size());
}

TEST(s21_set, test2) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(0);
  s21_set.insert(0);
  s21_set.insert(-999);
  s21_set.insert(999);
  s21_set.clear();
  ASSERT_TRUE(s21_set.empty());
}

TEST(s21_set, test3) {
  s21::set<char> s21_set;
  s21_set.insert('l');
  s21_set.insert('a');
  s21_set.insert('r');
  s21_set.insert('o');
  s21_set.insert('n');
  s21_set.insert('d');
  s21_set.insert('a');
  ASSERT_TRUE(s21_set.contains('l'));
  ASSERT_TRUE(s21_set.contains('o'));
  ASSERT_TRUE(s21_set.contains('a'));

  s21::set<char> s21_set_swap;
  s21_set_swap.insert('k');
  s21_set_swap.insert('e');
  s21_set_swap.insert('i');
  s21_set_swap.insert('l');
  s21_set_swap.insert('i');
  s21_set_swap.insert('g');
  s21_set_swap.insert('t');
  ASSERT_TRUE(s21_set_swap.contains('k'));
  ASSERT_TRUE(s21_set_swap.contains('i'));
  ASSERT_TRUE(s21_set_swap.contains('t'));

  s21_set.swap(s21_set_swap);
  ASSERT_TRUE(s21_set.contains('k'));
  ASSERT_TRUE(s21_set.contains('i'));
  ASSERT_TRUE(s21_set.contains('t'));
}

TEST(s21_set, test4) {
  s21::set<std::string> s21_set{"laronda", "Crimea", "Paradise", "Cat"};
  s21::set<std::string> s21_set2{"keilight", "laronda", "Crimea", "Boobs"};
  s21::set<std::string> s21_set_res;
  s21_set_res.merge(s21_set);
  s21_set_res.merge(s21_set2);
  ASSERT_EQ(s21_set_res.size(), 6);
}

TEST(s21_set, test7) {
  s21::set<int> s21_set{0, 44, -45, 33, 999, 2};
  s21::set<int> s21_set2{-3, -2, 0, 33, 99, 88, 23, 44};
  s21::set<int> s21_set_res;
  s21_set_res.merge(s21_set);
  s21_set_res.merge(s21_set2);
  ASSERT_EQ(s21_set_res.size(), 11);
}

TEST(s21_set, test5) {
  s21::set<std::string> s21_set;
  s21_set.emplace("gringo");
  s21_set.emplace("stay", "hard", "motherfucker");
  s21_set.emplace("stay", "hard", "motherfucker", "gringo", "beach");
  ASSERT_TRUE(s21_set.contains("stay"));
  ASSERT_TRUE(s21_set.contains("hard"));
  ASSERT_TRUE(s21_set.contains("motherfucker"));
}

TEST(s21_set, test6) {
  int val = 0;
  s21::set<int> s21_set({0, 99, 103, 50, 1});
  std::set<int> std_set({0, 99, 103, 50, 1});
  s21_set.erase(s21_set.find(val));
  std_set.erase(std_set.find(val));
  val = 103;
  s21_set.erase(s21_set.find(val));
  std_set.erase(std_set.find(val));
  val = 1;
  s21_set.erase(s21_set.find(val));
  std_set.erase(std_set.find(val));
  val = 99;
  s21_set.erase(s21_set.find(val));
  std_set.erase(std_set.find(val));
  val = 50;
  s21_set.erase(s21_set.find(val));
  std_set.erase(std_set.find(val));
  ASSERT_EQ(s21_set.size(), std_set.size());
}
// <------------------------ MULTISET TESTS ------------------->
TEST(s21_multiset, test1) {
  s21::multiset<int> s21_multiset_int;
  std::multiset<int> std_multiset_int;
  ASSERT_TRUE(s21_multiset_int.size() == std_multiset_int.size());
  ASSERT_TRUE(s21_multiset_int.empty() == std_multiset_int.empty());

  s21::multiset<char> s21_multiset_char;
  std::multiset<char> std_multiset_char;
  ASSERT_TRUE(s21_multiset_char.size() == std_multiset_char.size());
  ASSERT_TRUE(s21_multiset_char.empty() == std_multiset_char.empty());

  s21::multiset<double> s21_multiset_double;
  std::multiset<double> std_multiset_double;
  ASSERT_TRUE(s21_multiset_double.size() == std_multiset_double.size());
  ASSERT_TRUE(s21_multiset_double.empty() == std_multiset_double.empty());

  s21::multiset<int> s21_multiset_int1({4, 20, 420});
  std::multiset<int> std_multiset_int1({4, 20, 420});
  ASSERT_TRUE(s21_multiset_int1.size() == std_multiset_int1.size());

  s21::multiset<int> s21_multiset_int2(s21_multiset_int1);
  std::multiset<int> std_multiset_int2(std_multiset_int1);
  ;
  s21::multiset<int> s21_multiset_int3(std::move(s21_multiset_int2));
  ASSERT_TRUE(s21_multiset_int1.size() == std_multiset_int1.size());
}

TEST(s21_multiset, test2) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(1);
  s21_multiset.insert(0);
  s21_multiset.insert(0);
  s21_multiset.insert(-999);
  s21_multiset.insert(999);
  s21_multiset.insert(-999999);
  s21_multiset.clear();
  ASSERT_TRUE(s21_multiset.empty());
}

TEST(s21_multiset, test3) {
  s21::multiset<char> s21_multiset;
  s21_multiset.insert('l');
  s21_multiset.insert('a');
  s21_multiset.insert('r');
  s21_multiset.insert('o');
  s21_multiset.insert('n');
  s21_multiset.insert('r');
  s21_multiset.insert('o');
  s21_multiset.insert('n');
  s21_multiset.insert('d');
  s21_multiset.insert('a');
  ASSERT_TRUE(s21_multiset.contains('l'));
  ASSERT_TRUE(s21_multiset.contains('o'));
  ASSERT_TRUE(s21_multiset.contains('a'));

  s21::multiset<char> s21_multiset_swap;
  s21_multiset_swap.insert('k');
  s21_multiset_swap.insert('e');
  s21_multiset_swap.insert('i');
  s21_multiset_swap.insert('l');
  s21_multiset_swap.insert('i');
  s21_multiset_swap.insert('g');
  s21_multiset_swap.insert('t');
  ASSERT_TRUE(s21_multiset_swap.contains('k'));
  ASSERT_TRUE(s21_multiset_swap.contains('i'));
  ASSERT_TRUE(s21_multiset_swap.contains('t'));

  s21_multiset.swap(s21_multiset_swap);
  ASSERT_TRUE(s21_multiset.contains('k'));
  ASSERT_TRUE(s21_multiset.contains('i'));
  ASSERT_TRUE(s21_multiset.contains('t'));
}

TEST(s21_multiset, test4) {
  s21::multiset<std::string> s21_multiset{"laronda", "Crimea", "Paradise",
                                          "Cat"};
  s21::multiset<std::string> s21_multiset2{"keilight", "laronda", "Crimea",
                                           "Boobs"};
  s21::multiset<std::string> s21_multiset_res;
  s21_multiset_res.merge(s21_multiset);
  s21_multiset_res.merge(s21_multiset2);
  ASSERT_EQ(s21_multiset_res.size(), 8);
}

TEST(s21_multiset, tes5) {
  s21::multiset<int> s21_multiset{0, 44, -45, 33, 999, 2, 5, 4, 6, 7};
  s21::multiset<int> s21_multiset2{-3, -2, 0, 33, 99, 88, 1, 2, 4, 23, 44};
  s21::multiset<int> s21_multiset_res;
  s21_multiset_res.merge(s21_multiset);
  s21_multiset_res.merge(s21_multiset2);
  ASSERT_EQ(s21_multiset_res.size(), 21);
}

TEST(s21_multiset, test6) {
  s21::multiset<std::string> s21_multiset;
  s21_multiset.emplace("gringo");
  s21_multiset.emplace("stay", "hard", "motherfucker");
  s21_multiset.emplace("stay", "hard", "motherfucker", "gringo", "beach");
  ASSERT_TRUE(s21_multiset.contains("stay"));
  ASSERT_TRUE(s21_multiset.contains("hard"));
  ASSERT_TRUE(s21_multiset.contains("motherfucker"));
}

TEST(s21_multiset, test7) {
  int val = 0;
  s21::set<int> s21_multiset({0, 99, 103, 0, 50, 1});
  std::set<int> std_multiset({0, 99, 103, 0, 50, 1});
  s21_multiset.find(val);
  s21_multiset.erase(s21_multiset.find(val));
  std_multiset.erase(std_multiset.find(val));
  val = 103;
  s21_multiset.find(val);
  s21_multiset.erase(s21_multiset.find(val));
  std_multiset.erase(std_multiset.find(val));
  val = 1;
  s21_multiset.find(val);
  s21_multiset.erase(s21_multiset.find(val));
  std_multiset.erase(std_multiset.find(val));
  val = 99;
  s21_multiset.find(val);
  s21_multiset.erase(s21_multiset.find(val));
  std_multiset.erase(std_multiset.find(val));
  val = 50;
  s21_multiset.find(val);
  s21_multiset.erase(s21_multiset.find(val));
  std_multiset.erase(std_multiset.find(val));
  ASSERT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(s21_multiset, test8) {
  s21::multiset<int> s21_multiset;
  auto item = s21_multiset.insert(0);
  auto item2 = s21_multiset.insert(-100);
  auto item3 = s21_multiset.insert(100);
  auto item4 = s21_multiset.insert(34);
  auto item5 = s21_multiset.insert(-23);
  auto item6 = s21_multiset.insert(12);
  ASSERT_TRUE(s21_multiset.contains(0));
  ASSERT_TRUE(s21_multiset.contains(-100));
  ASSERT_TRUE(s21_multiset.contains(100));
  s21_multiset.erase(item3);
  s21_multiset.erase(item2);
  s21_multiset.erase(item);
  s21_multiset.erase(item6);
  s21_multiset.erase(item5);
  s21_multiset.erase(item4);
  ASSERT_TRUE(s21_multiset.size() == 0);
}

TEST(s21_multiset, test9) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(420);
  s21_multiset.insert(420);
  s21_multiset.insert(4);
  s21_multiset.insert(20);
  ASSERT_EQ(s21_multiset.count(420), 2);
  s21_multiset.equal_range(4);
  s21_multiset.lower_bound(420);
  s21_multiset.upper_bound(420);
}

// <------------------------ MAP TESTS ------------------------>
std::pair<const int, const char*> cero(0, "0");
std::pair<const int, const char*> uno(1, "1");
std::pair<const int, const char*> dos(2, "2");
std::pair<const int, const char*> tres(3, "3");
std::pair<const int, const char*> cuatro(4, "4");
std::pair<const int, const char*> cinco(5, "5");
std::pair<const int, const char*> seis(6, "6");
std::pair<const int, const char*> siete(7, "7");
std::pair<const int, const char*> ocho(38, "8");
std::pair<const int, const char*> nueve(5, "9");
std::pair<const int, const char*> diez(66, "10");

std::initializer_list<std::pair<const int, const char*>> numbers_list = {
    cero, uno, dos, seis, tres, cuatro, cinco, siete, ocho, nueve, diez};
std::initializer_list<std::pair<const int, const char*>> numbers_list2 = {
    cero, uno,  dos,   tres, cuatro, cinco, seis,
    seis, seis, siete, ocho, nueve,  diez};


TEST(s21_map, test1) {
  s21::map<std::string, int> s21_map;
  std::map<std::string, int> std_map;
  EXPECT_TRUE(s21_map.empty());
  EXPECT_TRUE(std_map.empty());

  s21::map<int, int> s21_map_1;
  std::map<int, int> std_map_1;
  EXPECT_TRUE(s21_map.empty());
  EXPECT_TRUE(std_map.empty());

  s21::map<double, double> s21_map_2;
  std::map<double, double> std_map_2;
  EXPECT_TRUE(s21_map.empty());
  EXPECT_TRUE(std_map.empty());
}

TEST(s21_map, test2) {
  s21::map<const int, const char*> s21_map;
  s21::map<int, int> s21_map2;
  s21::map<std::string, int> s21_map3{
      {"CPU", 10},
      {"GPU", 15},
      {"RAM", 20},
  };
}

TEST(s21_map, test3) {
  s21::map<const int, const char*> s21_map;
  s21::map<const int, const char*> s21_map2(numbers_list);
  s21::map<const int, const char*> s21_map3(s21_map2);
  s21::map<const int, const char*> s21_map4(std::move(s21_map3));

  std::map<const int, const char*> std_map;
  std::map<const int, const char*> std_map2(numbers_list);
  std::map<const int, const char*> std_map3(std_map2);
  std::map<const int, const char*> std_map4(std::move(std_map3));

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map2.size(), std_map2.size());
  EXPECT_EQ(s21_map3.size(), std_map3.size());
}

TEST(s21_map, tes4) {
  s21::map<const int, const char*> s21_map(numbers_list);
  std::map<const int, const char*> std_map(numbers_list);

  s21_map.at(1) = "one";
  std_map.at(1) = "one";
  auto it = numbers_list.begin();
  while (it < numbers_list.end()) {
    EXPECT_EQ(s21_map.at((*it).first), std_map.at((*it).first));
    it += 1;
  }

  s21_map[2] = "two";
  std_map[2] = "two";
  auto it1 = numbers_list.begin();
  while (it1 < numbers_list.end()) {
    EXPECT_EQ(s21_map[(*it1).first], std_map[(*it1).first]);
    it1 += 1;
  }
}

TEST(s21_map, test5) {
  s21::map<const int, const char*> s21_map(numbers_list);
  std::map<const int, const char*> std_map(numbers_list);
  s21_map.clear();
  std_map.clear();
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(s21_map, test6) {
  s21::map<const int, const char*> s21_map(numbers_list);
  std::map<const int, const char*> std_map(numbers_list);

  ASSERT_TRUE(s21_map.contains(0));
  ASSERT_TRUE(s21_map.contains(1));
  ASSERT_TRUE(s21_map.contains(2));
  ASSERT_TRUE(s21_map.contains(3));
  ASSERT_TRUE(s21_map.contains(4));
  ASSERT_TRUE(s21_map.contains(5));
  ASSERT_TRUE(s21_map.contains(6));
  ASSERT_TRUE(s21_map.contains(7));
  ASSERT_TRUE(s21_map.contains(38));
  ASSERT_TRUE(s21_map.contains(66));
}

TEST(s21_map, test7) {
  std::pair<const int, const char*> one(1, "one");
  std::pair<const int, const char*> two(2, "two");
  std::pair<const int, const char*> sixtynine(69, "sixtynine");
  std::pair<const int, const char*> lucky(666, "lucky");

  s21::map<const int, const char*> s21_map(numbers_list);
  std::map<const int, const char*> std_map(numbers_list);

  auto s21_it1 = s21_map.insert(one);
  auto s21_it2 = s21_map.insert(two);
  auto s21_it3 = s21_map.insert(sixtynine);
  auto s21_it4 = s21_map.insert(lucky);

  auto std_it1 = std_map.insert(one);
  auto std_it2 = std_map.insert(two);
  auto std_it3 = std_map.insert(sixtynine);
  auto std_it4 = std_map.insert(lucky);

  EXPECT_EQ(s21_it1.second, std_it1.second);
  EXPECT_EQ(s21_it2.second, std_it2.second);
  EXPECT_EQ(s21_it3.second, std_it3.second);
  EXPECT_EQ(s21_it4.second, std_it4.second);
}

TEST(s21_map, test8) {
  s21::map<int, const char*> s21_map;
  std::map<int, const char*> std_map;

  auto s21_it1 = s21_map.insert_or_assign(1, "one");
  auto s21_it2 = s21_map.insert_or_assign(2, "two");
  auto s21_it3 = s21_map.insert_or_assign(69, "sixtynine");
  auto s21_it4 = s21_map.insert_or_assign(666, "lucky");

  auto std_it1 = std_map.insert_or_assign(1, "one");
  auto std_it2 = std_map.insert_or_assign(2, "two");
  auto std_it3 = std_map.insert_or_assign(69, "sixtynine");
  auto std_it4 = std_map.insert_or_assign(666, "lucky");

  EXPECT_EQ(s21_it1.second, std_it1.second);
  EXPECT_EQ(s21_it2.second, std_it2.second);
  EXPECT_EQ(s21_it3.second, std_it3.second);
  EXPECT_EQ(s21_it4.second, std_it4.second);
}

TEST(s21_map, test9) {
  s21::map<const int, const char*> s21_map;
  s21::map<const int, const char*> swap_map(numbers_list);
  s21_map.swap(swap_map);
  ASSERT_TRUE(s21_map.contains(0));
  ASSERT_TRUE(s21_map.contains(4));
  ASSERT_TRUE(s21_map.contains(66));
  ASSERT_FALSE(s21_map.contains(69));
}

TEST(s21_map, test10) {
  s21::map<const int, const char*> s21_map(numbers_list);
  s21::map<const int, const char*> s21_map_merge;
  std::map<const int, const char*> std_map(numbers_list);
  std::map<const int, const char*> std_map_merge;
  s21_map.merge(s21_map_merge);
  std_map.merge(std_map_merge);
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(s21_map, test11) {
  s21::map<int, int> s21_map;
  s21_map.insert(1, 33);
  s21_map.insert(2, 45);
  s21_map.insert(3, 4);

  s21::map<int, int>::iterator s21_it = s21_map.begin();
  s21_map.erase(s21_it);
  ASSERT_EQ(s21_map.size(), 2);
}

TEST(s21_map, test13) {
  s21::map<int, int> s21_map;
  auto result = s21_map.insert(0, 0);
  ASSERT_TRUE(s21_map.contains(0));
  s21_map.erase(result.first);
  ASSERT_FALSE(s21_map.contains(0));
  s21::map<int, std::string> s21_map1;
  auto result1 = s21_map1.insert(1, "lashonda");
  s21_map1.erase(result1.first);
  ASSERT_EQ(s21_map1.size(), 0);
  s21::map<int, std::string> s21_map2{{1, "lashonda"}};
  result1 = s21_map2.insert(5, "laronda");
  s21_map2.erase(result1.first);
  ASSERT_EQ(s21_map2.size(), 1);
}

TEST(s21_map, test14) {
  s21::map<int, int> s21_map1;
  s21::map<int, int> s21_map2;
  s21::map<int, int> s21_map3;

  s21_map1[69] = 3;
  s21_map1[96] = 3;
  s21_map1[67] = 3;

  s21_map2[69] = 1;
  s21_map2[66] = 2;
  s21_map2[95] = 4;

  s21_map3[69] = 3;
  s21_map3[96] = 3;
  s21_map3[67] = 3;

  s21_map1.merge(s21_map2);
  s21_map2.merge(s21_map3);
  ASSERT_EQ(s21_map2.size(), 3);
}

TEST(s21_map, test15) {
  s21::map<int, int> s21_map1;
  s21_map1.insert_or_assign(0, 0);
  s21_map1.insert_or_assign(1, 1);
  s21_map1.insert_or_assign(5, 5);
  s21_map1.insert_or_assign(50, 50);
  s21_map1.insert_or_assign(99, 99);
  s21_map1.insert_or_assign(99, 99);
  s21_map1.insert_or_assign(99, 99);
  s21_map1.insert_or_assign(-1, -1);
  s21_map1.insert_or_assign(-20, -20);
  s21_map1.insert_or_assign(-50, -50);
  s21_map1.insert_or_assign(-50, -50);
  s21_map1.insert_or_assign(-50, -50);
  s21_map1.insert_or_assign(-99, -99);
  ASSERT_TRUE(s21_map1.size() == 9);

  s21::map<int, int> s21_map;
  auto s21_it = s21_map.begin();
  s21_map.erase(s21_it);
  ASSERT_TRUE(s21_map.size() == 0);
}

TEST(s21_map, test16) {
  s21::map<int, int> s21_map;
  s21_map[33] = 67;
  s21_map[4] = 7;
  s21_map[1] = 420;
  s21_map.insert_or_assign(3, 18);
  s21_map.insert_or_assign(500, 56);
  s21_map.insert_or_assign(0, 0);
}

TEST(s21_map, test17) {
  s21::map<int, int> s21_map;
  s21_map.emplace(std::make_pair(1, 1));
  s21_map.emplace(std::make_pair(2, 2), std::make_pair(3, 3));
  s21_map.emplace(std::make_pair(4, 4), std::make_pair(5, 5),
                  std::make_pair(6, 6));
  ASSERT_EQ(s21_map.size(), 6);
}

// <------------------------ VECTOR TESTS ------------------------>
bool is_double_eq(double a, double b) {
  double epsilon = 1e-6;
  if (fabs(a - b) > epsilon) {
    return false;
  }
  return true;
}

template <typename T>
bool is_vectors_eq(s21::vector<T>& a, std::vector<T>& b) {
  if ((a.size() != b.size()) || (a.capacity() != b.capacity())) {
    // std::cout << "Size or capacity are not equal" << std::endl;
    return false;
  }
  for (size_t i = 0; i != a.size(); i++) {
    if (!is_double_eq(a.at(i), b.at(i))) {
      // std::cout << "Different values at " << i << " position" << std::endl;
      // std::cout << "value in THIS array ==== " << a.at(i) << std::endl;
      // std::cout << "value in OTHER array ==== " << b.at(i) << std::endl;
      return false;
    }
  }
  return true;
}

//---------------------------------Constructors_and_Destructor----------------------
// basic constructor
TEST(ConstructorTest, BasicMatrix) {
  s21::vector<int> a;
  std::vector<int> b;

  EXPECT_EQ(is_vectors_eq(a, b), true);
}

// constructor with parametered size
TEST(ConstructorTest, ParameteredTrue) {
  s21::vector<int> a(5);
  std::vector<int> b(5);
  EXPECT_EQ(is_vectors_eq(a, b), true);
}

TEST(ConstructorTest, ParameteredFalse) {
  s21::vector<int> a(4);
  std::vector<int> b(5);
  EXPECT_EQ(is_vectors_eq(a, b), false);
}

TEST(ConstructorTest, ParameteredNull) {
  s21::vector<int> a(0);
  std::vector<int> b(0);
  EXPECT_EQ(is_vectors_eq(a, b), true);
}

// initialized constructor
TEST(ConstructorTest, InitializedTrue) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {1, 2, 3, 4, 5};
  EXPECT_EQ(is_vectors_eq(a, b), true);
}

TEST(ConstructorTest, InitializedFalse) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> std = {1, 2, 3, 4, 6};
  EXPECT_EQ(is_vectors_eq(a, std), false);
}

// copy
TEST(CopyTest, Copy) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> a2(a);

  std::vector<int> b = {1, 2, 3, 4, 5};
  std::vector<int> b2(b);

  EXPECT_EQ(is_vectors_eq(a2, b2), true);
  EXPECT_EQ(is_vectors_eq(a2, b), true);
}

// move
TEST(MoveTest, Move) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> a2(std::move(a));

  std::vector<int> b = {1, 2, 3, 4, 5};
  std::vector<int> b2(std::move(b));

  std::vector<int> empty;

  EXPECT_EQ(is_vectors_eq(a2, b2), true);
  EXPECT_EQ(is_vectors_eq(a, empty), true);
  EXPECT_EQ(is_vectors_eq(a, b), true);
}

//---------------------------------Vector_Element_Access----------------------------------------
// at
TEST(AtTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.at(0), b.at(0));
  EXPECT_EQ(a.at(1), b.at(1));
  EXPECT_EQ(a.at(2), b.at(2));
  EXPECT_EQ(a.at(3), b.at(3));
  EXPECT_EQ(a.at(4), b.at(4));
}

// operator[]
TEST(OperatorBracketsTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.operator[](0), b.operator[](0));
  EXPECT_EQ(a.operator[](1), b.operator[](1));
  EXPECT_EQ(a.operator[](2), b.operator[](2));
  EXPECT_EQ(a.operator[](3), b.operator[](3));
  EXPECT_EQ(a.operator[](4), b.operator[](4));
}

// front
TEST(FrontTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {1, 2, 3, 4, 5};

  s21::vector<int> c = {56, 2, 3, 4, 5};
  std::vector<int> d = {56, 2};

  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(c.front(), d.front());
}

// back
TEST(BackTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {1, 2, 3, 4, 5};

  s21::vector<int> c = {56, 2, 3, 4, 5};
  std::vector<int> d = {56, 5};

  EXPECT_EQ(a.back(), b.back());
  EXPECT_EQ(c.back(), d.back());
}

// data
TEST(DataTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {9, 8, 7, 6, 5};

  s21::vector<int> c = {1, 2, 3, 4, 5};
  std::vector<int> d = {9, 8, 7, 6, 5};

  EXPECT_EQ(*a.data(), *c.data());
  EXPECT_EQ(*b.data(), *d.data());
}
//---------------------------------Vector_Iterators----------------------------------------
// iterator begin
TEST(IteratorBeginTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {9, 8, 7, 6, 5};

  s21::vector<int> c = {1, 2, 3, 4, 5};
  std::vector<int> d = {9, 8, 7, 6, 5};

  EXPECT_EQ(*a.begin(), *c.begin());
  EXPECT_EQ(*b.begin(), *d.begin());
}

//---------------------------------Vector_Capacity----------------------------------------
// empty
TEST(EmptyTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b;

  std::vector<int> a1 = {1, 2, 3, 4, 5};
  std::vector<int> b1;

  EXPECT_EQ(a.empty(), a1.empty());
  EXPECT_EQ(b.empty(), b1.empty());
}

// size
TEST(SizeTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b;
  s21::vector<int> c(10);

  std::vector<int> a1 = {1, 2, 3, 4, 5};
  std::vector<int> b1;
  std::vector<int> c1(10);

  EXPECT_EQ(a.size(), a1.size());
  EXPECT_EQ(b.size(), b1.size());
  EXPECT_EQ(c.size(), c1.size());
}

// max size
TEST(MaxSizeTest, Case) {
  s21::vector<int> a;
  std::vector<int> b;
  EXPECT_EQ(a.max_size(), b.max_size());

  s21::vector<char> c;
  std::vector<char> d;
  EXPECT_EQ(c.max_size(), d.max_size());
}

// reserve
TEST(ReserveTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> a1 = {1, 2, 3, 4, 5};

  a.reserve(10);
  a1.reserve(10);

  EXPECT_EQ(is_vectors_eq(a, a1), true);
}

// capacity
TEST(CapacityTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> a1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(a.capacity(), a1.capacity());

  a.push_back(25);
  a1.push_back(10);
  EXPECT_EQ(a.capacity(), a1.capacity());
}

// shrink to fit
TEST(ShrinkToFitTest, Case) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> a1 = {1, 2, 3, 4, 5};

  a.pop_back();
  a1.pop_back();
  EXPECT_EQ(a.capacity(), a1.capacity());

  a.shrink_to_fit();
  a1.shrink_to_fit();
  EXPECT_EQ(a.capacity(), a1.capacity());
}

//---------------------------------Vector_Modifiers----------------------------------------
// clear
TEST(ClearTest, CaseOne) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  std::vector<int> b = {1, 2, 3, 4, 5};

  a.clear();
  b.clear();
  EXPECT_EQ(is_vectors_eq(a, b), true);
}

// insert
TEST(InsertTest, CaseOne) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator check_pointer = a.insert(a.begin() + 1, 56);

  std::vector<int> res = {1, 2, 3, 4, 5};
  std::vector<int>::iterator res_pointer = res.insert(res.begin() + 1, 56);

  EXPECT_EQ(is_vectors_eq(a, res), true);
  EXPECT_EQ(*check_pointer, *res_pointer);
}

TEST(InsertTest, CaseTwo) {
  s21::vector<int> a = {5, 4, 3, 2, 1};
  s21::vector<int>::iterator check_pointer = a.insert(a.end(), 225);

  std::vector<int> res = {5, 4, 3, 2, 1};
  std::vector<int>::iterator res_pointer = res.insert(res.end(), 225);

  EXPECT_EQ(is_vectors_eq(a, res), true);
  EXPECT_EQ(*check_pointer, *res_pointer);
}

TEST(InsertTest, CaseBegin) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator check_pointer = a.insert(a.begin(), 666);

  std::vector<int> res = {1, 2, 3, 4, 5};
  std::vector<int>::iterator res_pointer = res.insert(res.begin(), 666);

  EXPECT_EQ(is_vectors_eq(a, res), true);
  EXPECT_EQ(*check_pointer, *res_pointer);
}

TEST(InsertTest, CaseEnd) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int>::iterator check_pointer = a.insert(a.end(), 666);

  std::vector<int> res = {1, 2, 3, 4, 5};
  std::vector<int>::iterator res_pointer = res.insert(res.end(), 666);

  EXPECT_EQ(is_vectors_eq(a, res), true);
  EXPECT_EQ(*check_pointer, *res_pointer);
}

// erase
TEST(EraseTest, CaseOne) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  a.erase(a.begin() + 1);

  std::vector<int> res = {1, 2, 3, 4, 5};
  res.erase(res.begin() + 1);

  EXPECT_EQ(is_vectors_eq(a, res), true);
}

TEST(EraseTest, CaseBegin) {
  s21::vector<int> a = {9, 3, 56, 89, 6};
  a.erase(a.begin());

  std::vector<int> res = {9, 3, 56, 89, 6};
  res.erase(res.begin());

  EXPECT_EQ(is_vectors_eq(a, res), true);
}

// push_back
TEST(PushBackTest, CaseOne) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  a.push_back(666);

  std::vector<int> res = {1, 2, 3, 4, 5};
  res.push_back(666);

  EXPECT_EQ(is_vectors_eq(a, res), true);
}

// pop_back
TEST(PopBackTest, CaseOne) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  a.pop_back();

  std::vector<int> res = {1, 2, 3, 4, 5};
  res.pop_back();

  EXPECT_EQ(is_vectors_eq(a, res), true);
}

// swap
TEST(SwapTest, CaseOne) {
  s21::vector<int> a = {1, 2, 3, 4, 5};
  s21::vector<int> b;

  std::vector<int> res1 = {1, 2, 3, 4, 5};
  std::vector<int> res2;
  res1.swap(res2);

  a.swap(b);

  EXPECT_EQ(is_vectors_eq(a, res1), true);
  EXPECT_EQ(is_vectors_eq(b, res2), true);
}

TEST(s21_vector, test1) {
  s21::vector<int> s21_vector(1);
  s21_vector.emplace_back(1);
  s21_vector.emplace_back(1, 2, 3);
  s21_vector.emplace_back(1, 2, 3, 4, 5);

  auto s21_it = s21_vector.begin();
  s21_vector.emplace(s21_it, 4);
  s21_vector.emplace(s21_it, 4, 3, 5);
  s21_vector.emplace(s21_it, 10, 33, 45, 88, 69);
  ASSERT_TRUE(s21_vector.size() == 19);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

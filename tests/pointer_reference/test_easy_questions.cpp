#include "pointer_reference/easy_questions.h"
#include "gtest/gtest.h"

TEST(ReverseString, ReverseNonEmptyOddLengthString) {
  easy_questions easy_questions{};
  char str[] = {'a', 'b', 'c', 'd', 'e'};

  easy_questions.reverseString(str);
  EXPECT_STREQ("edcba", str);
}

TEST(ReverseString, ReverseNonEmptyEvenLengthString) {
  easy_questions easy_questions{};
  char str[] = {'a', 'b', 'c', 'd'};

  easy_questions.reverseString(str);
  EXPECT_STREQ("dcba", str);
}

TEST(IncrementTest, IncrementPositive) {
  easy_questions easy_questions{};
  int value = 5;
  easy_questions.increment(&value);
  EXPECT_EQ(value, 6);
}

TEST(FindMinMaxTest, NormalCase) {
  easy_questions easy_questions{};
  int arr[] = {3, 1, 4, 2, 5};
  int min = 0, max = 0;

  easy_questions.findMinMax(arr, 5, &min, &max);

  EXPECT_EQ(min, 1);
  EXPECT_EQ(max, 5);
}

TEST(FindMinMaxTest, SingleElement) {
  easy_questions easy_questions{};
  int arr[] = {10};
  int min = 0, max = 0;

  easy_questions.findMinMax(arr, 1, &min, &max);

  EXPECT_EQ(min, 10);
  EXPECT_EQ(max, 10);
}

TEST(FindMinMaxTest, AllSameElements) {
  easy_questions easy_questions{};
  int arr[] = {7, 7, 7, 7};
  int min = 0, max = 0;

  easy_questions.findMinMax(arr, 4, &min, &max);

  EXPECT_EQ(min, 7);
  EXPECT_EQ(max, 7);
}

TEST(FindMinMaxTest, NegativeElements) {
  easy_questions easy_questions{};
  int arr[] = {-4, -1, -7, -3};
  int min = 0, max = 0;

  easy_questions.findMinMax(arr, 4, &min, &max);

  EXPECT_EQ(min, -7);
  EXPECT_EQ(max, -1);
}

TEST(FindMinMaxTest, TwoElements) {
  easy_questions easy_questions{};
  int arr[] = {100, 50};
  int min = 0, max = 0;

  easy_questions.findMinMax(arr, 2, &min, &max);

  EXPECT_EQ(min, 50);
  EXPECT_EQ(max, 100);
}

TEST(FindMinMaxTest, EmptyArray) {
  easy_questions easy_questions{};
  int min = -1, max = -1;

  easy_questions.findMinMax(nullptr, 0, &min, &max);

  EXPECT_EQ(min, -1);
  EXPECT_EQ(max, -1);
}

TEST(FindMinMaxTest, NullArrayWithSize) {
  easy_questions easy_questions{};
  int min = -1, max = -1;

  easy_questions.findMinMax(nullptr, 5, &min, &max);

  EXPECT_EQ(min, -1);
  EXPECT_EQ(max, -1);
}

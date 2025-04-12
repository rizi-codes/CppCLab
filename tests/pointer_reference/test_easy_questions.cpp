#include "pointer_reference/easy_questions.h"
#include "gtest/gtest.h"

TEST(ReverseString, ReverseNonEmptyOddLengthString) {
  EasyQuestions easyQuestions{};
  char str[] = {'a', 'b', 'c', 'd', 'e'};

  easyQuestions.reverseString(str);
  EXPECT_STREQ("edcba", str);
}

TEST(ReverseString, ReverseNonEmptyEvenLengthString) {
  EasyQuestions easyQuestions{};
  char str[] = {'a', 'b', 'c', 'd'};

  easyQuestions.reverseString(str);
  EXPECT_STREQ("dcba", str);
}

TEST(IncrementTest, IncrementPositive) {
  EasyQuestions easyQuestions{};
  int value = 5;
  easyQuestions.increment(&value);
  EXPECT_EQ(value, 6);
}

TEST(FindMinMaxTest, NormalCase) {
  EasyQuestions easyQuestions{};
  int arr[] = {3, 1, 4, 2, 5};
  int min = 0, max = 0;

  easyQuestions.findMinMax(arr, 5, &min, &max);

  EXPECT_EQ(min, 1);
  EXPECT_EQ(max, 5);
}

TEST(FindMinMaxTest, SingleElement) {
  EasyQuestions easyQuestions{};
  int arr[] = {10};
  int min = 0, max = 0;

  easyQuestions.findMinMax(arr, 1, &min, &max);

  EXPECT_EQ(min, 10);
  EXPECT_EQ(max, 10);
}

TEST(FindMinMaxTest, AllSameElements) {
  EasyQuestions easyQuestions{};
  int arr[] = {7, 7, 7, 7};
  int min = 0, max = 0;

  easyQuestions.findMinMax(arr, 4, &min, &max);

  EXPECT_EQ(min, 7);
  EXPECT_EQ(max, 7);
}

TEST(FindMinMaxTest, NegativeElements) {
  EasyQuestions easyQuestions{};
  int arr[] = {-4, -1, -7, -3};
  int min = 0, max = 0;

  easyQuestions.findMinMax(arr, 4, &min, &max);

  EXPECT_EQ(min, -7);
  EXPECT_EQ(max, -1);
}

TEST(FindMinMaxTest, TwoElements) {
  EasyQuestions easyQuestions{};
  int arr[] = {100, 50};
  int min = 0, max = 0;

  easyQuestions.findMinMax(arr, 2, &min, &max);

  EXPECT_EQ(min, 50);
  EXPECT_EQ(max, 100);
}

TEST(FindMinMaxTest, EmptyArray) {
  EasyQuestions easyQuestions{};
  int min = -1, max = -1;

  easyQuestions.findMinMax(nullptr, 0, &min, &max);

  EXPECT_EQ(min, -1);
  EXPECT_EQ(max, -1);
}

TEST(FindMinMaxTest, NullArrayWithSize) {
  EasyQuestions easyQuestions{};
  int min = -1, max = -1;

  easyQuestions.findMinMax(nullptr, 5, &min, &max);

  EXPECT_EQ(min, -1);
  EXPECT_EQ(max, -1);
}

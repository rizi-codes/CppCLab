#ifndef EASY_QUESTIONS_H
#define EASY_QUESTIONS_H

#include <iostream>

class easy_questions {
public:
  void increment(int *number);
  void findMinMax(const int *arr, size_t size, int *min, int *max);
  void reverseString(char *str);
  void mergeSortedArrays(const int *arr1, size_t size1, const int *arr2,
                         size_t size2, int *result);
  void reverseWords(char *sentence);
};

#endif

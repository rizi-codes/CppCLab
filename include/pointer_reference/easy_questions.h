#ifndef EASY_QUESTIONS_H
#define EASY_QUESTIONS_H

#include <iostream>

class EasyQuestions {
public:
  void increment(int *number);
  void findMinMax(const int *arr, size_t size, int *min, int *max);
  void reverseString(char *str);
};

#endif

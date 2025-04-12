#include "pointer_reference/easy_questions.h"
#include <cstring>

void EasyQuestions::increment(int *number) { *number = *number + 1; }

void EasyQuestions::findMinMax(const int *arr, size_t size, int *min,
                               int *max) {
  if (size == 0 || arr == nullptr) {
    return;
  }

  *min = arr[0];
  *max = arr[0];

  for (size_t index = 1; index < size; index++) {
    int number = arr[index];

    if (number < *min) {
      *min = number;
    }

    if (number > *max) {
      *max = number;
    }
  }
}

void EasyQuestions::reverseString(char *str) {
  if (str == nullptr) {
    return;
  }

  size_t left = 0;
  size_t right = strlen(str);

  if (right == 0) {
    return;
  }

  right--;

  while (left < right) {
    char ch = str[left];
    str[left] = str[right];
    str[right] = ch;
    left++;
    right--;
  }
}

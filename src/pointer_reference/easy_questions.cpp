#include "pointer_reference/easy_questions.h"
#include <cstring>

static void copy_array(const int *source, size_t start, size_t end, int *dest,
                       size_t dest_pos) {
  if (dest == nullptr || end < start) {
    return;
  }

  for (size_t index = start; index < end; index++) {
    dest[dest_pos++] = source[index];
  }
}

static void reverse_substring(char *str, size_t start, size_t end) {
  if (str == nullptr || end <= start) {
    return;
  }

  while (end > start) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    end--;
    start++;
  }
}

void easy_questions::reverseWords(char *sentence) {
  if (sentence == nullptr) {
    return;
  }

  size_t len = strlen(sentence);

  if (len <= 1) {
    return;
  }

  reverse_substring(sentence, 0, len - 1);

  size_t start = 0;

  while (start < len) {
    while (start < len && sentence[start] == ' ') {
      start++;
    }

    if (start >= len) {
      break;
    }

    size_t end = start;
    while (end < len && sentence[end] != ' ') {
      end++;
    }

    reverse_substring(sentence, start, end - 1);
    start = end;
  }
}

void easy_questions::mergeSortedArrays(const int *arr1, size_t size1,
                                       const int *arr2, size_t size2,
                                       int *result) {
  if (arr1 == nullptr || size1 == 0) {
    copy_array(arr2, 0, size2, result, 0);
    return;
  }

  if (arr2 == nullptr || size2 == 0) {
    copy_array(arr1, 0, size1, result, 0);
    return;
  }

  size_t index1 = 0;
  size_t index2 = 0;
  size_t index = 0;

  while (index1 < size1 && index2 < size2) {
    if (arr1[index1] < arr2[index2]) {
      result[index++] = arr1[index1++];
    } else {
      result[index++] = arr2[index2++];
    }
  }

  if (index1 < size1) {
    copy_array(arr1, index1, size1, result, index);
  }

  if (index2 < size2) {
    copy_array(arr2, index2, size2, result, index);
  }
}

void easy_questions::increment(int *number) { *number = *number + 1; }

void easy_questions::findMinMax(const int *arr, size_t size, int *min,
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

void easy_questions::reverseString(char *str) {
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

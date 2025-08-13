#include <stdio.h>
#include <stddef.h>

void print_arr(int *a, size_t size);

void reverse(int *a, size_t l, size_t r);

void rotate_right(int *a, size_t size, size_t k);

void test_rotation(int *a, size_t size, size_t k);

int main() {
  // basic cases
  int a1[] = {1, 2, 3, 4, 5};
  size_t size1 = sizeof(a1) / sizeof(a1[0]);
  test_rotation(a1, size1, 2); // Expected [4, 5, 1, 2, 3]

  int a2[] = {10, 20, 30, 40};
  size_t size2 = sizeof(a2) / sizeof(a2[0]);
  test_rotation(a2, size2, 1); // Expected [40, 10, 20, 30]

  int a3[] = {5, 6, 7};
  size_t size3 = sizeof(a3) / sizeof(a3[0]);
  test_rotation(a3, size3, 3); // Expected [5, 6, 7]

  // edge cases
  int a4[] = {1, 2, 3, 4, 5};
  size_t size4 = sizeof(a4) / sizeof(a4[0]);
  test_rotation(a4, size4, 7); // Expected [4, 5, 1, 2, 3]

  int a5[] = {42};
  size_t size5 = sizeof(a5) / sizeof(a5[0]);
  test_rotation(a5, size5, 5); // Expected [42]

  int a6[] = {};
  size_t size6 = sizeof(a6) / sizeof(a6[0]);
  test_rotation(a6, size6, 3); // Expected []

  // validators
  int a7[] = {1, 2, 3};
  size_t size7 = sizeof(a7) / sizeof(a7[0]);
  test_rotation(a7, size7, 0); // Expected [1, 2, 3]

  int a8[] = {9, 9, 9, 9};
  size_t size8 = sizeof(a8) / sizeof(a8[0]);
  test_rotation(a8, size8, 2); // Expected [9, 9, 9, 9]

  return 0;
}

void print_arr(int *a, size_t size) {
	printf("[");
	for (size_t i = 0; i < size; i++) {
		printf("%d%s", a[i], i + 1 < size ? ", " : "");
	}
	printf("]\n\n");
}

void reverse(int *arr, size_t l, size_t r) {
  while (l < r) {
    int tmp = arr[r];
    arr[r] = arr[l];
    arr[l] = tmp;
    l++;
    r--;
  }
}

void rotate_right(int *arr, size_t size, size_t k) {
  // data normalization
  if (size == 0 || (k %= size) == 0) {
    print_arr(arr, size);
    return;
  }

  if (k > size) k %= size;

  // first we fully reverse the array - first reversion
  reverse(arr, 0, size - 1);

  // then we reverse only the first k elements - second reversion
  reverse(arr, 0, k - 1);

  // finally we reverse the last elements - third reversion
  reverse(arr, k, size - 1);

  print_arr(arr, size);
}

void test_rotation(int *arr, size_t size, size_t k) {
  rotate_right(arr, size, k);
  return;
}


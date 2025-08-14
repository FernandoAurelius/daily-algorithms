#include <stdio.h>
#include <stddef.h>

int dedup_sorted_inplace(int *arr, size_t n);

void print_arr(int *a, size_t size);

int main() {
  int a1[] = {1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 5};
  size_t size = sizeof(a1) / sizeof(a1[0]);

  printf("Initial array: ");
  print_arr(a1, size);

  printf("Deduped array: ");
  int logic_size = dedup_sorted_inplace(a1, size);

  if (logic_size == -1) return 0;

  print_arr(a1, logic_size);
  printf("Final logic size: %d", logic_size);
}

void print_arr(int *a, size_t size) {
  printf("[");
  for (size_t i = 0; i < size; i++) {
    printf(
      "%d%s",
      a[i],
      i + 1 < size ? ", " : ""
    );
  }
  printf("]\n\n");
}

int dedup_sorted_inplace(int *arr, size_t n) {
  if (n == 0) {
      printf("Invalid array");
      return -1;
  }

  int slow = 0;
  size_t fast = 1;

  while(fast < n) {
    if (arr[fast] != arr[slow]) {
      slow++;
      arr[slow] = arr[fast];
    }
    fast++;
  }

  return slow + 1;
}


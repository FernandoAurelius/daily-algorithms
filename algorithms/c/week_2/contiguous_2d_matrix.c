#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

int* mat_alloc(size_t rows, size_t cols);

void mat_free(int *buf);

int mat_get(const int *buf, size_t rows, size_t cols, size_t row, size_t col);

void mat_set(int *buf, size_t rows, size_t cols, size_t row, size_t col, int v);

void fill_mat_seq(int *buf, size_t rows, size_t cols);

void print_mat(int *buf, size_t rows, size_t cols);

int main() {
  int *buf = mat_alloc(2, 3);
  fill_mat_seq(buf, 2, 3);
  print_mat(buf, 2, 3);

  printf("\n[MAT_GET] Row 2 | Col 3 | Return: %d\n", mat_get(buf, 2, 3, 1, 2)); // Should be 6

  mat_set(buf, 2, 3, 1, 2, 10);

  printf("[MAT_GET] (After MAT_SET) Row 2 | Col 3 | Return: %d\n\n", mat_get(buf, 2, 3, 1, 2)); // Should be 10

  print_mat(buf, 2, 3);

  mat_free(buf);
}

int* mat_alloc(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) return NULL;

  if (rows > SIZE_MAX / cols) return NULL;

  int *buf = calloc(rows * cols, sizeof *buf);

  if (!buf) return NULL;

  return buf;
}

void mat_free(int *buf) {
  if (buf != NULL) free(buf);
}

int mat_get(const int *buf, size_t rows, size_t cols, size_t row, size_t col) {
  if (row >= rows || col >= cols || buf == NULL) return INT_MIN;

  return buf[row * cols + col];
}

void mat_set(int *buf, size_t rows, size_t cols, size_t row, size_t col, int v) {
  if (row >= rows || col >= cols || buf == NULL) return;

  buf[row * cols + col] = v;
}

void fill_mat_seq(int *buf, size_t rows, size_t cols) {
  if (!buf) return;

  int v = 1;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      buf[i * cols + j] = v;
      v++;
    }
  }
}

void print_mat(int *buf, size_t rows, size_t cols) {
  if (!buf) return;

  for (size_t i = 0; i < rows; i++) {
    printf("%zuº row: [", i + 1);
    for (size_t j = 0; j < cols; j++) {
      printf("%d%s", buf[i * cols + j], j + 1 < cols ? ", " : "");
    }
    printf("]\n");
  }
}


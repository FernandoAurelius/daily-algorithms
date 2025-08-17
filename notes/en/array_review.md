# Initial Review — Arrays in C

> **Progress (Arrays in C)**
> - [x] Initial study completed
> - Scheduled reviews: (to fill)

## 1. Declaration and initialization of arrays
- **Static**: size defined at compile time.
```c
int arr[5] = {1, 2, 3, 4, 5};
int arr2[] = {10, 20, 30}; // size inferred
```
- **Dynamic**: allocated at runtime with `malloc`/`calloc`.
```c
int *arr = malloc(n * sizeof(int));
if (!arr) { /* error */ }
```

## 2. Pointers and pointer arithmetic
- Array name decays to `int*` when passed to a function.
- `*(arr + i)` is equivalent to `arr[i]`.

## 3. `sizeof` and decay
- In local scope: `sizeof(arr)` = total size of the array in bytes.
- In a function: `sizeof(param)` = size of the pointer (the array decays to a pointer).

## 4. Dynamic allocation
```c
int *arr = malloc(n * sizeof *arr);
arr = realloc(arr, new_size * sizeof *arr);
free(arr);
```

## 5. 2D arrays
- **Contiguous** (single block):
```c
int *mat = malloc(rows * cols * sizeof(int));
mat[i * cols + j] = value;
```
- **Array of pointers** (non-contiguous):
```c
int **mat = malloc(rows * sizeof *mat);
for (int i = 0; i < rows; i++)
    mat[i] = malloc(cols * sizeof **mat);
```

## 6. Iterating arrays
```c
for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
```

## 7. Common manipulations
- **Rotate**: three reversals.
- **Reverse**: symmetric pairwise swaps.
- **Remove elements**: shift values forward and shrink the logical size.

---

## Exercise A1 — `index_of` (statement + solution)

**Statement.** Implement a C function that receives an integer array `a`, its size `n`, and a value `x`, and returns the **index of the first occurrence** of `x`. If it does not exist, return `-1`.

**Suggested signature**
```c
int index_of(const int *a, size_t n, int x);
```

**Constraints**
- Do not modify the array (use `const int *`).
- Time complexity O(n) and extra space O(1).
- Handle `n=0` by returning `-1`.
- Avoid *undefined behavior* (check for null pointer if needed).

**Solution (your final version, with `main`)**
```c
#include <stdio.h>

int index_of(const int *arr, size_t n, int x);

int main() {
	int arr_1[3] = {3, 5, 7};
	int arr_2[3] = {1, 1, 1};
	int *arr_3 = NULL;

	printf("First array [3, 5, 7] -> x = 5: %d (SHOULD BE 1)
", index_of(arr_1, sizeof(arr_1) / sizeof(arr_1[0]), 5));
	printf("Second array [1, 1, 1] -> x = 2: %d (SHOULD BE -1)
", index_of(arr_2, sizeof(arr_2) / sizeof(arr_2[0]), 2));
	printf("Third array [] -> x = 9: %d (SHOULD BE -1)", index_of(arr_3, 0, 9));

	return 0;
}

int index_of(const int *arr, size_t n, int x) {
	int index = -1;
	for (size_t i = 0; i < n; i++) {
		if (*(arr + i) == x) {
			index = (int)i;
			break;
		}
	}
	return index;
}
```

---

## Exercise A2 — Sliding Window (max_window_sum)

### Intuition (Analogy)
Imagine a **supermarket conveyor belt**. Each product has a price and your **basket** only holds **k contiguous products**.
You want to find which conveyor position (which contiguous block of size `k`) yields the **largest total**.

- **Conveyor** → array `a[]`
- **Basket (size k)** → fixed-size window `k`
- **Slide the basket** → one item leaves on the left and one enters on the right

### Dry run (step by step)
Array `a = [1, 3, -2, 5, 3, -1]`, `k = 3`

1) Initial sum of indices `0..2`:
```
[ 1 ][ 3 ][-2 ]  5   3  -1
sum = 1 + 3 + (-2) = 2
max  = 2
```

2) Slide 1 to the right (remove `1`, add `5`):
```
  1 [ 3 ][-2 ][ 5 ]  3  -1
sum = 2 - 1 + 5 = 6
max  = max(2, 6) = 6
```

3) Slide again (remove `3`, add `3`):
```
  1   3 [-2 ][ 5 ][ 3 ] -1
sum = 6 - 3 + 3 = 6
max  = 6
```

4) Slide again (remove `-2`, add `-1`):
```
  1   3   -2 [ 5 ][ 3 ][-1]
sum = 6 - (-2) + (-1) = 7
max  = 7  ← best subarray is [5, 3, -1]
```

### Why is it O(n) and not O(n·k)?
- Brute force: recompute each window sum from scratch → O(n·k)
- Sliding window: **reuse the previous sum**, updating only 2 items (the one that leaves and the one that enters) → **O(n)**

### Statement & Constraints
**Problem.** Given an array `a` of size `n` and an integer `k` with `1 ≤ k ≤ n`, find the **maximum sum** of a **contiguous** subarray of exact size `k`.

**Constraints / Rules:**
- Do not use external libraries to directly solve it.
- **Target time:** O(n) — use the **sliding window** technique.
- **Extra space:** O(1).
- Handle valid inputs (`a != NULL`, `1 ≤ k ≤ n`); if you wish to handle errors, describe the behavior.
- Think of edge cases: `k=1`, `k=n`, negative values in the array, all equal values, mixture of positives/negatives.

**Solution (your final version, with `main`)**
```c
#include <stdio.h>
#include <stddef.h>

void get_max_window_sum(const int *arr, size_t size, size_t k);

int main() {
	int arr[] = {1, 3, -2, 5, 3, -1};

	// Should be 7
	get_max_window_sum(arr, sizeof(arr) / sizeof(arr[0]), 3);

	// Should be 5
	get_max_window_sum(arr, sizeof(arr) / sizeof(arr[0]), 1);

	// Should be -3
	int arr2[] = {-1, -1, -1, -1, -1, -1};
	get_max_window_sum(arr2, sizeof(arr2) / sizeof(arr2[0]), 3);

	// Should be nothing
	get_max_window_sum(NULL, 0, 3);

	return 0;
}

void get_max_window_sum(const int *arr, size_t size, size_t k) {
	if (arr == NULL || 1 > k || k > size) {
		printf("Invalid parameters! Null array or invalid subarray size.\n");
		return;
	}

	// good practice to avoid overflow in big sums
	long long sum = 0;

	// first we get the sum of the first window
	for (size_t i = 0; i < k; i++) {
		sum += arr[i];
	}
	printf("Initial sum: %lld\n", sum);
	long long best = sum;
	size_t best_start = 0;

	// now we apply the sliding window
	for (size_t i = k; i < size; i++) {
		sum = sum - arr[i - k] + arr[i];

		if (sum > best) {
			best = sum;
			best_start = i - k + 1;
		}
	}

	printf("Final maximum sum: %lld\n", best);
	printf("Maximum window sum: [");
	for (size_t i = 0; i < k; i++) {
		printf(
			"%d%s",
			arr[best_start + i],
			i + 1 < k ? ", " : ""
		);
	}
	printf("]\n");
	return;
}
```

---

## Exercise A3 — Rotate array to the right (three reversals)

### Theoretical Review
Rotating an array to the right by `k` can be done in O(n) time and O(1) space using **three reversals**:
1. Reverse the entire array.
2. Reverse the first `k` elements.
3. Reverse the remaining `n-k` elements.
Remember to do `k %= n` and handle trivial cases (`n == 0` or `k == 0`).

### Statement
Given an array `a` of size `n` and an integer `k`, rotate `a` **to the right** by `k` positions **in-place**, using the three-reversal technique.

### Solution (student code, unchanged except for message translation)
```c
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

  // first we fully reverse the array - first reversal
  reverse(arr, 0, size - 1);

  // then we reverse only the first k elements - second reversal
  reverse(arr, 0, k - 1);

  // finally we reverse the last elements - third reversal
  reverse(arr, k, size - 1);

  print_arr(arr, size);
}

void test_rotation(int *arr, size_t size, size_t k) {
  rotate_right(arr, size, k);
  return;
}
```

---

## Exercise A4 — Remove duplicates in a sorted array (two pointers)

### Theoretical Review
- **Precondition:** array in **non-decreasing order**; duplicates are **adjacent**.
- **Two pointers:** `slow` writes the compacted part; `fast` reads the rest. Start with **`fast = slow + 1`** (if `n>0`).
- **Movement:** if `a[fast] != a[slow]`, then `slow++` and `a[slow] = a[fast]`.
- **Logical size:** at the end, `slow + 1` (if `n>0`).
- **Complexity:** time **O(n)**; extra space **O(1)**.
- **Pitfalls:** loop must be **`fast < n`** (prevents invalid access); handle `n==0`; do not use `const int *` (we modify the array).

### Analogy
A T-shirt catalog already **sorted by size**: iterate and **keep only the first** of each size. The final catalog occupies the **first positions**.

### Dry run
`a = [1, 1, 2, 2, 2, 3, 4, 4]` → uniques in the **first 4** slots: `[1,2,3,4]` (rest is irrelevant).
Edge cases: `[]→0`, `[7]→1`, `[1,2,3]→3`, `[5,5,5]→1`.

### Statement & Constraints
Implement `size_t dedup_sorted_inplace(int *a, size_t n);` which **removes duplicates in-place** from a **sorted** array and returns the **new logical size**.
Constraints: **O(n)** time, **O(1)** extra space; handle `n==0`; content after the logical size is irrelevant.

### Solution (student code, unchanged except for message translation)
```c
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
  printf("Final logical size: %d", logic_size);
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
```

---

## Exercise A5 — Contiguous 2D matrix (`malloc` + linear indexing)

### Theoretical Review
- **Objective:** represent a `rows x cols` matrix in **a single contiguous block** of memory using `malloc`.
- **Contiguous allocation:** `int *buf = malloc(rows * cols * sizeof *buf);`
  - **Advantages:** a single `malloc/free`, better **cache locality**, no fragmentation between rows.
  - **Cautions:** validate `buf != NULL`; watch for overflow in `rows * cols` if using small types.
- **Row-major layout (C):** elements of a row are laid out **next to each other** in memory.
  - **Linear indexing:** `buf[i * cols + j]` accesses cell `(i, j)`.
  - **Address:** `&buf[i * cols + j]` → compare with “`&buf[0] + (i*cols + j)`”.
- **Comparison with `int**` (pointer to pointer):**
  - `int **a` **does not guarantee contiguity**: each row can be a separate block (multiple `malloc` calls).
  - In a contiguous model, you have **one** block; with `int**`, you have **N+1** blocks (row vector + N rows).
- **Passing to functions:** pass the **base pointer**, plus `rows` and `cols`.
  - Example: `int get(const int *buf, size_t rows, size_t cols, size_t i, size_t j)`.
- **Initialization:** `calloc` zeroes the memory; `malloc` does not (indeterminate content).
- **Freeing:** `free(buf);` (only **once**).
- **Common pitfalls:**
  - **Off-by-one:** remember `0 ≤ i < rows` and `0 ≤ j < cols`.
  - **Mixing `int**` with contiguous block:** `a[i][j]` only works if you model as `int (*a)[cols]` (VLA) or a properly initialized `int**`; with `int *buf`, use **linear indexing**.
  - **Overflow:** if `rows*cols` can exceed `size_t`, validate before multiplying.

### Analogy
Imagine a **spreadsheet** where you “unroll” all rows into a **continuous tape**. Cell `(i, j)` becomes position **`i*cols + j`** on that tape. You move along the tape by adding fixed offsets of `cols` to jump from one row to the next.

### Dry run
`rows=3`, `cols=4` → valid indices `(0..2, 0..3)`
Fill with `value = i*cols + j`:
- Row 0: `[0, 1, 2, 3]`
- Row 1: `[4, 5, 6, 7]`
- Row 2: `[8, 9, 10, 11]`
Check: `buf[2*4 + 1] = buf[9] = 9` (cell `(2,1)`).

### Statement & Constraints
Implement a minimal API for a **contiguous 2D matrix**:
1. `int* mat_alloc(size_t rows, size_t cols)` → allocates and returns the contiguous buffer (or `NULL`).
2. `void mat_free(int *buf)` → frees the buffer.
3. `int  mat_get(const int *buf, size_t rows, size_t cols, size_t i, size_t j)` → reads `(i,j)` validating bounds (define an error policy).
4. `void mat_set(int *buf, size_t rows, size_t cols, size_t i, size_t j, int v)` → writes `(i,j)` validating bounds.
5. (Optional) `void mat_fill_seq(int *buf, size_t rows, size_t cols)` → sets `buf[k]=k` to ease debugging.

**Constraints:**
- Use **one contiguous block** (`malloc`/`calloc`) and **linear indexing** (`i*cols + j`).
- Per-access time **O(1)**; extra space beyond the buffer **O(1)**.
- Handle edge cases (`rows==0` or `cols==0` → return `NULL` in the allocator, for example).

### Solution (student code, unchanged except for message translation)
```c
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
    printf("%zuth row: [", i + 1);
    for (size_t j = 0; j < cols; j++) {
      printf("%d%s", buf[i * cols + j], j + 1 < cols ? ", " : "");
    }
    printf("]\n");
  }
}
```

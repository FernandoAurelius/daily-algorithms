#include <stdio.h>

int index_of(const int *arr, size_t n, int x);

int main() {
	int arr_1[3] = {3, 5, 7};
	int arr_2[3] = {1, 1, 1};
	int *arr_3 = NULL;

	printf("First array [3, 5, 7] -> x = 5: %d (SHOULD BE 1)\n", index_of(arr_1, sizeof(arr_1) / sizeof(arr_1[0]), 5));
	printf("Second array [1, 1, 1] -> x = 2: %d (SHOULD BE -1)\n", index_of(arr_2, sizeof(arr_2) / sizeof(arr_2[0]), 2));
	printf("Third array [] -> x = 9: %d (SHOULD BE -1)", index_of(arr_3, 0, 9));

	return 0;
}

int index_of(const int *arr, size_t n, int x) {
	int index = -1;
	for (size_t i = 0; i < n; i++) { 
		if (*(arr + i) == x) {
			index = i; 
			break; 
		}
	}
	return index;
}


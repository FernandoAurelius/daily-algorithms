#include <stdio.h>
#include <stdlib.h>

struct MaxWindowSum {
	int sum;
	int arr[];
};

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
		printf("Invalid parameters! Null array or invalid k");
		return;
	}

	// First we get the initial sum
	struct MaxWindowSum *max_window_sum = malloc(sizeof(struct MaxWindowSum *) + k * sizeof(int));
	if (!max_window_sum) {
		printf("Error during memory allocation - Xd");
		return;
	}
	max_window_sum->sum = 0;
	for (size_t i = 0; i < k; i++) {
		max_window_sum->sum += *(arr + i);
		max_window_sum->arr[i] = *(arr + i);
	}
	printf("Initial sum: %d | Initial window: ", max_window_sum->sum);
	for (size_t i = 0; i < k; i++) {
		if (i == 0 && k == 1) {
			printf("[%d]\n\n", max_window_sum->arr[i]);
			break;
		}

		if (i == 0) {
			printf("[%d,", max_window_sum->arr[i]);  
		} else if (i != (k - 1) && i != 0) {
			printf("%d,", max_window_sum->arr[i]);
		} else {
			printf("%d]\n\n", max_window_sum->arr[i]);
		}
	}

	// Now, we apply the sliding window logic
	
	// TODO: add subarray mapping here
	for (size_t i = k; i < size; i++) {
		printf("Subtraction to me made: (%d - %d) | Result sum: %d\n", max_window_sum->sum, *(arr + i - k), max_window_sum->sum - *(arr + i - k) + *(arr + i));
		max_window_sum->sum = (max_window_sum->sum - *(arr + i - k) + *(arr + i));
		printf("Debug values: i - %lu | k - %lu | sum - %d | (i-k) - %lu\n", i, k, max_window_sum->sum, i-k);
	}
	printf("\nFinal sum: %d | Final window: ", max_window_sum->sum);
	for (size_t i = 0; i < k; i++) {
		if (i == 0) {
			printf("[%d,", max_window_sum->arr[i]);  
		} else if (i != k - 1 && i != 0) {
			printf("%d,", max_window_sum->arr[i]);
		} else {
			printf("%d]\n\n", max_window_sum->arr[i]);
		}
	}


	free(max_window_sum);
	return;
}


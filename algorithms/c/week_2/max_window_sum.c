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

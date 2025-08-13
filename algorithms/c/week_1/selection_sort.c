#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct IntArray {
	int *data;
	int size;
} IntArray;

static int find_smallest(int *arr, int size);

static void fill_array_randomly(int *arr, int size);

int* selection_sort(int *arr, int size);

static void print_arr(int *arr, int size);

int main() {
	srand(time(NULL));
	int size = 0;

	printf("Welcome! First, enter the desired size for the array: ");
	scanf("%d", &size);

	int *tmp = malloc(size * sizeof(int));

	if (tmp == NULL) {
		printf("Memory allocation error! Try again Xd.");
		return 1;
	}

	struct IntArray arr = {tmp, size};

	fill_array_randomly(arr.data, arr.size);
	printf("Array elements before sorting:\n");
	print_arr(arr.data, arr.size);	

	printf("Array elements after sorting:\n");
	arr.data = selection_sort(arr.data, arr.size);
	print_arr(arr.data, arr.size);

	free(arr.data);

	return 0;
}

static int find_smallest(int *arr, int size) {
	int smallest = INT_MAX;
	int smallest_idx = -1;

	for (int i = 0; i < size; i++) {
		// Debug: printf("\nArray in %d position (%d) is -1? %s", i, *(arr + i), *(arr + i) == -1 ? "true" : "false");
		if (*(arr + i) == -1) { 
			// Debug: printf(" | Array in current position is -1, continuing"); 
			continue; 
		}; 
		if (*(arr + i) < smallest) {
			smallest = *(arr + i);
			smallest_idx = i;
			// Debug: printf(" | Smallest item in array is %d, filling", smallest);
		}
	}
	// Debug: printf("\nSmallest found: %d", smallest);
	
	if (smallest_idx != -1) *(arr + smallest_idx) = -1;
	return smallest;
}

static void fill_array_randomly(int *arr, int size) {
	int min_val = 1;
	for (int i = 0; i < size; i++) {
		*(arr + i) = (rand() % (size - min_val + 1)) + min_val;
	}
}

int* selection_sort(int *arr, int size) {
	int* sorted_arr = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		int smallest = find_smallest(arr, size);
		*(sorted_arr + i) = smallest;
		// Debug: printf("\nFilled array in %d position: %d | Smallest found: %d", i, *(sorted_arr + i), smallest);
	}
	free(arr);
	return sorted_arr;
}

static void print_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (i == size - 1) { printf("%d.\n", *(arr + i)); return; }
		printf("%d, ", *(arr + i));
	}
}


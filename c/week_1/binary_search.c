#include <stdio.h>
#include <stdlib.h>

struct SearchResult {
	int index;
	int steps;
};

struct SearchResult binary_search(int *haystack, int needle, int size);
void fill_array(int *arr, int arr_size);

int main() {
	printf("Welcome! First, enter the desired size for the array: ");
	int size;
	scanf("%d", &size);

	int *haystack = malloc(size * sizeof(int));

	if (haystack == NULL) {
		printf("Memory allocation failed! Xd\n");
		return 1;
	}

	int needle;

	fill_array(haystack, size);
	printf("Enter a number between 1 and %d: ", size);
	scanf("%d", &needle);
	struct SearchResult response = binary_search(haystack, needle, size);
	if (response.index == -1) { 
		printf("NOT FOUND! The element couldn't be find :/\n Try again later, bye!"); 
		return 0; 
	}
	printf("\nFOUND! The sought element is at position %d, and was found in %d steps! xD", response.index, response.steps);
}

struct SearchResult binary_search(int *haystack, int needle, int size) {
	int bottom = 0;
	int top = size - 1;
	int steps = 0;
	struct SearchResult response;
	while (bottom <= top) {	
		steps++;
		int middle = (top + bottom) / 2;
		int guess = haystack[middle];
		if (needle == guess) {
			response.index = middle;
			response.steps = steps;
			return response;
		};
		if (needle < guess) top = middle - 1;
		if (needle > guess) bottom = middle + 1;
	}
	response.index = -1;
	return response;
}

void fill_array(int *arr, int arr_size) {
	for (int i = 0; i < arr_size; i++) {
		*(arr + i) = (1+i);
	}
}


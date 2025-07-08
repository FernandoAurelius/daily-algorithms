import java.util.InputMismatchException;
import java.util.Scanner;

public class BinarySearch {
	static SearchResult binary_search(int[] haystack, int needle) {
		int top = haystack.length - 1;
		int bottom = 0;
		int steps = 0;
		while (bottom <= top) {
			steps++;
			int middle = (top + bottom) / 2;
			int guess = haystack[middle];
			if (guess == needle) return new SearchResult(middle, steps); 
			if (guess > needle) top = middle - 1;
			if (guess < needle) bottom = middle + 1;
		}
		return null;
	}

	static void fill_array(int[] array) {
		for (int i = 0; i < array.length; i++) {
			array[i] = (1+i);
		}
	}

	static int validate_integer_input(int var, Scanner sc) throws IllegalArgumentException {
		try {
			var = sc.nextInt();
			return var;
		} catch (InputMismatchException e) {
			System.out.println("\nInvalid character entered! Please only input integer numbers.");
			throw e;
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		try {
			System.out.print("Welcome! First, please enter the desired var for the array: ");
			int size = 0; size = validate_integer_input(size, sc);
		
			int[] haystack = new int[size];
			fill_array(haystack);
		
			System.out.print("\nOK! Now, enter the element to be looked for: ");
			int needle = 0; needle = validate_integer_input(needle, sc);
			
			SearchResult response = binary_search(haystack, needle);
			if (response == null) {
				System.out.println("The element could not be found! Try again :/");
				return;
			}	
			System.out.printf("\nThe element position is %d, and it was found in %d steps! xD", response.index, response.steps);
		} catch (InputMismatchException e) {
			return;
		} catch (Exception e) {
			System.out.println("\nAn unexpected error happened! xO");
			return;
		} finally {
			sc.close();
		}
	}
}

class SearchResult {
	int index;
	int steps;

	public SearchResult(int index, int steps) {
		this.index = index;
		this.steps = steps;
	}
}


import java.util.Random;
import java.util.Scanner;

public class SelectionSort {
	static final Random rand = new Random();

	static void printArray(int[] arr) {
		System.out.print("[");
		for (int i = 0; i < arr.length; i++) {
			if (i == arr.length -1) {
				System.out.print(arr[i]);
				continue;
			}
			System.out.print(arr[i] + ", ");
		}
		System.out.println("]");
	}		

	static int findSmallest(int[] arr) {
		int smallest = Integer.MAX_VALUE;
		int smallestIdx = -1;
		for (int i = 0; i < arr.length; i++) {
			if (arr[i] == -1) continue;
			if (arr[i] < smallest) {
				smallest = arr[i];
				smallestIdx = i;
			}
		}
			
		if (smallestIdx != -1) { 
			// Debug: System.out.printf("\n--Smallest: %d | Array in smallestIdx: %d\n", smallest, arr[smallestIdx]);	
			// Debug: System.out.printf("Array: ");
			// Debug: printArray(arr);
			arr[smallestIdx] = -1;
		}
		
		return smallest;
	}

	static void fillArray(int[] arr) {
		for (int i = 0; i < arr.length; i++) {
			arr[i] = SelectionSort.rand.nextInt(arr.length + 1);
		}
	}

	static int[] selectionSort(int[] arr) {
		int[] temp = new int[arr.length];
		for (int i = 0; i < arr.length; i++) {
			int smallest = findSmallest(arr);
			temp[i] = smallest;
		}
		return temp;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		try {
			int size = 0;
			System.out.print("Welcome! Please enter the desired size for the array: ");
			size = sc.nextInt(); sc.nextLine();
			
			int[] arr = new int[size];
			fillArray(arr);
			System.out.println("\nCool! Now let's see the array before sorting: ");
			printArray(arr);

			arr = selectionSort(arr);
			System.out.println("Now, let's see the array after sorting: ");
			printArray(arr);
		} catch (Exception e) {
			System.out.println("Unexpected error! " + e.toString());
		} finally {
			sc.close();
		}
	}
}

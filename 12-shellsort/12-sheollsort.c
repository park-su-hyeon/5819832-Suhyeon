#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 

int main() {
	int array[ARRAY_SIZE];
	int comparisonCount, moveCount;

	generateRandomNumbers(array);

	//Shell Sort
	printf("Sell Sort (n/2):\n");
	doShellSort(array, 2, &comparisonCount, &moveCount);
	printf("Sell Sort (n/2) - Comarisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

	printf("Shel Sort (n/3):\n");
	doSellSort(array, 3, &comparisonCount, &moveCount);
	printf("Shel Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

	//Insertion Sort - Bonus
	printf("Insertion Sort:\n");
	doInsertionSort(array, &comparisonCount, &moveCount);
	printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

	return 0;
}

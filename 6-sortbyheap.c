﻿#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void resortHeap(int inputData[], int n, int i) {
	int largest = i; // 루트를 가장 큰 값으로 설정
	int left = 2 * i + 1; // 왼쪽 자식
	int right = 2 * i + 2; // 오른쪽 자식

	// 왼쪽 자식이 더 큰 경우
	if (left < n && inputData[left] > inputData[largest]) {
		largest = left;
	}

	// 오른쪽 자식이 더 큰 경우
	if (right < n && inputData[right] > inputData[largest]) {
		largest = right;
	}

	// 루트가 가장 큰 값이 아닐 경우 교환하고 재귀 호출
	if (largest != i) {
		swap(&inputData[i], &inputData[largest]);
		resortHeap(inputData, n, largest);
	}
}

void BuildMaxHeap(int inputData[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		resortHeap(inputData, n, i);
	}
}

void BuildMaxHeapAndSort(int inputData[], int n) {
	// max heap 생성하는 함수
	BuildMaxHeap(inputData, n);
	// 하나씩 힙에서 루트(최대값)를 제거하고 정렬
	for (int i = n - 1; i > 0; i--) {
		swap(&inputData[0], &inputData[i]);
		resortHeap(inputData, i, 0);
		// 힙 재정렬 후 상태 출력
		for (int j = 0; j < i; j++) {
			printf("%d ", inputData[j]);
		}
		printf("\n");
	}
}


int main() {
	int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
	int size = sizeof(inputData) / sizeof(inputData[0]);
	// 힙 정렬 실행
	printf("<Sort>\n");
	BuildMaxHeapAndSort(inputData, size);
	// 정렬된 결과 출력
	printf("\nSorted Array:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", inputData[i]);
	}
	printf("\n");
	return 0;
}
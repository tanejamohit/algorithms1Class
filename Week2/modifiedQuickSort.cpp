#include <iostream>
#include "assert.h"

#define DEBUG 0
#define PIVOT_SELECTION_METHOD 2
using namespace std;

void quickSort (int * array, int startIndex, int endIndex, unsigned long long *totalChecks) {
	if(DEBUG) {
		cout<<"Length of Array :"<<endIndex-startIndex<<endl;
		//assert((endIndex-startIndex)>=1);
	}
	if(endIndex-startIndex <= 1) {
		return;
	}
	(*totalChecks) += endIndex - startIndex -1;
	int pivotIndex;
	
	if(PIVOT_SELECTION_METHOD == 0) { pivotIndex = startIndex; }
	else if (PIVOT_SELECTION_METHOD == 1) { pivotIndex = endIndex -1; }
	else if (PIVOT_SELECTION_METHOD == 2) {
		int middleIndex = startIndex + (endIndex-startIndex-1)/2;

		if ( ((array[endIndex-1]   <= array[middleIndex]) && (array[middleIndex] <= array[startIndex])) ||
			 ((array[startIndex] <= array[middleIndex]) && (array[middleIndex] <= array[endIndex-1])) ) {
			pivotIndex = middleIndex;
		}
		else if ( ((array[middleIndex] <= array[startIndex]) && (array[startIndex] <= array[endIndex-1])) ||
			 	  ((array[endIndex-1]    <= array[startIndex]) && (array[startIndex] <= array[middleIndex])) ) {
			pivotIndex = startIndex;
		}
		else if ( ((array[middleIndex] <= array[endIndex-1]) && (array[endIndex-1] <= array[startIndex])) ||
			 	  ((array[startIndex]  <= array[endIndex-1]) && (array[endIndex-1] <= array[middleIndex])) ) {
			pivotIndex = endIndex-1;
		}
		if(DEBUG) {
			cout<<"pivotIndex = "<<pivotIndex<<endl;
		}
	}
	
	int pivot = array[pivotIndex];
	int j = startIndex;
	int temp;

	// Place the pivot at startIndex
	temp = array[startIndex];
	array[startIndex] = array[pivotIndex];
	array[pivotIndex] = temp;

	// Partitioning
	for(int i=startIndex;i<endIndex;i++) {
		if(array[i]<=pivot) {
			// Exchange i and j
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			j++;
		}
	}

	// Place the pivot at its corrrect position
	array[startIndex] = array[j-1];
	array[j-1] = pivot;

	// reCurse again
	if(DEBUG) {
		cout<<"j:"<<j<<" startIndex:"<<startIndex<<" endIndex:"<<endIndex<<" pivotIndex:"<<pivotIndex<<endl;
	}
	quickSort(array, startIndex, j-1, totalChecks);
	quickSort(array, j, endIndex, totalChecks);

	return;
}

int main () {
	int dataLength = 10000;
	unsigned long long totalChecks = 0;
	int * array = new int[dataLength];
	for (int i = 0; i < dataLength; ++i)
	{
		cin>>array[i];
	}
	quickSort(array,0,dataLength,&totalChecks);
	cout<<totalChecks;
	return 0;
} 
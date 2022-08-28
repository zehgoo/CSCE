#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>

#define SIZE 1000000		// Size set to 10k for testing
using std::cout;
using std::endl;

void InsertionSort(std::vector<int>& data)
{
	int i = 1;
    //cout << i << endl;
	while (i < data.size())
	{
		int temp = data.at(i);
		int j = i - 1;
		while (j >= 0 && data.at(j) > temp)
		{
			data.at(j + 1) = data.at(j);
			j-=1;
		}
		data.at(j + 1) = temp;
		i++;
        // if((i % 1000) == 0)
        //     cout << i << endl;
	}
}

void SelectionSort(std::vector<int>& data)
{
	int minNum;
    for (int i = 0; i < data.size() - 1; i++)
    {
        minNum = i;
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data.at(j) < data.at(minNum))
                minNum = j; 
        }

        if (minNum != i)
            std::swap(data.at(i), data.at(minNum));

        if((i % 1000) == 0)
            cout << i << endl;
    }
}

// Builds max heap
void Heapify(std::vector<int>& data, int n, int i) 
{
	int rootNode = i;
	int leftNode = 2 * i + 1;
	int rightNode = 2 * i + 2;
  
	if (leftNode < n && data[leftNode] > data[rootNode])
		rootNode = leftNode;

	if (rightNode < n && data[rightNode] > data[rootNode])
		rootNode = rightNode;

	if (rootNode != i) 
	{
		std::swap(data.at(i), data[rootNode]);
		Heapify(data, n, rootNode);
	}
  }
  
// Main function for heap sort
void HeapSort(std::vector<int>& data) 
{
    int n = data.size();
    
	// Building max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(data, n, i);
  
	// Sorting array
	for (int i = n - 1; i >= 0; i--) 
	{
		std::swap(data[0], data.at(i));
		Heapify(data, i, 0);
    }
}

// Merges two sub arrays into one array.
void Merge(std::vector<int>& leftVec, std::vector<int>& rightVec, std::vector<int>& data)
{
	data.clear();

	while (leftVec.size() > 0 || rightVec.size() > 0)
	{
		if (leftVec.size() > 0 && rightVec.size() > 0)
		{
			if (leftVec.front() <= rightVec.front())
			{
				data.push_back(leftVec.front());
				leftVec.erase(leftVec.begin());
			}
			else
			{
				data.push_back(rightVec.front());
				rightVec.erase(rightVec.begin());
			}
		}

		else if (leftVec.size() > 0)
		{
			for (int i = 0; i < leftVec.size(); i++)
			{
				data.push_back(leftVec.at(i));
			}
			break;
		}
		else if (rightVec.size() > 0)
		{
			for (int i = 0; i < rightVec.size(); i++)
			{
				data.push_back(rightVec.at(i));
			}
			break;
		}
	}
}

void MergeSort(std::vector<int>& data)
{
	std::vector<int> left, right;

	if (data.size() <= 1)
	{
		return;
	}

	int middle = ((data.size()) + 1) / 2;

	for (int i = 0; i < middle; i++)
	{
		left.push_back(data.at(i));
	}
	for (int i = middle; i < data.size(); i++)
	{
		right.push_back(data.at(i));
	}

	MergeSort(left);
	MergeSort(right);
	Merge(left, right, data);

}

// Hoare Partition
int Partition(std::vector<int>& data, int low, int high)
{
    int pivot = data.at(floor((high + low) / 2)); // middle element
	//cout << pivot << std::endl;
    int i = low - 1;  // left index
	int j = high + 1;	// right index

	while(true)
	{
		do
		{
			i+=1;
		} while (data.at(i) < pivot);

		do
		{
			j-=1;
		} while (data.at(j) > pivot);

		if (i >= j)
			return j;

		std::swap(data.at(i), data.at(j));
		
	}
}

void QuickSort(std::vector<int>& data, int low, int high)
{
    if (low >= 0 && high >= 0 && low < high)
    {
        int pivot = Partition(data, low, high);
		QuickSort(data, low, pivot);
		QuickSort(data, pivot + 1, high);
    }
}

//Generates data file
void GenerateData()
{
    int num;
    std::ofstream writeFile;

    writeFile.open("data");

    for (int i = 0; i < SIZE; i++)
    {
        num = rand() % 100000;
        writeFile << num << '\n';
    }

	writeFile.close();
}

void PrintData(std::vector<int> &data)
{
    for (auto i : data)
        cout << i << '\n'; 
}

void SaveSortedData(std::vector<int> &data)
{
    std::ofstream writeFile;
    writeFile.open("sortedData");

    for (int i = 0; i < data.size(); i++)
        writeFile << data.at(i) << '\n'; 

    writeFile.close();
}

int main()
{
    std::vector<int> randomData, sortedData;
    std::ifstream readFile, readFile2;
	
    srand(time(NULL));
	//GenerateData();
    
	readFile.open("randomData");
    readFile2.open("sortedData");

    int num;
    for (int i = 0; i < SIZE; i++)
    {
        readFile >> num;
        randomData.push_back(num);
    }
    
    for (int i = 0; i < SIZE; i++)
    {
        readFile2 >> num;
        sortedData.push_back(num);
    }


	readFile.close();
    readFile2.close();

/*
	Sorting Functions. Uncomment the corresponding lines to run the sorting function
*/
/*  
    // Insertion Sort

    auto start = std::chrono::high_resolution_clock::now();
    InsertionSort(randomData);
    auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop - start;
    cout << "Insertion Sort (randomized data) elapsed time: " << elapsedSeconds.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    InsertionSort(sortedData);
    stop = std::chrono::high_resolution_clock::now();
	elapsedSeconds = stop - start;
    cout << "Insertion Sort (sorted data) elapsed time: " << elapsedSeconds.count() << "s\n";
*/


    // Selection Sort

    auto start = std::chrono::high_resolution_clock::now();
    //SelectionSort(randomData);
    auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop - start;
    //cout << "Selection Sort (randomized data) elapsed time: " << elapsedSeconds.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    SelectionSort(sortedData);
    stop = std::chrono::high_resolution_clock::now();
	elapsedSeconds = stop - start;
    cout << "Selection Sort (sorted data) elapsed time: " << elapsedSeconds.count() << "s\n";


/*
    // Heap Sort

    auto start = std::chrono::high_resolution_clock::now();
    HeapSort(randomData);
    auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop - start;
    cout << "Heap Sort (randomized data) elapsed time: " << elapsedSeconds.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    HeapSort(sortedData);
    stop = std::chrono::high_resolution_clock::now();
	elapsedSeconds = stop - start;
    cout << "Heap Sort (sorted data) elapsed time: " << elapsedSeconds.count() << "s\n";


/*
    //Merge Sort

    auto start = std::chrono::high_resolution_clock::now();
	MergeSort(data);
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop-start;
    cout << "Merge Sort (randomized data) elapsed time: " << elapsedSeconds.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
	MergeSort(data);
	stop = std::chrono::high_resolution_clock::now();
	elapsedSeconds = stop-start;
    cout << "Merge Sort (sorted data) elapsed time: " << elapsedSeconds.count() << "s\n";

*/


    // Quick Sort
/*
    auto start = std::chrono::high_resolution_clock::now();
	QuickSort(randomData, 0, randomData.size() - 1);
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop-start;
    cout << "Quick Sort elapsed time: " << elapsedSeconds.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
	QuickSort(data2, 0, data2.size() - 1);
	stop = std::chrono::high_resolution_clock::now();
	elapsedSeconds = stop-start;
    cout << "2nd run Quick Sort elapsed time: " << elapsedSeconds.count() << "s\n";

*/
    //SaveSortedData(data2);
    //PrintData(data2);
    return 0;
}
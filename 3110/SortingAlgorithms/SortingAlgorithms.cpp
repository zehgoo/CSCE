#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cmath>

#define SIZE 10000		// Size set to 10k for testing
using std::cout;
using std::endl;


void InsertionSort(std::vector<int> &data)
{
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 1; i < data.size(); i++)
	{
		int key = data.at(i);
		int j = i - 1;
		while (j >= 0 && data.at(j) > key)
		{
			data.at(j + 1) = data.at(j);
			j--;
		}
		data.at(j + 1) = key;
	}

	//Calculating how long insertion sort took to run
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop-start;
    std::cout << "Insertion Sort elapsed time: " << elapsedSeconds.count() << "s\n";
}

void SelectionSort(std::vector<int>& data)
{
    auto start = std::chrono::high_resolution_clock::now();
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

		cout << i << endl;
    }

	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop-start;
    std::cout << "Selection Sort elapsed time: " << elapsedSeconds.count() << "s\n";
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
	auto start = std::chrono::high_resolution_clock::now();
    
	// Building max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		Heapify(data, n, i);
  
	// Sorting array
	for (int i = n - 1; i >= 0; i--) 
	{
		std::swap(data[0], data.at(i));
		Heapify(data, i, 0);
    }

	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedSeconds = stop-start;
    std::cout << "Heap Sort elapsed time: " << elapsedSeconds.count() << "s\n";
}

// Merges two sub arrays into one array. Used in Merge Sort
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
	//std::cout << pivot << std::endl;
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

void PrintData(std::vector<int> &data)
{
    for (auto i : data)
        cout << i << '\n'; 

	cout << "SIZE: " << data.size() << endl;   
}

//Generates data file
void GenerateData()
{
    int num;

    srand(time(NULL));
    std::ofstream writeFile;

    writeFile.open("data");

    for (int i = 0; i < SIZE; i++)
    {
        num = rand() % 100000;
        writeFile << num << '\n';
    }

	writeFile.close();
}


int main()
{

    std::vector<int> data;
    std::ifstream readFile;
	
	//GenerateData();
    
	readFile.open("data");
    int num;
    
    for (int i = 0; i < SIZE; i++)
    {
        readFile >> num;
        data.push_back(num);
    }

	readFile.close();

/*

	Sorting Functions. Uncomment the corresponding line to run the sorting function

*/

    //InsertionSort(data);
    //SelectionSort(data);
	//HeapSort(data);

    // auto start = std::chrono::high_resolution_clock::now();
	// MergeSort(data);
	// auto stop = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> elapsedSeconds = stop-start;
    // std::cout << "Merge sort elapsed time: " << elapsedSeconds.count() << "s\n";

    // auto start = std::chrono::high_resolution_clock::now();
	// QuickSort(data, 0, data.size() - 1);
	// auto stop = std::chrono::high_resolution_clock::now();
	// std::chrono::duration<double> elapsedSeconds = stop-start;
    // std::cout << "Quick Sort elapsed time: " << elapsedSeconds.count() << "s\n";

	//Sanity Check
    //PrintData(data);
    return 0;
}
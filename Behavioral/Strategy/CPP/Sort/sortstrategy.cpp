/*
 * (c) 2015 Raghavendra Nayak, All Rights Reserved.
 * www.openguru.com/
 */

#include <iostream>
#include <string>

// This abstract class provides the SortingAlgorithm interface
class SortingAlgorithms
{
public:
    SortingAlgorithms() {}
    virtual ~SortingAlgorithms() {}

    virtual void sort(const std::string& arrayName) = 0;
};

// Implements the SortingAlgorithm interface via QuickSort
class QuickSort : public SortingAlgorithms
{
public:
    virtual void sort(const std::string& arrayName) {
        std::cout << "Sorting " << arrayName << " using QuickSort." << std::endl;
    }
};

// Implements the SortingAlgorithm interface via MergeSort
class MergeSort : public SortingAlgorithms
{
public:
    virtual void sort(const std::string& arrayName) {
        std::cout << "Sorting " << arrayName << " using MergeSort." << std::endl;
    }
};

// Implements the SortingAlgorithm interface via BubbleSort
class BubbleSort : public SortingAlgorithms
{
public:
    virtual void sort(const std::string& arrayName) {
        std::cout << "Sorting " << arrayName << " using BubbleSort." << std::endl;
    }
};

class Array
{
    SortingAlgorithms* sortStrategy;
    std::string arrayName;
public:
    enum SortStrategy
    {
        QUICK, MERGE, BUBBLE
    };
    Array(const std::string& arrayName)
        : sortStrategy(nullptr), arrayName(arrayName) {
    }
    void setStrategy(const int type) {
        switch (type) {
        case QUICK:
            sortStrategy = new QuickSort();
            break;
        case MERGE:
            sortStrategy = new MergeSort();
            break;
        case BUBBLE:
            sortStrategy = new BubbleSort();
        default:
            break;
        }
    }
    void applyStrategy() {
        if (sortStrategy != nullptr) {
            sortStrategy->sort(arrayName);
        }
    }
};

int main(int argc, char **argv)
{
    Array intArray("integer array");
    int sortStrategy;
    std::cout << "Enter the strategy for sorting: Quick(0) Merge(1) Bubble(2) : ";
    std::cin >> sortStrategy;
    
    intArray.setStrategy(sortStrategy);
    intArray.applyStrategy();

    return 0;
}

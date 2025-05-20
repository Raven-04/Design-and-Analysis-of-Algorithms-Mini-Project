#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace chrono;

long long comparisons = 0;
long long swaps = 0;

// first element as the pivot
int partition_first(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high) {
            comparisons++;
            if (arr[i] > pivot) break;
            i++;
        }
        while (j >= low + 1) {
            comparisons++;
            if (arr[j] <= pivot) break;
            j--;
        }
        if (i < j) {
            swap(arr[i], arr[j]);
            swaps++;
            i++;
            j--;
        }
    }
    swap(arr[low], arr[j]);
    swaps++;
    return j;
}

// Median-of-three fixed partition
int partition_median_fixed(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[high] < arr[low]) {
        swap(arr[low], arr[high]);
    }
    if (arr[mid] < arr[low]) {
        swap(arr[mid], arr[low]);
    }
    if (arr[high] < arr[mid]) {
        swap(arr[mid], arr[high]);
    }

    swap(arr[mid], arr[low]);
    swaps++;

    return partition_first(arr, low, high);
}

// Median-of-three random partition
int partition_median_random(vector<int>& arr, int low, int high) {
    int a = low + rand() % (high - low + 1);
    int b = low + rand() % (high - low + 1);
    int c = low + rand() % (high - low + 1);

    // Finding the median value
    int mid_value = max(min(arr[a], arr[b]), min(max(arr[a], arr[b]), arr[c]));

    if (arr[a] == mid_value) {
        swap(arr[a], arr[low]);
    }
    else if (arr[b] == mid_value) {
        swap(arr[b], arr[low]);
    }
    else {
        swap(arr[c], arr[low]);
    }

    swaps++;

    return partition_first(arr, low, high);
}

void quicksort_first(vector<int>& arr, int low, int high) {
    while (low < high) {
        int p = partition_first(arr, low, high);

        if (p - low < high - p) {
            quicksort_first(arr, low, p - 1);
            low = p + 1;
        }
        else {
            quicksort_first(arr, p + 1, high);
            high = p - 1;
        }
    }
}

void quicksort_median_fixed(vector<int>& arr, int low, int high) {
    while (low < high) {
        int p = partition_median_fixed(arr, low, high);

        if (p - low < high - p) {
            quicksort_median_fixed(arr, low, p - 1);
            low = p + 1;
        }
        else {
            quicksort_median_fixed(arr, p + 1, high);
            high = p - 1;
        }
    }
}

void quicksort_median_random(vector<int>& arr, int low, int high) {
    while (low < high) {
        int p = partition_median_random(arr, low, high);

        if (p - low < high - p) {
            quicksort_median_random(arr, low, p - 1);
            low = p + 1;
        }
        else {
            quicksort_median_random(arr, p + 1, high);
            high = p - 1;
        }
    }
}

vector<int> generateBestCase(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = rand();
    return arr;
}

vector<int> generateWorstCase(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = i;
    return arr;
}

vector<int> generateAverageCase(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
    return arr;
}

void testCase(int caseType, const string& caseName, vector<int> arr) {
    comparisons = swaps = 0;
    vector<int> arr_copy = arr;

    try {
        auto start = high_resolution_clock::now();

        switch (caseType) {
        case 1:
            quicksort_first(arr_copy, 0, arr_copy.size() - 1);
            break;
        case 2:
            quicksort_median_fixed(arr_copy, 0, arr_copy.size() - 1);
            break;
        case 3:
            quicksort_median_random(arr_copy, 0, arr_copy.size() - 1);
            break;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        string type;

        cout << "|-------------------------|------------|-----------|-------------|---------|\n";

        // If you are wondering why I repeated the same prints, it is because I tried adjusting the alignment (does not always fully align)
        if (caseType == 1) {
            type = "First-Element";
            if (caseName == "Best") {
                cout << "| " << type << "           | " << caseName << "       | " << duration.count() << " ms     | " << comparisons << "     | " << swaps << "  |\n";
            }
            else if (caseName == "Worst") {
                cout << "| " << type << "           | " << caseName << "      | " << duration.count() << " ms  | " << comparisons << "  | " << swaps << "   |\n";
            }
            else {
                cout << "| " << type << "           | " << caseName << "    | " << duration.count() << " ms     | " << comparisons << "     | " << swaps << "  |\n";
            }
        }
        else if (caseType == 2) {
            type = "Median-Fixed";
            if (caseName == "Best") {
                cout << "| " << type << "            | " << caseName << "       | " << duration.count() << " ms     | " << comparisons << "     | " << swaps << "  |\n";
            }
            else if (caseName == "Worst") {
                cout << "| " << type << "            | " << caseName << "      | " << duration.count() << " ms     | " << comparisons << "     | " << swaps << "  |\n";
            }
            else {
                cout << "| " << type << "            | " << caseName << "    | " << duration.count() << " ms    | " << comparisons << "     | " << swaps << "  |\n";
            }
        }
        else {
            type = "Median-Random";
            if (caseName == "Best") {
                cout << "| " << type << "           | " << caseName << "       | " << duration.count() << " ms     | " << comparisons << "     | " << swaps << "  |\n";
            }
            else if (caseName == "Worst") {
                cout << "| " << type << "           | " << caseName << "      | " << duration.count() << " ms     | " << comparisons << "     | " << swaps << "  |\n";
            }
            else {
                cout << "| " << type << "           | " << caseName << "    | " << duration.count() << " ms    | " << comparisons << "     | " << swaps << "  |\n";
            }
        }

        // Verify sorting
        for (size_t i = 1; i < arr_copy.size(); i++) {
            if (arr_copy[i - 1] > arr_copy[i]) {
                cerr << "Sorting failed!" << endl;
                break;
            }
        }
    }
    catch (const exception& e) {
        cout << "Error: " << caseName << " (Type " << caseType << "): " << e.what() << endl;
    }
}

int main() {
    srand(time(0));
    const int n = 100000;

    cout << "\n=========================== Experimental Results ===========================\n";
    cout << "| Algorithm               | Case       | Time (ms) | Comparisons | Swaps   |\n";

    for (int i = 1; i <= 3; i++) {
        testCase(i, "Best", generateBestCase(n));
        testCase(i, "Worst", generateWorstCase(n));
        testCase(i, "Average", generateAverageCase(n));
    }

    cout << "============================================================================\n";

    cout << "\n\n=============================  Theoretical Analysis ============================= \n";
    cout << "General Analysis:-\n";
    cout << "   - Input Size: 10^5 = 100000\n";
    cout << "   - Basic Operation: Comparison\n";
    cout << "   - Is there Best, Worst, and Average Cases: Yes there is\n";
    cout << "   - Stable: No\n";
    cout << "   - In-place: Yes\n\n";

    cout << "1. First-Element Quicksort:-\n";
    cout << "   - Best Case: O(n log n)  -  When the pivot divides the array into equal parts\n";
    cout << "   - Recurrence: T(n) = 2T(n/2) + O(n)\n";
    cout << "   - Worst Case: O(n^2)  -  When it is already sorted\n";
    cout << "   - Recurrence: T(n) = T(n-1) + O(n)\n";
    cout << "   - Average Case: O(n log n)\n\n";

    cout << "2. Median-of-Three (Fixed) Quicksort:-\n";
    cout << "   - Best Case: O(n log n)\n";
    cout << "   - Worst Case: O(n log n)\n";
    cout << "   - Average Case: O(n log n)\n";
    cout << "   - Recurrence (for all cases): T(n) = 2T(n/2) + O(n)\n\n";

    cout << "3. Median-of-Three (Random) Quicksort:-\n";
    cout << "   - Best Case: O(n log n)\n";
    cout << "   - Worst Case: O(n log n)\n";
    cout << "   - Average Case: O(n log n)\n";
    cout << "   - Recurrence (for all cases): T(n) = 2T(n/2) + O(n)\n";

    cout << "================================================================================= \n";

    return 0;
}
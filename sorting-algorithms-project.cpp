#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

#ifdef _WIN32
#include <conio.h>  // For Windows
#else
#include <cstdlib>  // For Linux and macOS
#endif

using namespace std;
using namespace std::chrono;

// Function prototypes for sorting algorithms
pair<long long, long long> bubbleSort(vector<int>& arr);
pair<long long, long long> selectionSort(vector<int>& arr);
pair<long long, long long> insertionSort(vector<int>& arr);
void merge(vector<int>& arr, int left, int mid, int right);
pair<long long, long long> mergeSort(vector<int>& arr, int left, int right);
int partition(vector<int>& arr, int low, int high);
pair<long long, long long> quickSort(vector<int>& arr, int low, int high);
void heapify(vector<int>& arr, int n, int i, long long& comparisons);
pair<long long, long long> heapSort(vector<int>& arr);

// Function to clear the screen
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    // Assume Unix-like system
    system("clear");
#endif
}

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip> // For setw() and setfill()

using namespace std;
using namespace std::chrono;

void display_current_datetime() {
    // Get current system time
    auto now = system_clock::now();

    // Convert to time_t (C-style time type)
    time_t now_c = system_clock::to_time_t(now);

    // Convert to local time format
    char* dt = ctime(&now_c);

    // Print current date and time
    cout << "Current Date and Time: " << dt;
}

void display_menu() {
    clear_screen(); // Clear screen before displaying menu

    // Calculate the width for center alignment
    int menu_width = 50; // Adjust as needed

    // University Name
    string university_name = "International Islamic University Chittagong";
    int university_name_length = university_name.length();
    int padding_spaces = (menu_width - university_name_length) / 2;

    cout << string(menu_width, '*') << endl;
    cout << setw(padding_spaces + university_name_length) << university_name << endl;
    cout << string(menu_width, '*') << endl;
    cout << endl;

    // Developer Information
    cout << setw(menu_width) << left << "Developed by:" << endl;
    cout << setw(menu_width) << left << "MD YASIR SAMI" << endl;
    cout << setw(menu_width) << left << "Roll: C223024" << endl;
    cout << setw(menu_width) << left << "Section: 3EM" << endl;

    cout << endl;
    display_current_datetime(); // Display current date and time
    cout << endl;

    // Sorting Algorithms Menu
    cout << string(menu_width, '*') << endl;
    cout << setw(menu_width) << left << "Sorting Algorithms Menu:" << endl;
    cout << string(menu_width, '*') << endl;
    cout << setw(menu_width) << left << "1. Bubble Sort" << endl;
    cout << setw(menu_width) << left << "2. Selection Sort" << endl;
    cout << setw(menu_width) << left << "3. Insertion Sort" << endl;
    cout << setw(menu_width) << left << "4. Merge Sort" << endl;
    cout << setw(menu_width) << left << "5. Quick Sort" << endl;
    cout << setw(menu_width) << left << "6. Heap Sort" << endl;
    cout << setw(menu_width) << left << "7. Exit" << endl;
    cout << string(menu_width, '*') << endl;
}

// Function to get user choice for sorting algorithm
int get_user_choice() {
    int choice;
    cout << "Select a sorting algorithm (1-7): ";
    cin >> choice;
    while (choice < 1 || choice > 7) {
        cout << "Invalid choice. Please select a number between 1 and 7: ";
        cin >> choice;
    }
    return choice;
}

// Function to get user input list of integers
vector<int> get_user_list() {
    vector<int> arr;
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        arr.push_back(num);
    }
    return arr;
}

// Function to print the sorted array
void print_array(const vector<int>& arr) {
    cout << "Sorted array:";
    for (int num : arr) {
        cout << " " << num;
    }
    cout << endl;
}

// Function to print performance metrics
void print_performance(long long time, long long comparisons, long long swaps = 0) {
    cout << "Time taken: " << time << " milliseconds" << endl;
    cout << "Comparisons made: " << comparisons << endl;
    if (swaps > 0) {
        cout << "Swaps made: " << swaps << endl;
    }
}

// Bubble Sort
pair<long long, long long> bubbleSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();

    int n = arr.size();
    long long comparisons = 0, swaps = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparisons;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                ++swaps;
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    return make_pair(duration.count(), comparisons);
}

// Selection Sort
pair<long long, long long> selectionSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();

    int n = arr.size();
    long long comparisons = 0, swaps = 0;

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            ++comparisons;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            ++swaps;
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    return make_pair(duration.count(), comparisons);
}

// Insertion Sort
pair<long long, long long> insertionSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();

    int n = arr.size();
    long long comparisons = 0, swaps = 0;

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            ++comparisons;
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
        ++swaps;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    return make_pair(duration.count(), comparisons);
}

// Merge Sort
pair<long long, long long> mergeSort(vector<int>& arr, int left, int right) {
    auto start = high_resolution_clock::now();

    long long comparisons = 0, swaps = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;
        auto leftResult = mergeSort(arr, left, mid);
        auto rightResult = mergeSort(arr, mid + 1, right);
        comparisons += leftResult.second + rightResult.second;

        merge(arr, left, mid, right);
        // No swaps in merge sort

        comparisons += (right - left + 1); // Merge step comparisons

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        return make_pair(duration.count(), comparisons);
    } else {
        return make_pair(0, comparisons); // Already sorted
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Quick Sort
pair<long long, long long> quickSort(vector<int>& arr, int low, int high) {
    auto start = high_resolution_clock::now();

    long long comparisons = 0, swaps = 0;

    if (low < high) {
        int pi = partition(arr, low, high);
        auto leftResult = quickSort(arr, low, pi - 1);
        auto rightResult = quickSort(arr, pi + 1, high);
        comparisons += leftResult.second + rightResult.second;

        comparisons += (high - low + 1); // Partition step comparisons
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    return make_pair(duration.count(), comparisons);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

// Heap Sort
pair<long long, long long> heapSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();

    int n = arr.size();
    long long comparisons = 0, swaps = 0;

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, comparisons);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        ++swaps;
        heapify(arr, i, 0, comparisons);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    return make_pair(duration.count(), comparisons);
}

void heapify(vector<int>& arr, int n, int i, long long& comparisons) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        ++comparisons;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        ++comparisons;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        ++comparisons;
        heapify(arr, n, largest, comparisons);
    }
}

int main() {
    int choice;
    vector<int> arr;

    while (true) {
        display_menu();
        choice = get_user_choice();

        if (choice == 7) {
            break;
        }

        arr = get_user_list();

        pair<long long, long long> result;
        long long swaps = 0;

        switch (choice) {
            case 1:
                result = bubbleSort(arr);
                print_performance(result.first, result.second, swaps);
                break;
            case 2:
                result = selectionSort(arr);
                print_performance(result.first, result.second, swaps);
                break;
            case 3:
                result = insertionSort(arr);
                print_performance(result.first, result.second, swaps);
                break;
            case 4:
                result = mergeSort(arr, 0, arr.size() - 1);
                print_performance(result.first, result.second);
                break;
            case 5:
                result = quickSort(arr, 0, arr.size() - 1);
                print_performance(result.first, result.second);
                break;
            case 6:
                result = heapSort(arr);
                print_performance(result.first, result.second);
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }

        print_array(arr);

        cout << "Press any key to continue...";
#ifdef _WIN32
        _getch();
#else
        cin.ignore();
        cout << "\033c"; // ANSI escape sequence for clearing screen on Unix-like systems
#endif

        clear_screen();
    }

    cout << "Exiting program..." << endl;
    return 0;
}

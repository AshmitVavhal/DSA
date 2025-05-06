#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n;

    // Input the number of students
    cout << "Enter number of students: ";
    cin >> n;

    vector<int> marks(n);

    // Input the marks of each student
    cout << "Enter marks for each student: ";
    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }

    // Create max-heap and min-heap
    priority_queue<int> maxHeap(marks.begin(), marks.end());  // Max-heap for maximum marks
    priority_queue<int, vector<int>, greater<int>> minHeap(marks.begin(), marks.end());  // Min-heap for minimum marks

    // Get the maximum and minimum marks
    int maxMarks = maxHeap.top();
    int minMarks = minHeap.top();

    // Output the results
    cout << "Maximum marks: " << maxMarks << endl;
    cout << "Minimum marks: " << minMarks << endl;

    return 0;
}


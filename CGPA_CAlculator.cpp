#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cout << " CGPA Calculator \n";
    cout << "Enter number of courses: ";
    cin >> n;

    vector<string> grade(n);
    vector<int> credit(n);
    vector<double> gradePoint(n);

    double totalCredits = 0;
    double totalPoints = 0;

    for (int i = 0; i < n; i++) 
    {
        cout << "\nCourse " << i + 1 << endl;

        cout << "Enter Grade (O, A+, A, B+, B, C, P, F): ";
        cin >> grade[i];

transform(grade[i].begin(), grade[i].end(), grade[i].begin(), ::toupper);

        cout << "Enter Credit Hours: ";
        cin >> credit[i];

        if (grade[i] == "O")

            gradePoint[i] = 10;

        else if (grade[i] == "A+")

            gradePoint[i] = 9;

        else if (grade[i] == "A")

            gradePoint[i] = 8;

        else if (grade[i] == "B+")

            gradePoint[i] = 7;

        else if (grade[i] == "B")

            gradePoint[i] = 6;

        else if (grade[i] == "C")

            gradePoint[i] = 5;

        else if (grade[i] == "P")

            gradePoint[i] = 4;

        else

            gradePoint[i] = 0;

        totalCredits += credit[i];

        totalPoints += gradePoint[i] * credit[i];
    }

    double cgpa = totalPoints / totalCredits;

    cout << "\nResult \n";

    cout << left << setw(10) << "Course"

         << setw(10) << "Grade"

         << setw(10) << "Credit"

         << setw(10) << "Point" << endl;

    for (int i = 0; i < n; i++)
     {
        cout << left << setw(10) << i + 1

             << setw(10) << grade[i]

             << setw(10) << credit[i]

             << setw(10) << gradePoint[i] << endl;
    }

    cout << "\nTotal Credits : " << totalCredits << endl;
    cout << "CGPA : " << fixed << setprecision(2) << cgpa << endl;

    return 0;
}
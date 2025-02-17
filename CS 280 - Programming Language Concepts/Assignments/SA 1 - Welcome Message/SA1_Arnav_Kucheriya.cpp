#include <iostream>
#include <string>
using namespace std;

int main() {
    // Display the initial message
    cout << "Welcome to CS 280 (Spring 2025)" << endl;

    // Prompt for user input
    cout << "What are your first name, last name, and section number?" << endl;

    // Declare variables to store input
    string firstName, lastName;
    int sectionNumber;

    // Read input from the user
    cin >> firstName >> lastName >> sectionNumber;

    // Display the welcome message
    cout << "Hello " << firstName << ", Welcome to CS 280 Section " << sectionNumber << "." << endl;

    return 0;
}

#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

struct Violation {
    string description;
    double fine;
    string date;

    Violation(string desc, double f, string d) : description(desc), fine(f), date(d) {}
};

map<string, vector<Violation>> database;

void addViolation(string carNumber, string description, double fine, string date) {
    database[carNumber].push_back(Violation(description, fine, date));
}

void printDatabase() {
    for (const auto& pair : database) {
        cout << "Car number: " << pair.first << endl;
        for (const auto& violation : pair.second) {
            cout << "Violation: " << violation.description << ", Fine: " << violation.fine << ", Date: " << violation.date << endl;
        }
    }
}

void printViolationsForCar(const string& carNumber) {
    if (database.count(carNumber) > 0) {
        for (const auto& violation : database[carNumber]) {
            cout << "Violation: " << violation.description << ", Fine: " << violation.fine << ", Date: " << violation.date << endl;
        }
    }
    else {
        cout << "No violations for car number: " << carNumber << endl;
    }
}

double calculateTotalFineForCar(const string& carNumber) {
    double totalFine = 0.0;
    if (database.count(carNumber) > 0) {
        for (const auto& violation : database[carNumber]) {
            totalFine += violation.fine;
        }
    }
    return totalFine;
}

void payFineForCar(const string& carNumber) {
    if (database.count(carNumber) > 0) {
        database[carNumber].clear();
    }
}

int compareDates(const string& date1, const string& date2) {
    int year1, month1, day1, year2, month2, day2;
    sscanf_s(date1.c_str(), "%d-%d-%d", &year1, &month1, &day1);
    sscanf_s(date2.c_str(), "%d-%d-%d", &year2, &month2, &day2);

    if (year1 != year2)
        return year1 - year2;
    else if (month1 != month2)
        return month1 - month2;
    else
        return day1 - day2;
}

void searchViolationsForPeriod(const string& startDate, const string& endDate) {
    for (const auto& pair : database) {
        cout << "Car number: " << pair.first << endl;
        for (const auto& violation : pair.second) {
            if (compareDates(violation.date, startDate) >= 0 && compareDates(violation.date, endDate) <= 0) {
                cout << "Violation: " << violation.description << ", Fine: " << violation.fine << ", Date: " << violation.date << endl;
            }
        }
    }
}

int main() {
    int choice;
    string carNumber, startDate, endDate;

    while (true) {
        cout << "1. Print database\n";
        cout << "2. Print violations for a car\n";
        cout << "3. Calculate total fine for a car\n";
        cout << "4. Pay fine for a car\n";
        cout << "5. Search violations for a period\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printDatabase();
            break;
        case 2:
            cout << "Enter car number: ";
            cin >> carNumber;
            printViolationsForCar(carNumber);
            break;
        case 3:
            cout << "Enter car number: ";
            cin >> carNumber;
            cout << "Total fine for car " << carNumber << ": " << calculateTotalFineForCar(carNumber) << endl;
            break;
        case 4:
            cout << "Enter car number: ";
            cin >> carNumber;
            payFineForCar(carNumber);
            break;
        case 5:
            cout << "Enter start date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter end date (YYYY-MM-DD): ";
            cin >> endDate;
            searchViolationsForPeriod(startDate, endDate);
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
        system("cls");
    }

    return 0;
}

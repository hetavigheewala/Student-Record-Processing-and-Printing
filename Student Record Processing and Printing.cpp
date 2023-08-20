

/// @brief This program explores structures

// preprocessor directives
// library includes
#include <iostream>
#include <fstream>
#include <iomanip>

// set namespace
using namespace std;

// Global constant definition(s)
const int SCORE_CNT = 5;            // the number of scores
const int STUDENT_CNT = 6;          // the number of students

// Data type definition(s) (aliases)


// Structure definition(s)
struct oneScore_t {
    string lName;
    string fName;
    int score = 0;
};

struct student_t {
    string lName;
    string fName;
    int scores[SCORE_CNT] = {0};
};


/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
void printRecord(const oneScore_t record);
void printRecord(const student_t record);
student_t getRecord();
void printRecord(const student_t records[]);
bool populateStudentData(const string& FN, student_t records[]);


/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Local constant definition(s)
    const string SEP = string(15, '-');    // line separator for section titles
    const string FN = "studentData.csv";   // data file

    // Variable declaration(s)
    int exitState;              // tracks the exit code for the process
    exitState = EXIT_SUCCESS;   // set state to successful run

    oneScore_t student1;                // student for section 2.1
    oneScore_t student2;                // student for section 2.2
    student_t student3;                 // student for section 3
    student_t student4;                 // student for section 4
    student_t students[STUDENT_CNT];    // array of student records

    // Section 2.1
    // populate record
    student1.fName = "Bugs";
    student1.lName = "Bunny";
    student1.score = 96;

    cout << endl;
    cout << "Section 2.1\n"
    << SEP << endl;

    printRecord(student1);
    cout << endl;

    // Section 2.2
    cout << "Section 2.2\n"
    << SEP << endl;

    printRecord(student2);
    cout << endl;

    // Section 3.1
    cout << "Section 3.1\n"
    << SEP << endl;

    // print default information in record
    printRecord(student3);
    cout << endl;

    // populate record
    student3.fName = "Bugs";
    student3.lName = "Bunny";
    student3.scores[0] = 72;
    for (int i = 1; i < SCORE_CNT; ++i) {
        student3.scores[i] = student3.scores[i - 1] + 5;
    }

    // print populated record
    printRecord(student3);
    cout << endl;

    // Section 4
    cout << "Section 4\n"
    << SEP << endl;

    student4 = getRecord();
    printRecord(student4);
    cout << endl;

    // Section 5
    cout << "Section 5\n"
    << SEP << endl;

    students[0] = getRecord();          // populate first record in array
    printRecord(students[0]);           // print the record
    cout << endl;

    // Section 6
    cout << "Section 6\n"
    << SEP << endl;

    printRecord(students);

    if (populateStudentData(FN, students)) {
        cout << endl;
        printRecord(students);
        cout << endl;
    } else {
        cout << "Unable to open file..." << endl;
    }


    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/// This function prints the contents of a variable of type oneScore_t
/// @param record is the data set to be printed
void printRecord(const oneScore_t record) {
    cout << record.fName << endl
    << record.lName << endl
    << record.score << endl
    << endl;
}


/// This function prints the contents of a variable of type student_t
/// @param record is the data set to be printed
void printRecord(const student_t record) {
    cout << record.fName << endl
    << record.lName << endl;

    for (int i = 0; i < SCORE_CNT; ++i) {       // output the scores
        cout << record.scores[i] << endl;
    }
}

/// This function is a struct factory to return a single student
/// with populated data
/// @return a single student in a structure
student_t getRecord() {
    student_t student;

    student.fName = "Bugs";
    student.lName = "Bunny";
    student.scores[0] = 72;
    for (int i = 1; i < SCORE_CNT; ++i) {
        student.scores[i] = student.scores[i - 1] + 5;
    }
    return student;
}

void printRecord(const student_t records[]) {
    int recordIdx = 0;
    string name;        // holds the name string for output

    while (recordIdx < STUDENT_CNT) {
        // concatenate the last and first name to make output formatting
        // easier, then print the name
        name = records[recordIdx].lName + ", " + records[recordIdx].fName;
        cout << left << setw(18) << name << ": ";

        // print the scores
        cout << right;
        for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
            cout << setw(3) << records[recordIdx].scores[scoreIdx];
        }
        cout << endl;

        // increment record pointer
        recordIdx++;
    }
}

/// This function reads a file containing student data.
/// @param FN is the name of the comma delimited file
/// @param records is the data model that will receive the student records
/// @returns true if successful, otherwise false
bool populateStudentData(const string& FN, student_t records[]) {
    bool didOpen = true;    // success flag
    ifstream fin;           // declare the file stream handler
    int record;             // current record from file

    fin.open(FN);           // attempt to open the data file

    // If the file was successfully opened...
    if (fin.is_open()) {
        record = 0;

        // loop through all the records in the file
        // extract the data and place in data model
        while (record < STUDENT_CNT) {
            getline(fin, records[record].lName, ',');  // get the last name
            getline(fin, records[record].fName, ',');  // get the first name

            // get student scores
            for (int scoreIdx = 0; scoreIdx < SCORE_CNT; ++scoreIdx) {
                fin >> records[record].scores[scoreIdx];
                fin.ignore();
            }
            // increment record pointer
            record++;
        }
    } else {    // the file wasn't open
        didOpen = false;
    }

    fin.close();

    return didOpen;
}
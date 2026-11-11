/* using a BST for efficient insertion and searching.
Using a stack to maintain search history because it
follows the LIFO (Last In First Out) principle.
The most recently searched student will be removed first.

time complexity: 
searching, insertion and deletion takes O(logn) average and worst case is O(n)
displaying takes O(n) while displaying a singular student takes O(1)
search history takes O(n) while removal of a record takes O(1)
*/
#include <iostream>
#include <string>
#include <stack>
using namespace std;

// node of a BST
struct Node{
    int roll;
    int semester;
    string name;
    string dept;

    Node *left;
    Node *right;
    Node(int val1, int val2, string val3, string val4){
        roll = val1;
        semester = val2;
        name = val3;
        dept = val4;
        left = nullptr;
        right = nullptr;
    }
};

//search function for bst
Node* search(Node* root , int id){
    if(root == nullptr || root->roll == id){
        return root;
    }
    if(id < root->roll){
        return search(root->left, id);
    }
    return search(root->right, id);
}
//insert function for bst
Node* insert(Node* root, int rollno,int sem, string sname, string sdept){
    if(root == nullptr){
        Node *newNode = new Node(rollno, sem, sname, sdept);
        return newNode;
    }
    if(rollno < root->roll){
        root->left = insert(root->left, rollno, sem, sname, sdept);

    }
    else if(rollno > root->roll){
        root->right = insert(root->right, rollno, sem, sname, sdept);
    }
    return root;
}
//display all students
void displayAll(Node* root){
    if(root == nullptr){
        return;
    }
    displayAll(root->left);

    cout << "\n Roll #: " << root->roll;

    cout << "\n Name: " << root->name;
    cout << "\n Semester: " << root->semester;
    cout << "\n Department: " << root->dept;
    cout << endl;

    displayAll(root->right);
}
void displayStudent(Node* student){
    if(student == nullptr){
        cout << "Student does not exist";
        return;
    }

    cout << "\nStudent Information";
    cout << "\nRoll #: " << student->roll;
    cout << "\nName: " << student->name;
    cout << "\nSemester: " << student->semester;
    cout << "\nDepartment: " << student->dept;

}
// to implement deletion, we need min node first/
Node* findMin(Node* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}
//deleting student function
Node* deleteNode(Node* root, int rollno) {
    // Node not found
    if (root == nullptr) {
        return nullptr;
    }
    // Search in left subtree
    if (rollno < root->roll) {
        root->left = deleteNode(root->left, rollno);
    }
    // Search in right subtree
    else if (rollno > root->roll) {
        root->right = deleteNode(root->right, rollno);
    }
    // Node found
    else {
        // case1: no children
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // case2: only right child
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // case3: only left child
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // case4: two children
         else {
            Node* temp = findMin(root->right);

            root->roll = temp->roll;
            root->name = temp->name;
            root->dept = temp->dept;
            root->semester = temp->semester;

            root->right = deleteNode(root->right, temp->roll);

            return root;
        }
    }
    return root;
}
//delete every Node
void clearMemory(Node* root){
    if(root == nullptr){
        return;
    }
    clearMemory(root->left);
    clearMemory(root->right);
    delete root;
}
//use a stack to display search history
void searchHistory(stack<int> history){
    if(history.empty()){
        cout << "No search history";
        return;
    }
    cout << "----Search History----" << endl;
    while(!history.empty()){
        cout << "Rollno: " << history.top() << endl;
        history.pop();
    }
}
//remove the most recent search
void removeHistory(stack<int>& history) {
    if (history.empty()) {
        cout << "Search history is empty!\n";
        return;
    }
    cout << "Removing history entry: " << history.top() << endl;
    history.pop();
    cout << "History entry removed successfully!\n";
}
int main() {
    Node* root = nullptr;
    stack<int> history;

    int choice;
    int rollno, semester;
    int searchRoll;
    string name, dept;

    do {
        cout << "\n\n------ STUDENT HELP DESK ------";
        cout << "\n1. Add Student";
        cout << "\n2. Search Student";
        cout << "\n3. Display All Students";
        cout << "\n4. Display Search History";
        cout << "\n5. Remove Latest Search History";
        cout << "\n6. Delete Student";
        cout << "\n7. Exit";
        cout << "\n\nEnter your choice: ";
        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number.";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (choice) {
            // add student 
            case 1: {
                cout << "\nEnter Roll Number: ";
                cin >> rollno;
                // Check for duplicate roll number
                if (search(root, rollno) != nullptr) {
                    cout << "\nRoll number already exists!";
                    break;
                }
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, name);

                cout << "Enter Semester: ";
                cin >> semester;
                cin.ignore();

                cout << "Enter Department: ";
                getline(cin, dept);
                root = insert(root, rollno, semester, name, dept);

                cout << "\nStudent added successfully!";
                break;
            }
            // search student
            case 2: {
                cout << "\nEnter Roll Number to search: ";
                cin >> searchRoll;
                Node* student = search(root, searchRoll);

                if (student == nullptr) {
                    cout << "\nStudent not found!";
                }
                else {
                    displayStudent(student);
                    // Push successful search into history
                    history.push(searchRoll);
                    cout << "\n\nSearch added to history!";
                }
                break;
            }
            // display all students
            case 3: {
                if (root == nullptr) {
                    cout << "\nNo students registered yet!";
                }
                else {
                    cout << "\n========== ALL STUDENTS ==========";
                    displayAll(root);
                }
                break;
            }
            // display search history
            case 4: {
                searchHistory(history);
                break;
            }
            // remove latest record from history
            case 5: {
                removeHistory(history);
                break;
            }
            // delete student
            case 6: {
                cout << "\nEnter Roll Number to delete: ";
                cin >> rollno;

                if (search(root, rollno) == nullptr) {
                    cout << "\nStudent not found!";
                }
                else {
                    root = deleteNode(root, rollno);
                    cout << "\nStudent deleted successfully!";
                }
                break;
            }
            case 7: {
                    cout << "\nExiting Student Help Desk...";
                break;
            }
            //if wrong choice
            default: {
                cout << "\nInvalid choice! Please try again.";
            }
        }
    } while (choice != 7);

    // delete memory
    clearMemory(root);
    root = nullptr;

    cout << "\nMemory released successfully!";
    cout << "\nThank you for using Student Help Desk!\n";
    return 0;
}
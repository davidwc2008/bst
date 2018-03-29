/*
David Chen (with help from Vikram Kashyap)
C++ 2018
Binary Search Tree Program
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <queue>

using namespace std;

struct Node {
  int value;
  Node* left = NULL;
  Node* right = NULL;

  Node(int num) { //node constructor
    value = num;
  }
};

//function prototypes
void add(Node *& root, int num);
void print(Node * root);
bool search(Node *& root, int num);
void remove(Node *& root, int num);

int main() {
  Node* root = NULL;
  char method;
  char fileName[30];
  
  cout << "Welcome to the Binary Search Tree Program.  Would you like to enter a series of numbers (S) or the name of a file (F)?" << endl;
  cin >> method;

  if (method =='S') {
    cout << "Enter number.  Enter 0 when you are finished." << endl;
    //code to add to tree for console input
    bool done = false;
    while(!done) {
      int val;
      cin >> val;
      if (val == 0) {
	done = true;
      } else {
	add(root, val);
      }
    }
  } else if (method == 'F') {
    //code to add to tree from file input
    ifstream inFile;
    cout << "What is the name of the file?" << endl;
    cin >> fileName;
    inFile.open(fileName);
    if(!inFile) {
      cout << "Error: No such file." << endl;
      return 0;
    }

    bool done = false;
    while(!done) {
      int val;
      inFile >> val;
      if (val == 0) {
        done = true;
      } else {
        add(root, val);
      }
    }

    inFile.close();
  } else {
    cout << "Error: Invalid Input Method." << endl;
    return 0;
  }

  while (method != 'Q') {
    cout << "Available commands: Search (S), Print (P), Remove (R), Quit (Q).  Enter your command: " << endl;
    cin >> method;

    if (method == 'S') {
      int val;
      cout << "Enter value: " << endl;
      cin >> val;
      if (search(root, val) == true) {
	cout << "That number is in the tree." << endl;
      } else {
	cout << "It is not in the tree." << endl;
      }
    }
    
    if (method == 'P') {
      print(root);
    }

    if (method == 'R') {
      int val;
      cout << "What number would you like to remove?" << endl;
      cin >> val;
      remove(root, val);
    }
    
  }

  return 0;
}

void add(Node *& root, int num) {
  if (root == NULL) {
    root = new Node(num); //new returns a pointer
  } else if (root->value > num) {
    add(root->left, num);
  } else if (root->value < num) {
    add(root->right, num);
    }
}

void print(Node * root) {
  queue<Node*> queue; //creates a queue to print the tree (First in first out data structure)
  queue.push(root);
  bool moredata = true;
  while (moredata) {
    moredata = false;
    int levelsize = queue.size();
    int counter = 0;
    while (counter != levelsize) {
      Node* current = queue.front();
      queue.pop();
      counter++;
      if (current == NULL) {
	cout << "-,";
	queue.push(NULL);
	queue.push(NULL);
      } else {
	cout << current->value << ",";
	moredata = true;
	queue.push(current->left);
	queue.push(current->right);
      }
    }
    cout << endl;
  }
  
}

bool search(Node *& root, int num) {
  if (root == NULL) { //the subtree is empty
    return false;
  } else if (root->value == num) {
    return true;
  } else if (root->value > num) {
      return search(root->left, num);
  } else if (root->value < num) {
      return search (root->right, num);
  }
}

void remove(Node *& root, int num) {
  if (search(root, num) == true) {
    if (num < root->value) {
      remove(root->left, num);
    } else if (num > root->value) {
      remove(root->right, num);
    } else {
      //leaf case
      if ((root->right == NULL) && (root->left == NULL)) {
	delete root;
	root = NULL;
      }
      //internal node with only left child
      else if ((root->right == NULL)) {
	Node* todelete = root;
	root = root->left;
	delete todelete;
      }
      //internal node with only right child
      else if ((root->left == NULL)) {
        Node* todelete = root;
        root = root->right;
        delete todelete;
      }
      //internal node has two children
      else {
	//find in order successor
	Node* successor = root->right;
	while (successor->left != NULL) {
	  successor = successor->left;
	}
	root->value = successor->value;
	remove(root->right, successor->value);
      }
    }
  } else {
    cout << "Cannot remove.  The number is not present." << endl;
  }
}

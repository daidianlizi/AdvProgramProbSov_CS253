#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#define EMPTY_VALUE -2147483648
using namespace std;

int RightChild(int index, int treelength) {
    if (2 * index < treelength) {
        return 2 * index;
    }
    return -1;
}
int LeftChild(int index, int treelength) {
    if (2 * index -1 < treelength) {
        return 2 * index - 1;
    }
    return -1;
}
void padtabs(int tabtimes) {
    for (int i = 0; i < tabtimes; i++) {
        cout << '\t';
    }
}
void DisplayTreeLeftRotation90(vector<int> sequencetree, int index, int level) {
    //rightchild, root, leftchild traverse
    int treelength = sequencetree.size();
    int rchild = RightChild(index + 1, treelength);
    int lchild = LeftChild(index + 1, treelength);
    if (rchild > 0) {
        DisplayTreeLeftRotation90(sequencetree, rchild, level+1);
    }

    padtabs(level);
    if (sequencetree[index] != EMPTY_VALUE)
        cout << sequencetree[index]<<endl;
    else 
        cout << "null" <<endl;
    
    if (lchild > 0) {
        DisplayTreeLeftRotation90(sequencetree, lchild, level+1);
    }
}
void DisplayTree(vector<int> &sequencetree) {
    DisplayTreeLeftRotation90(sequencetree, 0, 0);
}
void ModifyTree(vector<int> &sequencetree, int index) {
    //root, leftchild, rightchild traverse
    int treelength = sequencetree.size();
    int lchild = LeftChild(index + 1, treelength);
    int rchild = RightChild(index + 1, treelength);
    if (sequencetree[index] != EMPTY_VALUE) {
        sequencetree[index] *= 10;
    }
    if (lchild > 0) {
        ModifyTree(sequencetree, lchild);
    }
    if (rchild > 0) {
        ModifyTree(sequencetree, rchild);
    }
}
void LoadBinaryTreeFile (string infile, vector<int> &sequencetree) {
    ifstream in;
    in.open(infile);
    int treelength;
    in >> treelength;
    int data;
    for (int i = 0; i < treelength; i++) {
        in >> data;
        sequencetree.push_back(data);
    }
    in.close();
}
void SaveBinaryTreeFile (string outfile, vector<int> &sequencetree) {
    ofstream out;
    out.open(outfile);
    out << sequencetree.size() << endl;
    for (int data : sequencetree) {
        out << data << endl;
    }
    out.close();
}
int main(int argc, char *argv[]) {
    vector<int> sequencetree;
    
    LoadBinaryTreeFile(argv[1], sequencetree);
    cout << "Tree loaded"<<endl;
    DisplayTree(sequencetree);

    ModifyTree(sequencetree, 0);

    SaveBinaryTreeFile(argv[2], sequencetree);
    cout << "Tree saved after modification"<<endl;
    DisplayTree(sequencetree);
    
    return 0;
}

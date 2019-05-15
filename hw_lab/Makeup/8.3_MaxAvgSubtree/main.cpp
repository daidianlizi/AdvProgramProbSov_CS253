#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
using namespace std;
vector<int> binarytree;
struct Result {
    int sum;
    int count;
};
float resultmaxaverage = INT_MIN;
int resultindex  = -1;

int LeftChild(int indexi){
    if (indexi * 2 - 1 < binarytree.size()) 
        return indexi * 2 - 1;
    return 0;
}
int RightChild(int indexi){
    if (indexi * 2 < binarytree.size()) 
        return indexi * 2;
    return 0;
}
struct Result FindMaxAverageSubtree(int indexi){
    // renew sumbinarytree, countbinarytree
    ////cout<<"processing #"<<indexi<<endl;
    // divide:
    int lchild = LeftChild(indexi + 1 );
    int rchild = RightChild(indexi + 1);
    struct Result lresult, rresult, result;

    if (lchild) {
        lresult = FindMaxAverageSubtree(lchild);
    } else {
        lresult.sum = 0;
        lresult.count = 0;
    }

    if (rchild) {
        rresult = FindMaxAverageSubtree(rchild);
    } else {
        rresult.sum = 0;
        rresult.count = 0;
    }
    
    // conquer:
    result.sum = binarytree[indexi] + lresult.sum + rresult.sum;
    result.count = 1 + lresult.count + rresult.count;
    if (resultmaxaverage <= result.sum * 1.0 / result.count) {//since =, prefer to the lower level node
        resultmaxaverage = result.sum * 1.0 / result.count;
        resultindex = indexi;
        ////cout<<"changed at #"<<indexi<<": "<<binarytree[indexi]<<" with sum = "<<result.sum<<" and count = "<<result.count<<endl;
    }
    ////cout<<"return #"<<indexi<<endl;
    return result;
}
void ConstructTree(string filename) {
    ifstream in;
    in.open(filename);
    int treelength;
    in>> treelength;
    int data;
    bool coutflag = 1;
    if (coutflag) {
        cout << "input number: "<< treelength<<endl;
    }
    for (int i = 0; i < treelength; i++) {
        in >> data;
        if (coutflag) {
            cout << i << ": "<< data<<endl;
        }
        binarytree.push_back(data);
    }
    return;
}
int main(int argc, char *argv[]) {
    ConstructTree(argv[1]);
    FindMaxAverageSubtree(0);
    cout << "maximum_average_subtree is at node #" << resultindex << ": value "<< binarytree[resultindex]
         <<" with average of " << resultmaxaverage << endl;
    return 0;
}

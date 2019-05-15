#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>
#include <utility>
using namespace std;
#include <cstdint>
#include <climits>


class node{
public:
    float x;
    float y;
    node(float a, float b){
        x = a;
        y = b;
    }
};
class cluster{
public:
    int idc;
    vector<node> nds;
    cluster(int i, float a, float b){
        idc = i;
        node t(a,b);
        nds.push_back(t);
    }
};

int n_nodes;
int n_clusters;
vector<cluster> dataset;
vector<vector<float>> dTable;
int countcluster = 0;

float IniEuclideanDis(cluster u, cluster v){
    return sqrt( pow((u.nds[0].x - v.nds[0].x),2) + pow((u.nds[0].y - v.nds[0].y),2));
}
void InitialDistanceTable(){
    for (int i = 0; i < n_nodes; i++){
        vector<float> tmp;
        for (int j = 0; j < n_nodes; j++){
            if (j > i)
                tmp.push_back( IniEuclideanDis(dataset[i], dataset[j]) );
            else if (j < i)
                tmp.push_back( dTable[j][i] );
            else
                tmp.push_back(0);// i == j
        }
        dTable.push_back(tmp);
    }
    cout<<"InitialDistanceTable done."<<endl;
}
void FindClosestCluster(int &mi, int &mj, float &minDt){
    for(int i=0;i<dTable.size();i++){ // range for j in dTable.size() is changing.
        for(int j=i+1;j<dTable[i].size();j++){
             if(dTable[i][j]<minDt){
                minDt = dTable[i][j];
                mi = i;
                mj = j;
            }
         }
    }
    ///cout<<mi<<"-mi,   mj:"<<mj<<endl;
    cout<<"FindClosestCluster done."<<endl;
}
void MergeMJtoMI(int mi, int mj){
    for (int k = 0; k < dataset[mj].nds.size(); k++){
        dataset[mi].nds.push_back(dataset[mj].nds[k]);
    }
    cout<<"MergeMJtoMI done."<<endl;
}
void RemoveMJinDataset(int mj){
    vector<cluster>::iterator imj = dataset.begin();
    ///cout<<mj<<endl;
    imj += mj;
    dataset.erase(imj);
    cout<<"RemoveMJinDataset done."<<endl;
}
void UpdateDistanceTable(int mi, int mj){
    for (int k = 0; k < dTable.size(); k++){
        if (k == mi || k == mj) continue;//why not to 0?
        if (dTable[mi][k] > dTable[mj][k]){
            dTable[mi][k] = dTable[mj][k];
            dTable[k][mi] = dTable[mj][k];
        }
    }
    cout<<"UpdateDistanceTable done."<<endl;
}
void RemoveMJindTable(int mj){
    //rm whole row of mj
    vector<vector<float>>::iterator rowj = dTable.begin();
    rowj += mj;
    dTable.erase(rowj);
    //rm all column of mj;
    for (int k = 0; k < dTable.size(); k++){
        vector<float>::iterator kcolj = dTable[k].begin();
        kcolj += mj;
        dTable[k].erase(kcolj);
    }
    cout<<"RemoveMJindTable done."<<endl;
}
void SaveResult(){
    fstream outfile;
    //outfile.open("clustering.txt", ios::out);
    outfile.open("clustering.csv", ios::out);
    for (int i = 0; i < dataset.size(); i++){
        for (int j = 0; j < dataset[i].nds.size();j++){
            //outfile<<i+1<<"  "<<dataset[i].nds[j].x <<"  " << dataset[i].nds[j].y <<endl;
            outfile<<i+1<<","<<dataset[i].nds[j].x <<"," << dataset[i].nds[j].y <<endl;
        }
    }
    outfile.close();
    cout << "\nn_clusters in result: "<< dataset.size()<<" among "<<n_nodes<<endl;
}
vector<cluster> MyReadFile(string infile){
    ifstream in;
    in.open(infile);
    if (!in){
        cout <<"Open File Failed!" <<endl;
        vector<cluster> a;
        return a;
    }
    vector<cluster> data;
    in >> n_nodes;
    in >> n_clusters;
    for (int j = 0; j < n_nodes; j++){
        int i;
        float x, y;
        in >> i>>x>>y;
        cout<<i<<" "<<x<<" "<<y<<endl;
        cluster p(i,x,y);
        data.push_back(p);
    }
    in.close();   
    cout<<"Read data successfully!"<<endl;
    return data;
}
void HierarchicalClustering(){
    InitialDistanceTable();
    while (dataset.size() > n_clusters){
        countcluster++;
        cout<<"\ncount cluster times: "<<countcluster<<endl;
        //find and merge two closest clusters, by shortest distance in dTable;
        float minDt = INT_MAX;
        int mi, mj;
        FindClosestCluster(mi, mj, minDt);
        ///cout<<mi<<"-mi,   mj:"<<mj<<endl;
        //merge mj into mi;
        MergeMJtoMI(mi, mj);
        ///cout<<mi<<"-mi,   mj:"<<mj<<endl;
        //rm the originial mj in dataset;
        ///cout<<mi<<"-mi,   mj:"<<mj<<endl;
        RemoveMJinDataset(mj);
        //update dTable;
        UpdateDistanceTable(mi,mj);
        //rm row of mj and column of mj in dTable;
        RemoveMJindTable(mj);
    }
}
int main() {
    string infile = "input.txt";
    //string infile = "spiral_format.txt";
    //string infile = "aggregation_format.txt";
    //string infile = "Pathbased_format.txt";
    dataset = MyReadFile(infile);
    HierarchicalClustering();
    //save result as txt in the format of ;
    SaveResult();
    return 0;
}

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

const int INF = 1000000000;

struct ListNode{
    int v; //edge to v from the index u in the List
    int weight; //weight from u to v
    ListNode(int v, int weight): v(v), weight(weight){}
    ListNode(){}
};
struct CodiNode{
    int x; //x coordinate in 2D plane
    int y; //y coordinate in 2D plane
    CodiNode(int x, int y): x(x), y(y){}
    CodiNode(){}
};

int PrimMST(int n_nodes, int start, vector< vector<ListNode> > Adj, vector<bool> &visit, vector<int> &costexpand){
    fill(costexpand.begin(), costexpand.end(), INF);
    costexpand[start] = 0;
    int sum = 0;
    //loop for all the nodes
    for (int i = 0; i < n_nodes; i++){
        //find the smallest in Set visited
        int u = -1;
        int MIN = INF;
        for (int j = 0; j < n_nodes; j++){
            if (visit[j] == false && costexpand[j] < MIN){
                u = j;
                MIN = costexpand[j];
            }
        }
        //cout<<"u: "<<u<<endl;
        if (u == -1)
            return -1;
        //find the nearest adjacent edge
        visit[u] = true;
        //cout<<"sum+="<<costexpand[u]<<endl;
        sum += costexpand[u];
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;
            int weight = Adj[u][j].weight;
            //cout<<(costexpand[u] + weight)<<" "<<costexpand[v]<<endl;
            if (visit[v] == false && weight < costexpand[v]){
                costexpand[v] = weight;
            }
        }
    }
    return sum;
}

int main() {
    ifstream in("input.txt");
    int n_nodes;
    in >> n_nodes;
    cout<<n_nodes<<endl;
    //get the input to create the adjacent list
    vector< vector<ListNode> > Adj(n_nodes);
    vector<CodiNode> Coo(n_nodes);
    for (int j = 0; j < n_nodes; j++){
        string str;

        my_getline(in,str);
        if ( str.empty() )

        cout<<"coor str: "<<str<<endl;
        int size_str = str.size();
        cout<<"coor str size: "<<size_str<<endl;
        char uchar;
        str[0] = uchar;
        cout<<uchar<<endl;
        int u = uchar - 'A';
        int ux, uy;//coordinate
        ux = atoi(&str[2]);
        uy = atoi(&str[4]);
        cout<<ux<<" "<<uy<<endl;
        Coo[u].x = ux;
        Coo[u].y = uy;

        getline(in,str);
        cout<<"link str: "<<str<<endl;
        size_str = str.size();
        cout<<"link str size: "<<size_str<<endl;
        //char vchar;
        for (int i=0;i < size_str;i++)
        {
            if ( isalpha(str[i]) ){
                cout<<str[i]<<" ";
                int v = str[i] - 'A';
                Adj[u-1].push_back(ListNode(v-1,-1));
                Adj[v-1].push_back(ListNode(u-1,-1));
            }
        }
    }

    vector<bool> visit(n_nodes);
    vector<double> costexpand(n_nodes);
    vector<double> distance(n_nodes);
    //int ans = PrimMST(n_nodes, 0, Adj, visit, costexpand);
    int ans = 0;
    cout << "the MST weights sum is: " << ans << endl;
    in.close();
    return 0;
}

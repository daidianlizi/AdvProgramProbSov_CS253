#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
using namespace std;

const int INF = 1000000000;

struct ListNode{
    int v; //edge to v from the index u in the List
    int weight; // weight from u to v
    ListNode(int v, int weight): v(v), weight(weight){}
};

int PrimMST(int n_nodes, int start, vector<vector<ListNode>> Adj, vector<bool> &visit, vector<int> &distance){
    fill(distance.begin(), distance.end(), INF);
    distance[start] = 0;
    int sum = 0;
    //loop for all the nodes
    for (int i = 0; i < n_nodes; i++){
        //find the smallest in Set visited
        int u = -1;
        int MIN = INF;
        for (int j = 0; j < n_nodes; j++){
            if (visit[j] == false && distance[j] < MIN){
                u = j;
                MIN = distance[j];
            }
        }
        //cout<<"u: "<<u<<endl;
        if (u == -1)
            return -1;
        //find the nearest adjacent edge
        visit[u] = true;
        //cout<<"sum+="<<distance[u]<<endl;
        sum += distance[u];
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;
            int weight = Adj[u][j].weight;
            //cout<<(distance[u] + weight)<<" "<<distance[v]<<endl;
            if (visit[v] == false && weight < distance[v]){
                distance[v] = weight;
            }
        }
    }
    return sum;
}

int main() {
    ifstream in;
    in.open("input.txt");
    int T;
    in >> T;
    //loop the cases
    for (int i = 0; i < T; i ++) {
        int n_nodes;
        in >> n_nodes;
        int n_edges;
        in >> n_edges;
        //get the input to create the adjacent list
        vector<vector<ListNode>> Adj(n_nodes);

        for (int j = 0; j < n_edges; j++){
            int u, v, weight;
            in>>u;
            in>>v;
            in>>weight;
            Adj[u-1].push_back(ListNode(v-1,weight));
            Adj[v-1].push_back(ListNode(u-1,weight));
        }

        vector<bool> visit(n_nodes);
        vector<int> distance(n_nodes);
        int ans = PrimMST(n_nodes, 0, Adj, visit, distance);
        cout << "the MST weights sum is: " << ans << endl;
    }
    in.close();
    return 0;
}

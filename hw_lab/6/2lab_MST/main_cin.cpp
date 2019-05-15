#include <iostream>
#include <cstdio>
#include <vector>
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
    int T;
    cout<<"input Number of test case: ";
    cin >> T;
    if (T < 1 || T > 30) {
        printf("Number of test case should be in [1, 30].\n");
        return -1;
    }
    //loop the cases
    for (int i = 0; i < T; i ++) {
        cout<<"input Number of nodes, edges in test case " << i+1 << ": ";
        int n_nodes;
        cin >> n_nodes;
        int n_edges;
        cin >> n_edges;
        cout<<"input an edge from u to v with weight w:\n";
        //get the input to create the adjacent list
        vector<vector<ListNode>> Adj;
        for (int j = 0; j < n_edges; j++){
            int u, v, weight;
            cin>>u;
            cin>>v;
            cin>>weight;
            //cout<<u<<v<<weight;
            Adj[u].push_back(ListNode(v,weight));
        }

        vector<bool> visit(n_nodes);
        vector<int> distance(n_nodes);
        int ans = PrimMST(n_nodes, 0, Adj, visit, distance);
        cout << "the MST weights sum is: " << ans << endl;
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

#define sqr(x) (x)*(x)

const int INF = 1000000000;

struct ListNode{
    int v; //edge to v from the index u in the List
    float weight; //weight from u to v
    ListNode(int v, float weight): v(v), weight(weight){}
    ListNode(){}
};
struct CodiNode{
    int x; //x coordinate in 2D plane
    int y; //y coordinate in 2D plane
    CodiNode(int x, int y): x(x), y(y){}
    CodiNode(){}
};

float PrimMST(int n_nodes, int start, vector<vector<ListNode> > Adj, vector<bool> &visit, vector<float> &costexpand){
    fill(costexpand.begin(), costexpand.end(), INF);
    costexpand[start] = 0;
    float sum = 0;
    //loop for all the nodes
    for (int i = 0; i < n_nodes; i++){
        //find the smallest in Set visited
        int u = -1;
        float MIN = INF;
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
            float weight = Adj[u][j].weight;
            //cout<<(costexpand[u] + weight)<<" "<<costexpand[v]<<endl;
            if (visit[v] == false && weight < costexpand[v]){
                costexpand[v] = weight;
            }
        }
    }
    return sum;
}

int main() {
    ifstream in;
    in.open("input_easy.txt");
    int n_nodes;
    in >> n_nodes;
    //cout<<n_nodes<<endl;
    //get the input to create the adjacent list
    vector<vector<ListNode> > Adj(n_nodes);
    vector<CodiNode> Coo(n_nodes);
    for (int j = 0; j < n_nodes; j++){
        char uchar;
        in>>uchar;
		while (uchar == '\n') in>>uchar;
        int u = uchar - 'A';
        //cout<<uchar<<endl;
        int ux, uy;//coordinate
        in >> ux >> uy;
        Coo[u].x = ux;
        Coo[u].y = uy;
        cout<<ux<<" "<<uy<<endl;
        char vchar;
        char test;
		cout << "hhhhh--------\n";
	    in >> vchar;
		while (vchar == '\n') in >> vchar;
        for (int i=0;;i++)
        {
            cout<<vchar<<" ";
            int v = vchar - 'A';
            cout<<v<<" " << u << "\n";
            Adj[u].push_back(ListNode(v,1));
            Adj[v].push_back(ListNode(u,1));
			vchar = in.get();
            if(vchar=='\n'||vchar == EOF)
                break;
			in >> vchar;
        }
    }

    vector<bool> visit(n_nodes);
    vector<float> costexpand(n_nodes);
    vector<float> distance(n_nodes);
	for (int i = 0; i < n_nodes; i ++)
		for (int j = 0; j < Adj[i].size(); j ++) {
			Adj[i][j].weight = sqrt(sqr(Coo[i].x - Coo[Adj[i][j].v].x) + sqr(Coo[i].y - Coo[Adj[i][j].v].y));
		}
    float ans = PrimMST(n_nodes, 0, Adj, visit, costexpand);
    //int ans = 0;
    cout << "the MST weights sum is: " << ans << endl;
    in.close();
    return 0;
}

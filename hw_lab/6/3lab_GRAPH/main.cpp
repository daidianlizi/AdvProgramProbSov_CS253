#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>
#include <utility>
using namespace std;

const int INF = 1000000000;
const bool  heuristicSearch = true;
//const bool  heuristicSearch = false;

struct ListNode{
    int v; //edge to v from the index u in the List
    double weight; //weight from u to v
    ListNode(int v, double weight): v(v), weight(weight){}
    ListNode(){}
};
struct CodiNode{
    double x; //x coordinate in 2D plane
    double y; //y coordinate in 2D plane
    CodiNode(int x, int y): x(x), y(y){}
    CodiNode(){}
};
vector<vector<ListNode>> Adj;
vector<CodiNode> Coo;
vector<bool> visit;
vector<char> prevpath;
vector<double> dist;
vector<double> heurdist;
pair <string, string> ret_object;
string ques2_1;
string ques2_2;
double EuclideanDis(CodiNode uxy, CodiNode vxy){
    return sqrt( pow((uxy.x - vxy.x),2) + pow((uxy.y - vxy.y),2));
}
double HeuristicFunc(int v, vector<CodiNode> Coo, int end){
    if (heuristicSearch == false){
        return 0; //Dij:0
    }
    return EuclideanDis(Coo[v],Coo[end]); //A*
}
void DFSSSP(int start, int end){
    if ( end == start){
        char tmp = end+ 'A';
        ret_object.first = ret_object.first + tmp;
        //cout<<tmp<<": "<<dist[end]<<endl;
        return;
    }
    DFSSSP(start, prevpath[end]);
    char tmp = end+ 'A';
    ret_object.first = ret_object.first + tmp;
    //cout<<tmp<<": "<<dist[end]<<endl;
}
double PrintEnd(int start, int end){
            DFSSSP(start, end);
            char sc = start + 'A';
            char ec = end + 'A';
            cout<<"heuristicSearch: "<<heuristicSearch<<endl;
            cout<<"start point: "<<sc<<endl;
            cout<<"end point: "<<ec<<endl;
            cout<<"ret_object.first: "<<ret_object.first<<endl;
            cout<<"ret_object.second: "<<ret_object.second<<endl;
            cout<<"build order of the tested edge: "<<ques2_1<<endl;
            cout<<"build order of the expanded edge: "<<ques2_2<<endl;
            return dist[end];
}
double DijMST(int n_nodes, int start, int end){
    fill(dist.begin(), dist.end(), INF);
    fill(heurdist.begin(), heurdist.end(), INF);
    for (int i = 0; i < n_nodes; i ++){
        prevpath[i] = i;
    }
    dist[start] = 0;
    heurdist[start] = EuclideanDis(Coo[start], Coo[end]);
    //loop for all the nodes
    for (int i = 0; i < n_nodes; i++){
        //find the smallest in Set visited
        //cout<<"i:"<<i<<endl;
        int u = -1;
        double MIN = INF;
        for (int j = 0; j < n_nodes; j++){
            if (visit[j] == false && heurdist[j] < MIN){
                u = j;
                MIN = heurdist[j];
            }
        }
        //cout<<"u: "<<u<<endl;
        if (u == -1)
            return -1;
        visit[u] = true;
        char tmp = u + 'A';
        char pre_tmp = prevpath[u] + 'A';
        if (u != start)
            ques2_2 = ques2_2 + pre_tmp+tmp+' ';
        ret_object.second = ret_object.second + tmp;//expanded
        if (u == end){
            return PrintEnd(start, end);
        }
        //renew the adjacent edge
        //cout<<"Adj[0].size(): "<<Adj[u].size()<<endl;
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;
            //cout<<(dist[u] + weight)<<" "<<dist[v]<<endl;
            char uc = u + 'A';
            char vc = v + 'A';
            if (visit[v] == false) ques2_1 = ques2_1 + uc+vc+' ';
            if (visit[v] == false && (dist[u] + Adj[u][j].weight) < dist[v] ){
                //cout<<"v: "<<v<< ", dis: "<<heurrenew<< ","<<Coo[v].x<<","<<Coo[v].y<<" ";
                dist[v] = dist[u] + Adj[u][j].weight;
                heurdist[v] = dist[v] + HeuristicFunc(v, Coo, end);
                prevpath[v] = u;
            }
        }
    }
    return -1;
}
void renew(int n_nodes){
    for (int u = 0; u < n_nodes; u++){
        CodiNode uxy = Coo[u];
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;
            CodiNode vxy = Coo[v];
            Adj[u][j].weight = EuclideanDis(uxy,vxy); 
        }
    }
}
void myreadfile(ifstream &in, int n_nodes){
    for (int j = 0; j < n_nodes; j++){
        char uchar;
        in>>uchar;
        int u = uchar - 'A';
        //cout<<uchar<<endl;
        int ux, uy;//coordinate
        in >> ux >> uy;
        Coo[u].x = ux;
        Coo[u].y = uy;
        //cout<<ux<<" "<<uy<<" ";
        char vchar;
        char test;
        for (int i=0;;i++)
        {
            in >> vchar;
            //cout<<vchar<<" ";
            int v = vchar - 'A';
            //cout<<v<<" " << u << "\n";
            Adj[u].push_back(ListNode(v,1));
            //Adj[v].push_back(ListNode(u,1));
            vchar = in.get();
            if(vchar=='\n'||vchar=='\r'||vchar == EOF){
                //cout<<endl;
                break;
            }
        }
    }
}
int main() {
    int casenumber = 3;
    char start_char, end_char;
    string infile;
    switch (casenumber){
        case 1 : 
            start_char = 'A';
            end_char = 'G';
            infile = "input.txt";
            break;
        case 2 : 
            start_char = 'E';
            end_char = 'I';
            infile = "input.txt";
            break;
        case 3 : 
            start_char = 'A';
            end_char = 'C';
            infile = "input_easy.txt";
            break;
    }
    ifstream in;
    in.open(infile);
    int n_nodes;
    in >> n_nodes;
    //cout<<n_nodes<<endl;
    Adj.resize(n_nodes);
    Coo.resize(n_nodes);
    visit.resize(n_nodes);
    prevpath.resize(n_nodes);
    dist.resize(n_nodes);
    heurdist.resize(n_nodes);
    //get the input to create the adjacent list
    myreadfile(in, n_nodes);
    //cout<<"Adj[0].size(): "<<Adj[0].size()<<endl;
    renew(n_nodes);
    int start = start_char -'A';
    int end = end_char -'A';
    double ans = DijMST(n_nodes, start, end);
    cout << "the MST weights sum is: " << ans << endl<<endl;
    in.close();
    return 0;
}

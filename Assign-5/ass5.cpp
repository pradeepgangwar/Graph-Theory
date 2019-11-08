#include<bits/stdc++.h>
using namespace std;

class cls {
    vector<vector<int>> graph;
    int v;

    unordered_set<int> setx;
    deque<int> que;

    public:cls(vector<vector<int>> graph) {
        this->graph = graph;
        v = graph.size();

        que.push_back(0);
        bool x = dfs(0,0,0);

        if(x == false) {cout<<"\nNo Hamiltonian Cycle Exist\n";}
        else {print_cycle();}

        return;
    }

    bool dfs(int cur, int par, int tar) {
        if(cur != tar) {setx.insert(cur);}

        for(int i=0;i<v;i++) {
            if(graph[cur][i]==0 || i==par) {continue;}
            if(setx.find(i) != setx.end()) {continue;}

            que.push_back(i);
            if(i==tar && que.size()==v+1) {return true;}

            bool x = dfs(i,cur,tar);
            if(x == false) {
                que.pop_back();
                setx.erase(i);
                continue;
            }
            else {return true;}
        }

        return false;
    }

    void print_cycle() {
        cout<<endl;
        for(int i=0;i<que.size();i++) {
            cout<<que[i]<<" ";
        }
        cout<<endl;
    }
};

int main() {
    int v;
    cin>>v;
    vector<vector<int> > graph;
    for(int i=0;i<v;i++) {
        vector<int> vec;
        graph.push_back(vec);
        for(int j=0;j<v;j++) {
            int x;
            cin>>x;
            graph[i].push_back(x);
        }
    }

    cls c(graph);

	return 0;
}

/*
sample inputs

5
0 1 0 0 1
1 0 1 1 1
0 1 0 1 0
0 1 1 0 1
1 1 0 1 0


5
0 1 1 1 0
1 0 1 1 0
1 1 0 1 1
1 1 1 0 1
0 0 1 1 0

*/

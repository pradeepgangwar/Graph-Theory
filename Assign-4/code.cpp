#include<bits/stdc++.h>
using namespace std;

class cls {
    vector<vector<int>> g1, g2;
    map<int,int> deg_v1, deg_v2;
    int v;
    public:bool ans;

    public:cls(vector<vector<int>> g1_temp, vector<vector<int>> g2_temp) {
        g1 = g1_temp;
        g2 = g2_temp;
        v = g1.size();

        assign_degree();

        ans = trivial_check();
        if(ans == false) {return;}

        ans = compare_edges();
        return;
    }

    bool trivial_check() {
        if(g1.size() != g2.size()) {return false;}

        map<int,int> m1, m2;
        for(auto itr=deg_v1.begin(); itr!=deg_v1.end(); itr++) {
            m1[itr->second]++;
        }
        for(auto itr=deg_v2.begin(); itr!=deg_v2.end(); itr++) {
            m2[itr->second]++;
        }

        for(auto itr=m1.begin(); itr!=m1.end(); itr++) {
            if(m2.find(itr->first) == m2.end()) {return false;}
            if(m2[itr->first] != itr->second) {return false;}
        }
        return true;
    }

    void assign_degree() {
        for(int i=0;i<v;i++) {
            int c = 0;
            for(int j=0;j<v;j++) {
                if(g1[i][j] == 1) {c++;}
            }
            deg_v1[i] = c;
        }

        for(int i=0;i<v;i++) {
            int c = 0;
            for(int j=0;j<v;j++) {
                if(g2[i][j] == 1) {c++;}
            }
            deg_v2[i] = c;
        }
    }

    bool compare_edges() {
        map<tuple<int,int>,int> edge_deg;

        for(int i=0;i<v;i++) {
            for(int j=0;j<v;j++) {
                if(g1[i][j] == 0) {continue;}
                int x = deg_v1[i];
                int y = deg_v1[j];
                //printf("i = %d, x = %d, j = %d, y = %d,\n",i,x,j,y);
                edge_deg[make_tuple(x,y)]++;
            }
        }
        /*for(auto itr=edge_deg.begin();itr!=edge_deg.end();itr++) {
            printf("[%d, %d] = %d\n", get<0>(itr->first), get<1>(itr->first), itr->second);
        }
        cout<<endl;*/

        for(int i=0;i<v;i++) {
            for(int j=0;j<v;j++) {
                if(g2[i][j] == 0) {continue;}
                int x = deg_v2[i];
                int y = deg_v2[j];
                //printf("i = %d, x = %d, j = %d, y = %d,\n",i,x,j,y);
                edge_deg[make_tuple(x,y)]--;
            }
        }
        /*for(auto itr=edge_deg.begin();itr!=edge_deg.end();itr++) {
            printf("[%d, %d] = %d\n", get<0>(itr->first), get<1>(itr->first), itr->second);
        }
        cout<<endl;*/

        for(auto itr=edge_deg.begin();itr!=edge_deg.end();itr++) {
            if(itr->second != 0) {return false;}
        }
        return true;
    }
};

int main() {
    int v1;
    cin>>v1;
    vector<vector<int> > g1;
    for(int i=0;i<v1;i++) {
        vector<int> vec;
        g1.push_back(vec);
        for(int j=0;j<v1;j++) {
            int x;
            cin>>x;
            g1[i].push_back(x);
        }
    }
    cout<<endl;

    int v2;
    cin>>v2;
    vector<vector<int> > g2;
    for(int i=0;i<v2;i++) {
        vector<int> vec;
        g2.push_back(vec);
        for(int j=0;j<v2;j++) {
            int x;
            cin>>x;
            g2[i].push_back(x);
        }
    }
    cout<<endl;

    cls c(g1, g2);
    cout<<c.ans<<endl;

	return 0;
}

/*
sample input

5
0 1 0 0 1
1 0 1 0 1
0 1 0 1 0
0 0 1 0 1
1 1 0 1 0

5
0 1 0 0 1
1 0 1 0 0
0 1 0 1 1
0 0 1 0 1
1 0 1 1 0

*/

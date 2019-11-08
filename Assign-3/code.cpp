/*

C++ Implementation of : Listing all the minimum spanning trees in an undirected graph --- Paper published by: Yamada, Takeo 30 November 2010
By: Pradeep Gangwar
Paper link: http://www.nda.ac.jp/~yamada/paper/enum-mst.pdf

*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e4 + 5;
int idx[MAX], nodes, edges;
pair <int, pair<int, int> > p[MAX];
int min_cost = 0;

void initialize()
{
    for (int i=1; i<=MAX; i++)
    {
        idx[i] = i;
    }
}

int root(int i)
{
    while (idx[i] != i)
    {
        i = idx[i];
    }
    return i;
}

void union_func(int a, int b)
{
    int root_a = root(a);
    int root_b = root(b);

    idx[root_a] = idx[root_b];
}

set < pair<int, pair <int, int> > > kruskal(pair<int, pair<int, int> > p[])
{
    int x, y;
    int cost;
    set < pair<int, pair <int, int> > > tree_edges;

    for (int i=0; i<edges; i++)
    {
        x = p[i].second.first;
        y = p[i].second.second;

        cost = p[i].first;

        if (root(x) != root(y))
        {
            union_func(x,y);
            tree_edges.insert(p[i]);
            min_cost += cost;
        }
    }
    return tree_edges;
}

bool isMinTree(set < pair<int, pair <int, int> > > tree_edges)
{
    int x, y;
    set < pair<int, pair <int, int> > >:: iterator it;

    for (it=tree_edges.begin(); it!=tree_edges.end(); it++)
    {
        x = it->second.first;
        y = it->second.second;

        if (root(x) != root(y))
        {
            union_func(x,y);
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool validMinSpanningTree(set < pair<int, pair <int, int> > > tree_edges)
{
    int x, y;
    set < pair<int, pair <int, int> > >:: iterator it;
    int cost=0;

    for (it=tree_edges.begin(); it!=tree_edges.end(); it++)
    {
        x = it->second.first;
        y = it->second.second;

        int weight = it->first;

        if (root(x) != root(y))
        {
            cost += weight;
            union_func(x,y);
        }
        else
        {
            return false;
        }
    }
    cout<<cost<<" ffff"<<endl;
    if (cost == min_cost)
        return true;
    else
        return false;
}

set < pair<int, pair <int, int> > > find_cut_set(set < pair<int, pair <int, int> > > tree_edges, int turn, set < pair<int, pair <int, int> > > rest_edges)
{
    set < pair<int, pair <int, int> > > cut_set;
    set < pair<int, pair <int, int> > >:: iterator it;
    pair<int, pair<int, int> > removed;

    it=tree_edges.begin();
    advance(it, turn);

    int weight = it -> first;
    int v1 = it -> second.first;
    int v2 = it -> second.second;

    cout<<"Removing "<<v1<<" "<<v2<<endl;

    removed = make_pair(weight, make_pair(v1, v2));

    tree_edges.erase(it);

    for (int i=0; i<edges; i++)
    {
        // The edge should not be the same edge or edges in the tree ot the restricted edge
        if (tree_edges.find(p[i]) != tree_edges.end() || p[i] == removed || rest_edges.find(p[i]) != rest_edges.end())
        {
            continue;
        }
        int x = p[i].second.first;
        int y = p[i].second.second;

        int cost = p[i].first;

        if (cost == weight)
        {
            tree_edges.insert(p[i]);
            initialize();
            if (isMinTree(tree_edges))
            {
                cut_set.insert(p[i]);
            }
            tree_edges.erase(p[i]);
        }
    }

    return cut_set;

}

void printTree(set < pair<int, pair <int, int> > > tree_edges)
{
    cout<<endl<<"This tree contins the following edges"<<endl;
    set < pair<int, pair <int, int> > >:: iterator it;

    for (it=tree_edges.begin(); it!=tree_edges.end(); it++)
    {
        cout<<it->first<<", ";
        cout<<it->second.first<<" -> "<<it->second.second<<endl;
    }
    cout<<endl;
}

void all_mst(set < pair<int, pair <int, int> > > tree_edges, set < pair<int, pair <int, int> > > fixed_edges, set < pair<int, pair <int, int> > > rest_edges)
{
    set < pair<int, pair <int, int> > >:: iterator it;
    set < pair<int, pair <int, int> > > tree_minus_fixed;

    for (it=tree_edges.begin(); it!=tree_edges.end(); it++)
    {
        if (fixed_edges.find(*it) != fixed_edges.end())
        {
            continue;
        }
        else
        {
            tree_minus_fixed.insert(*it);
        }
    }

    int branches = 0;

    for (it=tree_minus_fixed.begin(); it!=tree_minus_fixed.end(); it++)
    {
        branches++;
    }

    for (int i=0; i< branches; i++)
    {
        set < pair<int, pair <int, int> > > cut_set;
        set < pair<int, pair <int, int> > >:: iterator it, it_tree;
        cout<<"Turn "<<i<<endl;

        it_tree=tree_minus_fixed.begin();
        advance(it_tree, i);

        cut_set = find_cut_set(tree_minus_fixed, i, rest_edges);

        /* If cut set exists */
        it = cut_set.begin();
        if (it != cut_set.end()) 
        {
            for (it=cut_set.begin(); it!=cut_set.end(); it++)
            {
                tree_edges.erase(*it_tree);
                tree_edges.insert(*it);
                rest_edges.insert(*it_tree);

                cout<<it->first<<endl;
                cout<<it->second.first<<" "<<it->second.second<<endl<<endl;
                
                initialize();
                if(validMinSpanningTree(tree_edges))
                {
                    cout<<"New tree found"<<endl;
                    printTree(tree_edges);
                }
                all_mst(tree_edges, fixed_edges, rest_edges);
            }
        }
        // If cut set doesn't exist
        else
        {
            set < pair<int, pair <int, int> > >:: iterator it_fix;
            it_fix = tree_minus_fixed.begin();
            advance(it_fix, i);
            fixed_edges.insert(*it_fix);
            cout<<"No cut set found for this edge"<<endl<<endl;
        }
        
    }
}

int main()
{
    int weight, v1, v2;

    initialize();

    cout<<"Enter the number of nodes and edges"<<endl;
    cin>>nodes>>edges;

    cout<<endl<<"Enter the edges in format: 'v1 v2 weight' and press enter"<<endl<<endl;
    for (int i=0; i<edges; i++)
    {
        cin>>v1>>v2>>weight;
        p[i] = make_pair(weight, make_pair(v1, v2));
    }

    sort(p, p+edges);
    set < pair<int, pair <int, int> > > tree_edges = kruskal(p);
    set < pair<int, pair <int, int> > > fixed_edges;
    set < pair<int, pair <int, int> > > rest_edges;

    set < pair<int, pair <int, int> > >:: iterator it;

    printTree(tree_edges);

    all_mst(tree_edges, fixed_edges, rest_edges);

    cout<<"Minimum weight is "<<min_cost<<endl;
}
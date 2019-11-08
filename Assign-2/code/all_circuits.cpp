#include <bits/stdc++.h>
using namespace std;

void insert_edge(vector <int> v[], int origin, int destination)
{
    v[origin].push_back(destination);
    v[destination].push_back(origin);
    cout<<"Edge inserted successfully"<<endl;
}

void delete_edge(vector <int> v[], int origin, int destination)
{
    v[origin].erase(remove(v[origin].begin(), v[origin].end(), destination), v[origin].end());
    v[destination].erase(remove(v[destination].begin(), v[destination].end(), origin), v[destination].end());
}

void print_graph(vector<int> v[], int n) 
{ 
    for (int i = 0; i < n; ++i) 
    { 
        cout << "\n Adjacency list of vertex "
             << i << "\n head "; 
        for (int j=0; j<v[i].size(); j++)
        {
            cout << "-> " << v[i][j];
        } 
        printf("\n"); 
    }
}

void extract_circuit_util(int s, int d, vector <int> v[], bool visited[], int path[], int path_index)
{
    visited[s] = true;
    path[path_index] = s;
    path_index++;

    if (s == d && path_index > 2)
    {
        for (int i=0; i<path_index; i++)
        {
            cout<<path[i]<<" ";
        }
        cout<<endl;
    }
    else
    {
        for (int i=0; i<v[s].size(); i++)
        {
            if (!visited[v[s][i]])
            {
                extract_circuit_util(v[s][i], d, v, visited, path, path_index);
            }
        }
    }
    visited[s] = false;
    path_index--;
}

void extract_circuits(int s, int d, vector <int> v[])
{
    bool visited[200] = {false};
    int path[300];
    int path_index = 0;

    extract_circuit_util(s, d, v, visited, path, path_index);
}

int main()
{
    int n;

    cout<<"Enter the number of vertices: "<<endl;
    cin>>n;

    vector <int> v[200];

    while(1)
    {
        int choice;

        cout<<"Enter your choice:"<<endl;
        cout<<"1. Insert an edge"<<endl;
        cout<<"2. Delete an edge"<<endl;
        cout<<"3. Print graph"<<endl;
        cout<<"4. Exit"<<endl;

        cin>>choice;

        if (choice == 1)
        {
            int origin, destination;
            cout<<"Enter the origin and destination"<<endl;
            cin>>origin>>destination;
            insert_edge(v, origin, destination);
        }

        else if (choice == 2)
        {
            int origin, destination;
            cout<<"Enter the origin and destination"<<endl;
            cin>>origin>>destination;
            delete_edge(v, origin, destination);
        }

        else if (choice == 3)
        {
            print_graph(v, n);
        }

        else if (choice == 4)
        {
            break;
        }

        else
        {
            cout<<"Invalid choice"<<endl;
        }
    }

    int vertex;
    cout<<endl<<"Enter the vertex you want to find circuit at?"<<endl;
    cin>>vertex;

    for (int i=0; i<v[vertex].size(); i++)
    {
        extract_circuits(v[vertex][i], vertex, v);
    }
}
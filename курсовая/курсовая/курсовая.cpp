#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

#define edge pair<int,int>

class Graf 
{
public:
    vector<vector<int> > matrix, matr;
    vector<pair<int, edge>> G; 
    vector<pair<int, edge>> MST; 
    int* parent,* vertic;
    int kolvo;

    Graf() { kolvo = 0; parent = 0; vertic = 0; }
    ~Graf() {
        G.clear();
        MST.clear();
        matrix.clear();
        matr.clear();
    }
private:
    void ini(int n) 
    { 
        kolvo = n;
        parent = new int[n];
        vertic = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            vertic[i] = i;
        }
        matrix = vector<vector<int> >(n, vector<int>(n, 0));
        G.clear();
        MST.clear();
    }

    void AddEdge(int u, int v, int data)
    {
        G.push_back(make_pair(data, edge(u, v)));
    }
    void AddEdgeM(int u, int v, int data)
    {
        matrix[u][v] = data;
        matrix[v][u] = data;
    }
    void AddM(int u, int v, int data)
    {
        matr[u][v] = data;
        matr[v][u] = data;
    }
    void SinM() 
    {
        int u, v, data;
        matr = vector<vector<int> >(kolvo, vector<int>(kolvo, 0));
        for (int i = 0; i < MST.size(); i++) {
            u = MST[i].second.first;
            v = MST[i].second.second;
            data = MST[i].first;
            AddM(u, v, data);
        }
    }

    void print(vector<vector<int> > m)
    {
        cout << "matrix:" << endl;
        for (int i = 0; i < kolvo; i++)
        {
            for (int j = 0; j < kolvo; j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
    }
    void gprint(vector<pair<int, edge>> H)
    {
        cout << "Edge : Weight" << endl;
        for (int i = 0; i < H.size(); i++) {
            cout << H[i].second.first << "-" << H[i].second.second << " : " << H[i].first;
            cout << endl;
        }
    }

    void depth(int visited[], int v)
    {
        visited[v] = 1;
        cout << vertic[v] << " ";
        for (int i = 0; i < kolvo; i++)
            if ((!visited[i]) and (matr[v][i] > 0))
                depth(visited, i);
    }
    void widht(int visited[], int v)
    {
        queue<int> q;
        int ind;
        q.push(v);
        cout << vertic[v] << " ";
        visited[v] = 1;
        while (!q.empty()) 
        {
            ind = q.front();
            q.pop();
            for (int i = 1; i < kolvo; i++) 
                if ((!visited[i]) and (matr[ind][i]>0))
                {
                    visited[i] = 1;
                    q.push(i);
                    cout << vertic[i] << " ";
                }
        }
    }

public:
    void depthTraversal()
    {
        int* visited = 0;
        if (!MST.empty())
        {
            visited = new int[kolvo + 1];
            for (int i = 0; i < kolvo; i++)
                visited[i] = 0;
            cout << "Depth traversal: ";
            depth(visited, 0);
            cout << endl;
        }
        delete[] visited;
    }
    void widhtTraversal()
    {
        int* visited = 0;
        if (!MST.empty())
        {
            visited = new int[kolvo + 1];
            for (int i = 0; i < kolvo; i++)
                visited[i] = 0;
            cout << "Width traversal: ";
            widht(visited, 0);
            cout << endl;
        }
        delete[] visited;
    }

    void translate()
    {
        ifstream file("C:\\Users\\1\\OneDrive\\Рабочий стол\\обучение\\предметы\\прога\\курсовая\\primer.txt", ios::binary);
        if (file.is_open())
        {
            string s;
            char c;
            int i = 0;

            getline(file, s);
            int razm = s.length(), n = 0, cur = 0;
            while (cur < razm) 
            {
                c = s.at(cur);
                if ((c != ' ') and (c != '\r')) { n++; }
                cur++;
            }

            ini(n);

            while (!file.eof())
            {
                getline(file, s);
                int f = 0, j =0, k = 0;
                razm = s.length();
                for (int j = 0; j < razm; j++)
                {
                    c = s[j];
                    if ((c != ' ') and (c != '\r'))
                    {
                        k = 10 * k + (c - '0');
                    }
                    else
                    {
                        AddEdgeM(i, f, k);
                        f++;
                        k = 0;
                    }
                }
                i++;
            }
            print(matrix);
        }
        else
            cout << "Error" << endl;
    }

private:  
    void spisok() 
    {
        for (int i = 0; i < kolvo; i++)
        {
            for (int j = 0; j < kolvo; j++) {
                if (matrix[i][j] != 0)
                    AddEdge(i, j, matrix[i][j]);
            }
        }
        gprint(G);
    }
    void sort()
    {
        for (int i = 0; i < G.size(); i++)
        {
            pair<int, edge> key = G[i];
            int j = i - 1;

            while ((j >= 0) && (G[j].first > key.first))
            {
                G[j + 1] = G[j];
                j--;
            }

            G[j + 1] = key;
        }
    }
    int find_s(int i)
    {
        if (i == parent[i])
            return i;
        else
            return find_s(parent[i]);
    }
    void unit(int x, int y)
    {
        int px = find_s(x);
        int py = find_s(y);
        if (px != py) 
            parent[px] = py;
    }
public:
    void algoritm()
    {
        spisok();
        int u, v, ves = 0;
        sort();
        for (int i = 0; i < G.size(); i++) 
        {
            u = find_s(G[i].second.first);
            v = find_s(G[i].second.second);
            if (u != v)
            {
                MST.push_back(G[i]);
                unit(u, v);
                ves += G[i].first;
            }
        }
        gprint(MST);
        cout << "Weight: " << ves << endl;
        SinM();
        print(matr);
    }
};


int main()
{
    Graf G;
    G.translate();
    G.algoritm();
    G.depthTraversal();
    G.widhtTraversal();
    G.~Graf();
    return 0;
}
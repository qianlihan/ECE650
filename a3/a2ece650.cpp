// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

bool** initialize(bool** g, int n){
    g = new bool*[n];
    for(int i=0; i<n; i++){
        g[i] = new bool[n];
        for(int j=0; j<n; j++){
            g[i][j] = false;
        }
    }
    return g;
}

void add(bool** g, int a, int b){
    g[a][b] = true;
    g[b][a] = true;
}

void shortest(bool** g, int start, int end, int n){
    //initialize an array to keep track of the previous node, initial value = -1
    int track[n];
    for(int i=0; i<n; i++){
        track[i] = -1;
    }
    track[start] = -2;

    queue<int> next;
    next.push(start);
    int current;

    //traverse the graph with BFS
    while (!next.empty())
    {
        current = next.front();
        next.pop();
        for (int i = 0; i < n; i++)
        {
            if(g[current][i] && track[i] == -1){
                next.push(i);
                track[i] = current;
                if(i == end){
                    break;
                }
            }
                
        }

    }

    if(track[end] != -1){
        //print the result in a reverse order using reverse iterator
        vector<int> result;
        int temp = end;
        do{
            result.push_back(temp);
            temp = track[temp];
        }while(temp != -2);
        
        vector<int>::reverse_iterator i = result.rbegin();
        cout << *i;
        for(i++;i != result.rend(); i++){
            cout<< '-' << *i;
        }
        cout << '\n';
        

    }
    else{
        cerr << "Error: cannot reach"<< endl;
    }
    return;
}

int main(int argc, char** argv) {
    bool **graph;
    int n;
    int start,end;
    // read from stdin until EOF
    while (!cin.eof()) {
        string line;

        // read a line of input until EOL and store in a string
        getline(cin, line);
        
        if (cin.eof() || line.empty()){
            return 0;
        }
        
        // we will use the input stream to parse the line
        istringstream input(line);

        char first;
        input >> first;
        if (first == 'V')
        {   
            cout<<line << endl;
            input >> n;
            if(n < 1){
                cerr << "Error: illegal number"<< endl;
            }
            graph = initialize(graph, n);
        }
        else if(first == 'E')
        {   
            line[line.length()-2]='}';
            line[line.length()-1]='\n';
            cout<<line;
            char e, d, f;

            //delete "{"
            input >> e;

            int a,b;
            while(e != '}'){

                //format: char int char int char   ex. <2,3>
                input >> e >> a >> d >> b >> f;

                //check if the vertices are legals
                if(a < 0 || a >= n || b < 0 || b >= n || a == b){
                    graph = initialize(graph, n);
                    cerr << "Error: illegal edges"<< endl;
                    break;
                }
                add(graph, a, b);

                //this letter is either ',' or '}'
                input >> e;
            }
        }
        else if(first == 's'){
            input >> start >> end;
            if(start < 0 || end >= n || end < 0 || start >= n){
                cerr << "Error: illegal input"<< endl;
            }
            else{
                shortest(graph, start, end, n);
            }
            start = -1;
            end = -1;
        }
        

    }
}

// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"
#include <iostream>
#include <sstream>
#include <vector>

struct Edge{
    int u, v;
};

struct Graph{
    std::vector<Edge> e;
    int edgeN, vertexN;
    void add(int a, int b);
};

void Graph::add(int a, int b){
    Edge temp;
    temp.u =a;
    temp.v = b;
    e.push_back(temp);
}

int main(int argc, char **argv) {
    std::string line;
    // -- allocate on the heap so that we can reset later if needed
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    //Minisat::Lit *literal;
    std::vector<int> result;
    Graph g;
    int n;

    while (!std::cin.eof()) {

        // read a line of input until EOL and store in a string
        std::getline(std::cin, line);
        if (std::cin.eof()){
          break;
        }

        // we will use the input stream to parse the line
        std::istringstream input(line);
        char first;
        input >> first;

        if(first == 'V'){
            input >> n;
            if(n < 1){
                std::cerr << "Error: illegal number"<< std::endl;
                break;
            }
            
            g.edgeN = 0;
            g.vertexN = n;
            g.e.clear();
        }
        else if(first == 'E'){
            //reset the graph
            g.edgeN = 0;
            g.e.clear();

            char e, d, f;

            //delete "{"
            input >> e;
            int a,b;
            while(e != '}'){

                //format: char int char int char   ex. <2,3>
                input >> e>> a >> d >> b >> f;
                if(e == '}'){
                    break;
                }
                //input >> a >> d >> b >> f;

                //check if the vertices are legal
                if(a < 0 || a >= g.vertexN || b < 0 || b >= g.vertexN || a == b){
                    std::cerr << "Error: illegal edges"<< std::endl;
                    break;
                }
                g.add(a, b);
                g.edgeN++;

                //this letter is either ',' or '}'
                input >> e;
            }
            if(g.edgeN==0){
                std::cout<<'\n';
                continue;
            }
            
            int h = g.vertexN;
            int l = 0;
            while(h >= l){
                int k = (h+l)/2;
                std::cout<<k<<'\n';
                if(k==0){
                    break;
                }
                Minisat::Lit literal[g.vertexN][k];

                //add literals
                for(int i=0; i<g.vertexN; i++){
                    for(int j=0; j<k; j++){
                        literal[i][j] = Minisat::mkLit(solver->newVar());
                    }
                }

                //first condition
                Minisat::vec<Minisat::Lit> temp;
                for (int i = 0; i < k; i++) {
                    for (int j = 0; j < g.vertexN; j++) {
                        temp.push(literal[j][i]);
                    }
                    solver->addClause(temp);
                    temp.clear();
                }   
                
                //second condition
                for(int i = 0; i < g.vertexN; i++) {
                    for (int j = 0; j < k; j++){
                        for (int m=0; m<j; m++) {
                            solver->addClause(~literal[i][j], ~literal[i][m]);
                        }
                    }
                }

                //third
                for(int i = 0; i < k; i++) {
                    for (int j = 0; j < g.vertexN; j++){
                        for (int k=0; k<j; k++) {
                            solver->addClause(~literal[j][i], ~literal[k][i]);
                        }
                    }
                }

                //fourth
                for(Edge edge: g.e){
                    for(int i = 0; i < k; i++){
                        temp.push(literal[edge.u][i]);
                        temp.push(literal[edge.v][i]);
                    }
                    solver->addClause(temp);
                    temp.clear();
                }
                
                bool res = solver->solve();
                if(res){
                    result.clear();
                    for(int i=0; i<g.vertexN; i++){
                        for (int j = 0; j < k; j++){
                            if(Minisat::toInt(solver->modelValue(literal[i][j])) == 0){
                                result.push_back(i);
                                break;
                            }
                        }
                    }
                    if(h<= l+1){
                        h--;
                    }
                    else{
                        h = (h+l)/2;
                    }
                }
                else{
                    if(h<= l+1){
                        l++;
                    }
                    else{
                        l = (h+l)/2;
                    }
                }
                solver.reset(new Minisat::Solver());
            }

            //output the result
            for (auto i = result.begin(); i != result.end(); i++){
                std::cout << *i;
                if((i+1) != result.end()){
                    std::cout<< " ";
                }
                else{
                    std::cout<<'\n';
                }
            }
        }
        else{
            std::cerr << "Error: invalid input"<<std::endl;
        }
        
    }
}

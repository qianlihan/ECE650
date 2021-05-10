#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>


#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

using namespace std;
std::vector<int> result1, result2, result3;
//clockid_t cid1, cid2, cid3;
pthread_t solution1, solution2, solution3;
pthread_mutex_t lock;

struct Graph{
    int edgeN, vertexN;
    void add(int a, int b);
    void initialize(int n);
    int *degree;
    bool **edge;
    std::vector < std::pair<int,int> > edgeLst;
};

void Graph::initialize(int n){
    vertexN = n;
    edgeN = 0;
    edge = new bool*[n];
    for(int i = 0; i < n; i++) {
        edge[i] = new bool[n];
        for(int j = 0; j < n; j++) {
            edge[i][j] = false;
        }
    }
    degree = new int[n];
    for(int i=0; i < n; i++){
       degree[i] =0;
    }
    edgeLst.clear();
}

void Graph::add(int a, int b){
    if(a<b){
        edge[a][b]=true;
    }
    else if(b<a){
        edge[b][a]=true;
    }
    degree[a]++;
    degree[b]++;
    edgeN++;
    std::pair<int,int> tmp(a,b);
    edgeLst.push_back(tmp);
}

int findMax(int arr[], int size);
void printResult(std::vector<int> result);
static void pclock(char *msg, clockid_t cid);

void *reduction(void *arg){
    Graph *g= static_cast<Graph *>(arg);
    if(g->edgeN == 0){
        pthread_exit(NULL);
    }
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    int l = 0;
    int h = g->vertexN;
    while(h >= l){
        int k = (h+l)/2;
        if(k == 0){
            break;
        }
        Minisat::Lit literal[g->vertexN][k];

        //add literals
        for(int i=0; i<g->vertexN; i++){
            for(int j=0; j<k; j++){
                literal[i][j] = Minisat::mkLit(solver->newVar());
            }
        }

        //first condition
        Minisat::vec<Minisat::Lit> temp;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < g->vertexN; j++) {
                temp.push(literal[j][i]);
            }
            solver->addClause(temp);
            temp.clear();
        }   
        
        //second condition
        for(int i = 0; i < g->vertexN; i++) {
            for (int j = 0; j < k; j++){
                for (int m=0; m<j; m++) {
                    solver->addClause(~literal[i][j], ~literal[i][m]);
                }
            }
        }

        //third
        for(int i = 0; i < k; i++) {
            for (int j = 0; j < g->vertexN; j++){
                for (int k=0; k<j; k++) {
                    solver->addClause(~literal[j][i], ~literal[k][i]);
                }
            }
        }

        //fourth
        for(int i = 0; i < g->vertexN; i++){
            for(int j = i+1; j < g->vertexN; j++){
                if(g->edge[i][j]){
                    for(int m = 0; m < k; m++){
                        temp.push(literal[i][m]);
                        temp.push(literal[j][m]);
                    }
                    solver->addClause(temp);
                    temp.clear();
                }
            }
        }
        

        bool res = solver->solve();
        
        if(res){
            result1.clear();
            for(int i=0; i<g->vertexN; i++){
                for (int j = 0; j < k; j++){
                    if(Minisat::toInt(solver->modelValue(literal[i][j])) == 0){
                        result1.push_back(i);
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
    //pthread_mutex_lock(&lock);
    // int s =pthread_getcpuclockid(pthread_self(), &cid1);
    // if (s!=0)
	// {
	// 	handle_error_en(s, "pthread_getcpuclockid");
	// }
    // pclock("Subthread 1 CPU time:    ", cid1);
    // pclock("Subthread 1 CPU time:    ", CLOCK_THREAD_CPUTIME_ID);
    // pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *approx1(void *arg){
    Graph *g= static_cast<Graph *>(arg);

    //create temp variable to manipulate
    int tempDegree[g->vertexN];
    for(int i=0; i < g->vertexN; i++){
        tempDegree[i] = g->degree[i];
    }

    int  maxIndex, edgeRemoved = 0;
    while(edgeRemoved < g->edgeN){
        //get the index with max, updata the degree table and edgeRemoved
        maxIndex = findMax(tempDegree, g->vertexN);
        result2.push_back(maxIndex);
        edgeRemoved += tempDegree[maxIndex];
        tempDegree[maxIndex] = 0;
        for(int i=0; i<g->vertexN; i++){
            if(g->edge[maxIndex][i] || g->edge[i][maxIndex]){
                tempDegree[i]--;
            }
        }
    }
    //pthread_mutex_lock(&lock);
    // int s =pthread_getcpuclockid(pthread_self(), &cid2);
    // if (s!=0)
	// {
	// 	handle_error_en(s, "pthread_getcpuclockid");
	// }
    // pclock("Subthread 2 CPU time:    ", cid2);
    // pclock("Subthread 2 CPU time:    ", CLOCK_THREAD_CPUTIME_ID);
    // pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void *approx2(void *arg){
    Graph *g= static_cast<Graph *>(arg);
    int index;
    std::vector < std::pair<int,int> > tmp;
    
    while(!g->edgeLst.empty()){
        //pick a random edge and store it
        index = rand() % g->edgeLst.size();
        std::pair<int,int> target= g->edgeLst[index];
        result3.push_back(target.first);
        result3.push_back(target.second);
        
        //remove the related edges
        for(auto i = g->edgeLst.cbegin(); i != g->edgeLst.cend(); ++i){
            if(i->first != target.first && i->second != target.first && i->first != target.second && i->second != target.second){
                tmp.push_back(*i);
            }
        }

        g->edgeLst.clear();
        for (int i=0; i<tmp.size(); i++)
            g->edgeLst.push_back(tmp[i]);
        tmp.clear();

    }
    //pthread_mutex_lock(&lock);
    // int s =pthread_getcpuclockid(pthread_self(), &cid3);
    // if (s!=0)
	// {
	// 	handle_error_en(s, "pthread_getcpuclockid");
	// }
    // pclock("Subthread 3 CPU time:    ", cid3);
    // pclock("Subthread 3 CPU time:    ", CLOCK_THREAD_CPUTIME_ID);
    // pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}


void *ioHandler(void *arg){
    std::string line;
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
            
        }
        else if(first == 'E'){
            //reset the graph
            g.initialize(n);

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

                //check if the vertices are legal
                if(a < 0 || a >= g.vertexN || b < 0 || b >= g.vertexN || a == b){
                    std::cerr << "Error: illegal edges"<< std::endl;
                    break;
                }
                g.add(a, b);

                //this letter is either ',' or '}'
                input >> e;

            }
            
            pthread_mutex_init(&lock, NULL);
            //create 3 threads

            pthread_create(&solution1, NULL, reduction, &g);
            pthread_create(&solution2, NULL, approx1, &g);
            pthread_create(&solution3, NULL, approx2, &g);       

            struct timespec ts1;
            clock_gettime(CLOCK_REALTIME, &ts1);
            ts1.tv_sec += 30;

            pthread_join(solution2, NULL);
            pthread_join(solution3, NULL);

            int s = pthread_timedjoin_np(solution1, NULL, &ts1);
            if (s != 0) {
                std::cerr<< "CNF-SAT-VC: timeout\n";
            }
            else{
                std::cout<<"CNF-SAT-VC: ";
                printResult(result1);
                std::cout<<'\n';
                result1.clear();
            }
            
        
            std::cout<<"APPROX-VC-1: ";
            printResult(result2);
            std::cout<<'\n';
            result2.clear();

            std::cout<<"APPROX-VC-2: ";
            printResult(result3);
            std::cout<<'\n';            
            result3.clear();
        }
    }
    return NULL;
}


int main(int argc, char **argv) {
    pthread_t threadIO;
    pthread_create(&threadIO, NULL, ioHandler, NULL);
    pthread_join(threadIO, NULL);
}

int findMax(int arr[], int size){
    int index =0;
    for(int i=0; i<size; i++){
        if(arr[i]>arr[index]){
            index = i;
        }
    }
    return index;
}

void printResult(std::vector<int> result){
    if(!result.empty()){
        for (auto i = result.begin(); i != result.end(); i++){
            std::cout << *i;
            if((i+1) != result.end()){
                std::cout<< ",";
            }
        }
    }
}

static void pclock(char *msg, clockid_t cid)
{
    struct timespec ts;

    printf("%s", msg);
    if (clock_gettime(cid, &ts) == -1)
        handle_error("clock_gettime");
    std::cout << (ts.tv_sec*1000000000)+(ts.tv_nsec) << "ns" << std::endl;
    //printf("%4jd.%09ld\n", (intmax_t) ts.tv_sec, ts.tv_nsec / 1000000);
}

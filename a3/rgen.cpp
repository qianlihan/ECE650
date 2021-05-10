#include <iostream>
#include <unistd.h> 
#include <fstream>
#include <signal.h>
#include <utility>
#include <sys/wait.h>
using namespace std;

bool doAgain(std::pair<int, int> *coor[], int s, int n);
bool median(int x1, int y1, int x2, int y2, int x3, int y3);
bool overlap(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void Write();

int main (int argc, char **argv) {
    int opt;
    int s=10;
    int n=5;
    int l=5;
    int c=20;
    
    

    while((opt = getopt(argc, argv, "s:n:l:c:")) != -1)  
    {  
        switch(opt)  
        {  
            case 's':  
                //# of streets
                s = atoi(optarg);
                if(s < 2){
                    std::cerr << "Error: invalid input" << std::endl;
                    return 1;
                }  
                break;
            case 'n':  
                //segment for each street
                n=atoi(optarg);  
                if(n < 1){
                    std::cerr << "Error: invalid input" << std::endl;
                    return 1;
                }  
                break;   
            case 'l':
                //waiting time
                l=atoi(optarg);  
                if(l < 5){
                    std::cerr << "Error: invalid input" << std::endl;
                    return 1;
                } 
                break;
            case 'c':  
                //coordinate bound [-c, c]
                c=atoi(optarg);
                if(c < 1){
                    std::cerr << "Error: invalid input" << std::endl;
                    return 1;
                }   
                break;  
            case '?':  
                std::cerr << "Error: invalid option" << std::endl;
                return 1;
            default:
                return 0;
        }  
    }   
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }

    // read a random 8-bit value.
    // Have to use read() method for low-level reading
    int num = 1;
    // cast to integer to see the numeric value of the character

    //initialize a 2d array
    std::pair<int, int> *coor[s];
    int count = 0;
    do{
        std::cout << std::flush;
        for(int i=0; i<s; i++){
            coor[i] = new pair<int, int> [n+1];
            for(int j=0; j<n+1; j++){
                do{
                    urandom.read((char *)&num, sizeof(int));
                    coor[i][j].first = (int)num%(c+1);
                    urandom.read((char *)&num, sizeof(int));
                    coor[i][j].second = (int)num%(c+1);
                    count++;
                }while(doAgain(coor, i, j-1) && count < 25);
                if(count ==25){
                    std::cout << "eof" <<std::endl;
                    std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts"<<std::endl;
                    return 0;
                }
                else{
                    count = 0;
                }
            }

        }

        for(int i=0; i<s; i++){
            cout<< "a \"" << i << "\" ";
            for(int j=0; j<n+1; j++){
                cout<< "("<< coor[i][j].first<< ","<< coor[i][j].second<<") ";
            }
            cout<<"\n";
        }
        cout<<'g'<<endl;
        for(int i=0; i<s; i++){
            cout<< "r \"" << i << "\" "<<endl;
        }
        sleep(l);
    }while(true);
    //close random stream
    urandom.close();
    return 0;
}

bool doAgain(std::pair<int, int> *coor[], int s, int n){
    if(n<0){
        return false;
    }
    for(int i=0; i<s; i++){
        for(int j=0; j<n; j++){
            if(overlap(coor[i][j].first, coor[i][j].second, coor[i][j+1].first, coor[i][j+1].second, coor[s][n].first, coor[s][n].second, coor[s][n+1].first, coor[s][n+1].second)){
                return true;
            }
            
        }     
    }
    return false;
}

bool overlap(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    if(x4 == x3 && y3==y4){
        return true;
    }
    if((x1==x3 && y1==y3)&&(x4==x2 && y4==y2)){
        return true;
    }
    if((x2==x3 && y2==y3)&&(x4==x1 && y4==y1)){
        return true;
    }
    if ((y3 - y2) * (x2 - x1) ==  (y2 - y1) * (x3 - x2) && (y4 - y2) * (x2 - x1) ==  (y2 - y1) * (x4 - x2)){
        if(median(x1, y1, x2, y2, x3, y3)){
            return true;
        }
        if(median(x1, y1, x2, y2, x4, y4)){
            return true;
        }
        if(median(x3, y3, x4, y4, x1, y1)){
            return true;
        }
        if(median(x3, y3, x4, y4, x2, y2)){
            return true;
        }
    }
    return false;   
}

bool median(int x1, int y1, int x2, int y2, int x3, int y3){
    if(x1==x2){
        return (y3 > y1 && y1 > y2) || (y3 > y2 && y2 > y1);
    }
    return (x3 > x1 && x1 > x2) || (x3 > x2 && x2 > x1);
}

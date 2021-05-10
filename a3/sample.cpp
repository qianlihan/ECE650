#include <iostream>
#include <unistd.h> 
#include <fstream>
#include <signal.h>
#include <utility>
#include <sys/wait.h>
using namespace std;


int main (int argc, char **argv) {

    std::cout << std::flush; 
    
    cout<< "a \"Weber Street\" (2,-1) (2,2) (5,5) (5,6) (3,8)"<<endl;
    cout<< "a \"King Street S\" (4,2) (4,8)"<<endl;
    cout<< "a \"Davenport Road\" (1,4) (5,8)"<<endl;
    cout<< "g"<<endl;
    sleep(3);
    
}
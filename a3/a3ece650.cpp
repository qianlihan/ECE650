#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
using namespace std;

int main (int argc, char **argv) {
    int one2rgen[2];
    int a1Toa2[2];
    pipe(one2rgen);
    pipe(a1Toa2);
    std::vector<pid_t> kids;
    pid_t child_pid;
    child_pid = fork();

    //a2
    if(child_pid==0){
        //a1 and reading write to a2
        dup2(a1Toa2[0], STDIN_FILENO);
        
        close(a1Toa2[0]);
        close(a1Toa2[1]);
        execv("./a2ece650", NULL);
    }
    kids.push_back(child_pid);

    child_pid = fork();

    //a1
    if(child_pid==0){
        //rgen writes to a1
        dup2(one2rgen[0], STDIN_FILENO);
        close(one2rgen[0]);
        close(one2rgen[1]);

        //a1 writes to a2
        dup2(a1Toa2[1], STDOUT_FILENO);
        close(a1Toa2[0]);
        close(a1Toa2[1]);
        
        execl("/usr/bin/python3", "python", "a1ece650.py", NULL);
    }
    kids.push_back(child_pid);

    child_pid = fork();

    //rgen
    if(child_pid==0){
        //rgen writes to a1
        dup2(one2rgen[1], STDOUT_FILENO);
        close(one2rgen[0]);
        close(one2rgen[1]);
        
        execv("./rgen", argv);
    }

    kids.push_back(child_pid);

    //reading
    child_pid = fork();
    if(child_pid==0){
        //reading writes to a2
        dup2(a1Toa2[1], STDOUT_FILENO);
        close(a1Toa2[0]);
        close(a1Toa2[1]);
        execv("./reading", NULL);
    }
    kids.push_back(child_pid);
  
    int status;
    wait(&status);

    for (int i = 0; i < kids.size(); i++) {
        kill(kids[i], SIGTERM);
        waitpid(kids[i], &status, 0);
    }
    
    return 0;
}

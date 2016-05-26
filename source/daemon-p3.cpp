#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

pid_t cpids[3];
bool cpids_lock;

void sigterm_handler(int signum, siginfo_t *siginfo, void *ucontext){
    if(!cpids_lock){
        cpids_lock = true;

        int i, wstatus;
        pid_t res;
        for(i = 0; i < 3; i++){
            res = waitpid(cpids[i], &wstatus, WNOHANG);
            if(res == 0){
                kill(cpids[i], SIGTERM);
            }
        }
    }
    else {
        sleep(1);
    }
}

int main(int argc, char *argv[]){
    cpids[0] = fork();
    cpids_lock = false;
    if(cpids[0] == -1){
        exit(EXIT_FAILURE);
    }

    if(cpids[0] == 0){
        char serv1[] = "/opt/daemon-p3/server-1.py";
        char *serv1_argv[] = {serv1, NULL};
        char *serv1_envp[] = {NULL};
        execve(serv1, serv1_argv, serv1_envp);
        exit(EXIT_FAILURE);
    }
    else {
        cpids[1] = fork();
        if(cpids[1] == -1){
            exit(EXIT_FAILURE);
        }

        if(cpids[1] == 0){
            char serv2[] = "/opt/daemon-p3/server-2.py";
            char *serv2_argv[] = {serv2, NULL};
            char *serv2_envp[] = {NULL};
            execve(serv2, serv2_argv, serv2_envp);
            exit(EXIT_FAILURE);
        }
        else {
            cpids[2] = fork();
            if(cpids[2] == -1){
                exit(EXIT_FAILURE);
            }

            if(cpids[2] == 0){
                char serv3[] = "/opt/daemon-p3/server-3.py";
                char *serv3_argv[] = {serv3, NULL};
                char *serv3_envp[] = {NULL};
                execve(serv3, serv3_argv, serv3_envp);
                exit(EXIT_FAILURE);
            }
            else {
                int res, i;

                struct sigaction act;
                act.sa_sigaction = sigterm_handler;
                act.sa_flags = SA_SIGINFO;
                res = sigaction(SIGTERM, &act, NULL);
                if(res == -1){
                    for(i = 0; i < 3; i++){
                        kill(cpids[i], SIGTERM);
                    }
                    exit(EXIT_FAILURE);
                }

                int wstatus;
                pid_t terminated_pid = wait(&wstatus);
                if(terminated_pid == -1){
                    exit(EXIT_FAILURE);
                }

                if(!cpids_lock){
                    cpids_lock = true;

                    for(i = 0; i < 3; i++){
                        if(cpids[i] == terminated_pid) continue;
                        res = kill(cpids[i], SIGTERM);
                        if(res == -1){
                            exit(EXIT_FAILURE);
                        }
                    }
                }

                exit(EXIT_SUCCESS);
            }
        }
    }
}

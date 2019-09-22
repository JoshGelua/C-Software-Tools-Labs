#include <signal.h>
#include <stdio.h>
int x = 5;

void handler(int sig) {
    x += 3;
    printf("inside %d ", x);
}

int main() {
    printf("start ");
    //                             POSITION A
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT,&act,NULL);
    //                             POSITION B
    x += 2;
    raise (SIGINT);
    //                             POSITION C
    printf("outside %d", x);
    return 0;

}

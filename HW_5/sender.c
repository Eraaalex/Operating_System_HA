#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int receiver_pid;
int current_bit = 0;
int num_to_send;

void handler(int sig) {
    if (sig == SIGUSR1) {
        current_bit++;
        if (current_bit < 32) {
            if ((num_to_send >> current_bit) & 1){
                kill(receiver_pid, SIGUSR2);
            }
            else{
                kill(receiver_pid, SIGUSR1);
            }
        } else {
            printf("[Sender] Result number: %d\n", num_to_send);
            exit(0);
        }
    }
}

int main() {
    printf("[Sender] PID: %d\n", getpid());
    printf("Please, enter the pid of the client: ");
    scanf("%d", &receiver_pid);
    printf("[Sender] Enter an integer decimal number to send: ");
    scanf("%d", &num_to_send);
    signal(SIGUSR1, handler);

    if (num_to_send & 1)
        kill(receiver_pid, SIGUSR2);
    else
        kill(receiver_pid, SIGUSR1);

    while (1) {
        pause();
    }

    return 0;
}
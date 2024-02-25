#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int cleint_pid;

void signal_handler(int sig) {
    static int bit_count = 0;
    static int cleint_number = 0;
    
    if (sig == SIGUSR1) {
        cleint_number |= (1 << bit_count);
    }
    
    bit_count++;
    
    if (bit_count == sizeof(int) * 8) {
        printf("[Sender] Sending number %d to receiver...\n", cleint_number);
        kill(cleint_pid, SIGUSR1);
        exit(0);
    }
    
    kill(cleint_pid, SIGUSR2);
}

int main() {
    printf("[Sender] PID: %d\n", getpid());
    printf("Please enter the PID of the client: ");
    scanf("%d", &cleint_pid);
    
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    
    int number;
    printf("Enter an integer decimal number: ");
    scanf("%d", &number);
    
    for (int i = 0; i < sizeof(int) * 8; i++) {
        if ((number >> i) & 1) {
            kill(cleint_pid, SIGUSR1);
        } else {
            kill(cleint_pid, SIGUSR2);
        }
        usleep(100000);
    }
    
    printf("[Sender] Number sent to receiver.\n");
    
    return 0;
}

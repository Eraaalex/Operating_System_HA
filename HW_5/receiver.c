#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int sig) {
    static int bit_count = 0;
    static int received_number = 0;
    
    if (sig == SIGUSR1) {
        received_number |= (1 << bit_count);
    }
    
    bit_count++;
    
    if (bit_count == sizeof(int) * 8) {
        printf("[Receiver] Received number: %d\n", received_number);
        exit(0);
    }
}

int main() {
    printf("[Receiver] PID: %d\n", getpid());
    printf("[Receiver] Please enter the PID of the sender: ");
    int server_pid;
    scanf("%d", &server_pid);
    
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    
    printf("[Receiver] Waiting...\n");
    
    while(1) {
        pause();
    }
    
    return 0;
}

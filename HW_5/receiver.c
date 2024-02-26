#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int sender_pid;
int received_num = 0;
int current_bit = 0;

void process_SIGUSR1(int signal) {
    received_num |= (0 << current_bit);
    current_bit++;
    kill(sender_pid, SIGUSR1);
}


void process_SIGUSR2(int signal) {
    received_num |= (1 << current_bit);
    current_bit++;
    kill(sender_pid, SIGUSR1);
}

int main() {
    printf("[Receiver] PID: %d\n", getpid());
    printf("Input sender PID: ");
    scanf("%d", &sender_pid);

    signal(SIGUSR1, process_SIGUSR1);
    signal(SIGUSR2, process_SIGUSR2);

    printf("[Receiver] Waiting...\n");

    while (current_bit < 32) {
        pause();
    }

    printf("\n");

    printf("[Receiver] Result number: %d\n", received_num);  // Выводим полученное число

    return 0;
}
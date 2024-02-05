#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <dirent.h>

typedef unsigned long long u64;

u64 fibonacci(u64 n) {
    unsigned long long first = 0, second = 1, tmp;
    if (n == 0) return 0;
    for(int i = 2; i < n; ++i) {
        if (first + second < first) {
            printf("Fibonacci overflow!\n");
            return 0;
        }
        tmp = first + second;
        first = second;
        second = tmp;
    }
    return second;
}

u64 factorial(u64 n) {
    u64 result = 1;

    for (u64 i = 2; i <= n; ++i) {
        if (result*i < result) {
            printf("Factorial overflow!\n");
            return 0;
        }
        result *= i;
    }

    return result;
}


void displayDirectoryContents() {
    DIR *directory;
    struct dirent *dir;

    directory = opendir(".");
    if (directory == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    printf("Contents of the current directory:\n");
    while ((dir = readdir(directory)) != NULL) {
        printf("%s\n", dir->d_name);
    }

    closedir(directory);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Using: ./program <argument>\n");
        return 1;
    }

    int input = atoi(argv[1]);

    pid_t pid, ppid, chpid;
    chpid = fork();
    pid  = getpid();
    ppid = getppid();

    if(chpid <= -1) {
        printf("Incorrect fork syscall\n");
    } else if (chpid == 0) {
        printf("I am child. ");
        printf("My pid = %d, my parent is %d and I have no child, factorial = %llu\n",
               (int)pid, (int)ppid, factorial(input) );

    } else {
        printf("I am parent. ");
        printf("My pid = %d, my parent is %d, my child is %d, fibonacci = %llu \n",
               (int)pid, (int)ppid, (int)chpid,fibonacci(input) );

        wait(NULL);

        pid_t dirDisplayPid = fork();

        printf("[Display directory] I am child. ");
        printf("My pid = %d, my parent is %d and I have no child\n",
               (int)getpid(), (int)getppid() );
        if (dirDisplayPid == -1) {
            printf("Incorrect fork syscall\n");
        } else if (dirDisplayPid == 0) {

            displayDirectoryContents();
        } else {

            wait(NULL);
        }


    }
    return 0;
}



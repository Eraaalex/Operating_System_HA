#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_KEY 1234

typedef struct {
    int data;
    volatile int flag;
} shared_data;

// Объявление глобальной переменной для хранения ID разделяемой памяти
int shmid;

void cleanup(int sig) {
    // Получаем доступ к разделяемой памяти
    shared_data *data = (shared_data *)shmat(shmid, NULL, 0);
    if (data != (shared_data *)(-1)) {
        // Отсоединяемся от сегмента разделяемой памяти
        shmdt((void *) data);
        // Удаляем сегмент разделяемой памяти
        shmctl(shmid, IPC_RMID, NULL);
    }
    printf("Server shutdown gracefully.\n");
    exit(0); // Завершаем работу сервера
}

int main() {
    // Регистрируем обработчик сигнала
    signal(SIGINT, cleanup);

    // Создаем сегмент разделяемой памяти
    shmid = shmget(SHM_KEY, sizeof(shared_data), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shared_data *data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (shared_data *)(-1)) {
        perror("shmat");
        exit(1);
    }

    data->flag = 0; // Инициализация флага

    // Основной цикл сервера
    while (1) {
        while (data->flag == 0) {
            sleep(1);
        }
        if (data->data == -1) {
            printf("Termination signal received. Shutting down.\n");
            break;
        }
        printf("Received: %d\n", data->data);
        data->flag = 0;
    }

    cleanup(0); // Вызываем функцию очистки ресурсов

    return 0;
}

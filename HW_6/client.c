#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define SHM_KEY 1234
typedef struct {
    int data;
    volatile int flag; // 0 - данные не готовы, 1 - данные готовы для чтения
} shared_data;


int main() {
    int shmid;
    shared_data *data;

    // Получаем доступ к сегменту разделяемой памяти
    shmid = shmget(SHM_KEY, sizeof(shared_data), 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Прикрепляем сегмент разделяемой памяти
    data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (shared_data *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Инициализируем генератор случайных чисел
    srand(time(NULL));

    for (int i = 0; i < 10; ++i) { // Ограничим количество чисел для примера
        while (data->flag == 1) {
            sleep(1); // Ожидаем, пока сервер не прочитает предыдущее число
        }

        // Генерация случайного числа и запись в разделяемую память
        data->data = rand() % 100; // Случайное число в пределах от 0 до 99
        data->flag = 1; // Устанавливаем флаг готовности данных
        printf("Sent: %d\n", data->data);
    }

    // Сигнализируем серверу о завершении работы
    while (data->flag == 1) {
        sleep(1); // Ожидаем, пока сервер не прочитает последнее число
    }
    data->data = -1; // Специальное значение для завершения сервера
    data->flag = 1;

    // Отсоединяемся от сегмента разделяемой памяти
    shmdt((void *) data);

    return 0;
}

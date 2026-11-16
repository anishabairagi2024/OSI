
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main() {
    int key = IPC_PRIVATE;

    // Create semaphore
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget error");
        return 1;
    }

    printf("1. Semaphore created. ID: %d\n", semid);

    // Initialize semaphore to 1
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl init error");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    printf("2. Semaphore initialized to 1.\n");

    struct sembuf op;

    op.sem_num = 0;
    op.sem_flg = SEM_UNDO;
    op.sem_op = -1;

    // Lock semaphore
    printf("3. Locking semaphore...\n");

    if (semop(semid, &op, 1) == -1) {
        perror("semop lock error");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    printf("4. INSIDE CRITICAL SECTION! (Sleeping for 2 seconds...)\n");

    sleep(2);

    // Unlock semaphore
    op.sem_op = 1;

    printf("5. Unlocking semaphore...\n");

    if (semop(semid, &op, 1) == -1) {
        perror("semop unlock error");
        semctl(semid, 0, IPC_RMID);
        return 1;
    }

    printf("6. Semaphore unlocked successfully.\n");

    // Delete semaphore
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl delete error");
        return 1;
    }

    printf("7. Semaphore deleted successfully.\n");

    return 0;
}

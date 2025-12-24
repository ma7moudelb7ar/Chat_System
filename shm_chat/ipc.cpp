#include "ipc.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdexcept>

int create_or_get_shm(key_t key, size_t size){
    int shmid = shmget(key, size, IPC_CREAT | 0666);
    if(shmid < 0) throw std::runtime_error("shmget failed");
    return shmid;
}

void* attach_shm(int shmid){
    void* addr = shmat(shmid, nullptr, 0);
    if(addr == (void*)-1) throw std::runtime_error("shmat failed");
    return addr;
}

void detach_shm(void* addr){
    shmdt(addr);
}

int create_or_get_sem(key_t key, int nsems){
    int semid = semget(key, nsems, IPC_CREAT | 0666);
    if(semid < 0) throw std::runtime_error("semget failed");
    return semid;
}

static void sem_op(int semid, int idx, int val){
    sembuf op{};
    op.sem_num = idx;
    op.sem_op = val;
    op.sem_flg = 0;
    if(semop(semid, &op, 1) < 0)
        throw std::runtime_error("semop failed");
}

void sem_p(int semid, int idx){ sem_op(semid, idx, -1); }
void sem_v(int semid, int idx){ sem_op(semid, idx, +1); }

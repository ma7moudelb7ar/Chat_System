#pragma once
#include <sys/types.h>

int create_or_get_shm(key_t key, size_t size);
void* attach_shm(int shmid);
void detach_shm(void* addr);

int create_or_get_sem(key_t key, int nsems);
void sem_p(int semid, int idx); // wait / down
void sem_v(int semid, int idx); // signal / up

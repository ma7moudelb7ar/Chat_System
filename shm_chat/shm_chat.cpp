#include <iostream>
#include <cstring>
#include <csignal>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "../common/protocol.h"
#include "../common/utils.h"
#include "ipc.h"

#define MAX_CLIENTS 10

/*
Semaphore:
0 = mutex (protect shared memory)
*/

struct SharedRegion {
    int initialized;               // ★ مهم
    int write_idx;
    int read_idx[MAX_CLIENTS];
    Message buf[SHM_CAPACITY];
};

static std::atomic<bool> running(true);

void on_sigint(int) {
    running = false;
}

/* ================= Receiver Thread ================= */
void receiver_loop(int client_id,
    const std::string& username,
    SharedRegion* region,
    int semid)
{
    while (running) {
        sem_p(semid, 0); // mutex

        while (region->read_idx[client_id] != region->write_idx) {
            Message msg = region->buf[region->read_idx[client_id]];
            region->read_idx[client_id] =
                (region->read_idx[client_id] + 1) % SHM_CAPACITY;

            // اطبع أي رسالة مش جاية من نفس الـ client
            if (msg.sender_id != client_id) {
                std::cout << format_message(msg)
                    << std::endl << std::flush;
            }
        }

        sem_v(semid, 0); // mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main(int argc, char** argv) {

    // ★ مهم جدًا علشان GUI يشوف الـ stdout فورًا
    setvbuf(stdout, NULL, _IONBF, 0);

    if (argc < 3) {
        std::cerr << "Usage: shm_chat <client_id 0-" << MAX_CLIENTS - 1
            << "> <username>\n";
        return 1;
    }

    int client_id = std::stoi(argv[1]);
    std::string username = argv[2];

    if (client_id < 0 || client_id >= MAX_CLIENTS) {
        std::cerr << "Invalid client_id\n";
        return 1;
    }

    signal(SIGINT, on_sigint);

    key_t shm_key = 0x1111;
    key_t sem_key = 0x2222;

    try {
        /* -------- Shared Memory -------- */
        int shmid = create_or_get_shm(shm_key, sizeof(SharedRegion));
        auto* region = static_cast<SharedRegion*>(attach_shm(shmid));

        /* -------- Semaphore -------- */
        int semid = create_or_get_sem(sem_key, 1);
        semctl(semid, 0, SETVAL, 1);

        /* -------- Safe Initialization (ONCE) -------- */
        sem_p(semid, 0);

        if (region->initialized != 1) {
            region->initialized = 1;
            region->write_idx = 0;

            for (int i = 0; i < MAX_CLIENTS; ++i)
                region->read_idx[i] = 0;

            std::memset(region->buf, 0, sizeof(region->buf));
        }

        sem_v(semid, 0);

        std::cout << "تيم قد الدنيا 💪" << std::endl;

        /* -------- Receiver Thread -------- */
        std::thread receiver(
            receiver_loop,
            client_id,
            username,
            region,
            semid
        );

        /* -------- Send Loop -------- */
        while (running) {
            std::string line;
            std::getline(std::cin, line);

            if (!running || line == "/quit") {
                running = false;
                break;
            }

            Message out{};
            out.sender_id = client_id;
            copy_cstr(out.sender, MAX_NAME, username);
            copy_cstr(out.text, MAX_TEXT, line);
            out.timestamp_ms = now_ms();

            sem_p(semid, 0);
            region->buf[region->write_idx] = out;
            region->write_idx =
                (region->write_idx + 1) % SHM_CAPACITY;
            sem_v(semid, 0);
        }

        receiver.join();
        detach_shm(region);
    }
    catch (const std::exception& e) {
        std::cerr << "SHM error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

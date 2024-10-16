#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

std::mutex m1, m2;

/**
 * @brief Función que representa el comportamiento del hilo 1.
 *
 * Usa std::scoped_lock para adquirir ambos mutexes de manera segura.
 */
void thread1()
{
    scoped_lock lock(m1, m2); // Bloqueo atómico de m1 y m2
    printf("Thread 1 locked m1 and m2\n");
}

/**
 * @brief Función que representa el comportamiento del hilo 2.
 *
 * Usa std::scoped_lock para adquirir ambos mutexes de manera segura.
 */
void thread2()
{
    scoped_lock lock(m1, m2); // Bloqueo atómico de m1 y m2
    printf("Thread 2 locked m1 and m2\n");
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}

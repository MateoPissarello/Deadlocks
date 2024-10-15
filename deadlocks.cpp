#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

std::mutex m1, m2;

/**
 * @brief Función que representa el comportamiento del hilo 1.
 *
 * Esta función bloquea el mutex m1 y luego intenta bloquear el mutex m2.
 * Si otro hilo bloquea m2 antes de que este hilo lo haga y luego intenta
 * bloquear m1, se producirá un interbloqueo (deadlock).
 */
void thread1()
{
    m1.lock();
    printf("Thread 1 locked m1\n");

    // Se añade una ventana de tiempo para aumentar la probabilidad de un deadlock
    this_thread::sleep_for(chrono::milliseconds(100));

    m2.lock();
    printf("Thread 1 locked m2\n");

    m2.unlock();
    m1.unlock();
}

/**
 * @brief Función que representa el comportamiento del hilo 2.
 *
 * Esta función bloquea el mutex m2 y luego intenta bloquear el mutex m1.
 * Si otro hilo bloquea m1 antes de que este hilo lo haga y luego intenta
 * bloquear m2, se producirá un interbloqueo (deadlock).
 */
void thread2()
{
    m2.lock();
    printf("Thread 2 locked m2\n");

    // Se añade una ventana de tiempo para aumentar la probabilidad de un deadlock
    this_thread::sleep_for(chrono::milliseconds(100));

    m1.lock();
    printf("Thread 2 locked m1\n");

    m1.unlock();
    m2.unlock();
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}

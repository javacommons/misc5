#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

void worker(std::mutex &mtx)
{
    for (int i = 0; i < 10; i++)
    {
        std::lock_guard<std::mutex> lock(mtx);
        for (int j = 0; j < 10; j++)
        {
            putchar('#');
        }
        putchar('\n');
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::lock_guard<std::mutex> lock(mtx);
}

int main(void)
{
    std::mutex mtx;
    std::thread *th = new std::thread(worker, std::ref(mtx));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    for (int i = 0; i < 10; i++)
    {
        std::lock_guard<std::mutex> lock(mtx);
        for (int j = 0; j < 10; j++)
        {
            putchar('*');
        }
        putchar('\n');
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    th->join();
    delete th;
    return 0;
}

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>

std::condition_variable cv;
std::mutex mtx; // This mutex is used for three purposes:
                // 1) to synchronize accesses to i
                // 2) to synchronize accesses to std::cerr
                // 3) for the condition variable cv

std::condition_variable cv2;

int i = 0;

void waits()
{
    {
        std::unique_lock<std::mutex> lk(mtx);
        std::cerr << "Central thread: Waiting... \n";
        cv.wait(lk, []
                { return i == 3; });
        std::cerr << "Central thread: Finished merging. i == " << i << "\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    cv2.notify_all();
}

void signals(int id)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lk(mtx);
        i++;
        std::cerr << "Thread " << id << ": Notifying " << i << std::endl;
    }
    cv.notify_one();

    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    {
        std::unique_lock<std::mutex> lk(mtx);
        std::cerr << "Thread " << id << ": Waiting... \n";
        cv2.wait(lk);
        std::cerr << "Thread " << id << ": finished distribution.\n";
    }
}

int main()
{
    std::thread t1(signals, 0), t2(signals, 1), t3(signals, 2), t4(waits);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
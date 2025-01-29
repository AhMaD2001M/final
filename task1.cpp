#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

class Intersection
{
public:
    Intersection(int capacity) : capacity(capacity), cars_inside(0) {}

    void enter(int car_id)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]()
                { return cars_inside < capacity; });

        cars_inside++;
        cout << "Car " << car_id << " entered the intersection. Cars inside: " << cars_inside << endl;
    }

    void leave(int car_id)
    {
        unique_lock<mutex> lock(mtx);
        cars_inside--;
        cout << "Car " << car_id << " left the intersection. Cars inside: " << cars_inside << endl;
        cv.notify_all();
    }

private:
    int capacity;
    int cars_inside;
    mutex mtx;
    condition_variable cv;
};

void car(Intersection &intersection, int car_id)
{
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    intersection.enter(car_id);
    this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
    intersection.leave(car_id);
}

int main()
{
    const int num_cars = 10;
    const int intersection_capacity = 2;
    Intersection intersection(intersection_capacity);

    thread cars[num_cars];
    for (int i = 0; i < num_cars; ++i)
    {
        cars[i] = thread(car, ref(intersection), i + 1);
    }

    for (int i = 0; i < num_cars; ++i)
    {
        cars[i].join();
    }

    return 0;
}

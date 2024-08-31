#include "Scheduler.h"
#include <iostream>

int main() {
    Scheduler new_scheduler(4);  // Example with 4 threads

    new_scheduler.setSchedulingAlgorithm(Scheduler::SchedulingAlgorithm::FCFS);

    // Example tasks
    new_scheduler.addTask(Task(1, 1, std::chrono::milliseconds(500), []{ std::cout << "Task 1 executed\n"; }));
    new_scheduler.addTask(Task(2, 2, std::chrono::milliseconds(300), []{ std::cout << "Task 2 executed\n"; }));
    new_scheduler.addTask(Task(3, 3, std::chrono::milliseconds(200), []{ std::cout << "Task 3 executed\n"; }));

    new_scheduler.start();

    std::this_thread::sleep_for(std::chrono::seconds(15));

    new_scheduler.stop();

    return 0;
}
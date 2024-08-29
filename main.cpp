#include "Task.h"
#include "Scheduler.h"
#include "FCFSScheduler.h"
#include "SJNScheduler.h"
#include "PriorityScheduler.h"
#include "RoundRobinScheduler.h"

int main() {
    size_t numThreads = 4; // Configurable number of threads
    std::chrono::milliseconds timeQuantum(100); // Time quantum for Round-Robin

    FCFSScheduler fcfsScheduler(numThreads);
    SJNScheduler sjnScheduler(numThreads);
    PriorityScheduler priorityScheduler(numThreads);
    RoundRobinScheduler rrScheduler(numThreads, timeQuantum);

    // Add tasks to the desired scheduler
    fcfsScheduler.addTask(Task(1, std::chrono::milliseconds(500)));
    sjnScheduler.addTask(Task(2, std::chrono::milliseconds(300)));
    priorityScheduler.addTask(Task(3, std::chrono::milliseconds(700)));
    rrScheduler.addTask(Task(4, std::chrono::milliseconds(200)));

    // Execute tasks (for Round-Robin)
    rrScheduler.executeTasks();

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Allow time for tasks to complete

    return 0;
}

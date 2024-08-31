#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Task.h"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class Scheduler {
public:
    Scheduler(int numThreads);

    void addTask(const Task& task);
    void removeTask(int taskId);
    void start();
    void stop();

    enum class SchedulingAlgorithm {
        FCFS,
        SJN,
        Priority,
        RoundRobin
    };

    void setSchedulingAlgorithm(SchedulingAlgorithm algorithm);
    void setTimeQuantum(int quantum);
    bool compareTaskPriority (Task const& t1, Task const& t2);
    bool compareTaskDuration (Task const& t1, Task const& t2);

private:
    void executeTasks();
    std::vector<std::thread> threads;
    std::atomic<bool> running;
    std::mutex queueMutex;
    std::condition_variable cv;

    std::queue<Task> taskQueue; // For FCFS
    std::vector<Task> SJNQueue; // For SJN
    std::queue<Task> RRQueue; // For RR
    std::priority_queue<Task, std::vector<Task>, std::function<bool(Task, Task)>> priorityQueue; // For Priority Scheduling

    SchedulingAlgorithm currentAlgorithm;
    int timeQuantum;

};

#endif // SCHEDULER_H
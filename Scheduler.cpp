#include "Scheduler.h"
#include <algorithm>
#include <iostream>

Scheduler::Scheduler(int numThreads) : running(false), currentAlgorithm(SchedulingAlgorithm::FCFS), timeQuantum(100) {
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(&Scheduler::executeTasks, this);
    }
}

void Scheduler::addTask(const Task& task) {
    std::lock_guard<std::mutex> lock(queueMutex);
    switch (currentAlgorithm) {
        case SchedulingAlgorithm::FCFS:
            taskQueue.push(task);
            break;
        case SchedulingAlgorithm::SJN:
            SJNQueue.push_back(task);
            std::sort(SJNQueue.begin(), SJNQueue.end()); // Sort by execution time
            break;
        case SchedulingAlgorithm::Priority:
            priorityQueue.push(task);
            break;
        case SchedulingAlgorithm::RoundRobin:
            RRQueue.push(task);
            break;
        default:
            taskQueue.push(task);
            break;
    }
    cv.notify_one();
}

void Scheduler::removeTask(int taskId) {
    std::lock_guard<std::mutex> lock(queueMutex);
    // Implement task removal logic based on taskId
}

void Scheduler::start() {
    running.store(true);
}

void Scheduler::stop() {
    running.store(false);
    cv.notify_all();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Scheduler::setSchedulingAlgorithm(SchedulingAlgorithm algorithm) {
    currentAlgorithm = algorithm;
}

void Scheduler::executeTasks() {
    while (running.load()) {
        Task task(0, 0, std::chrono::milliseconds(0), []{});
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this] { return !taskQueue.empty() || !SJNQueue.empty() || !priorityQueue.empty() || !RRQueue.empty() || !running.load(); });
            if (!running.load()) break;

            switch (currentAlgorithm) {
                case SchedulingAlgorithm::FCFS:
                    task = taskQueue.front();
                    taskQueue.pop();
                    lock.unlock();
                    std::cout << "Executing with FCFS .. Task ID: " << task.getId() << std::endl;
                    break;
                case SchedulingAlgorithm::SJN:
                    task = SJNQueue.front();
                    SJNQueue.erase(SJNQueue.begin());
                    lock.unlock();
                    std::cout << "Executing with SJN .. Task ID: " << task.getId() << std::endl;
                    break;
                case SchedulingAlgorithm::Priority:
                    task = priorityQueue.top();
                    priorityQueue.pop();
                    lock.unlock();
                    std::cout << "Executing with Priority .. Task ID: " << task.getId() << std::endl;
                    break;
                case SchedulingAlgorithm::RoundRobin:
                    task = RRQueue.front();
                    RRQueue.pop();
                    break;
                default:
                    task = taskQueue.front();
                    taskQueue.pop();
                    break;
            }
        }
        auto duration = std::min(task.getDuration(), std::chrono::milliseconds(timeQuantum));
        task.execute();
        std::this_thread::sleep_for(duration);

        if (currentAlgorithm == SchedulingAlgorithm::RoundRobin && duration < task.getDuration()) {
            std::lock_guard<std::mutex> lock(queueMutex);
            RRQueue.push(Task(task.getId(), task.getPriority(), task.getDuration() - duration, task.getTaskFunction()));
        }
    }
}

void Scheduler::setTimeQuantum(int quantum) {
    timeQuantum = quantum;
}

bool Scheduler::compareTaskPriority (Task const& t1, Task const& t2) {
    return t1.getPriority() < t2.getPriority();
}

bool Scheduler::compareTaskDuration (Task const& t1, Task const& t2) {
    return t1.getDuration() < t2.getDuration();
}
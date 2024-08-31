#ifndef TASK_H
#define TASK_H

#include <functional>
#include <chrono>

class Task {
public:
    Task(int task_id, int task_priority, std::chrono::milliseconds task_duration, std::function<void()> taskFunction);
    ~Task(); //destructor

    int getId() const;
    int getPriority() const;
    std::chrono::milliseconds getDuration() const;
    std::function<void()> getTaskFunction() const;
    void execute();

    // For SJN, we need to compare execution times
    bool operator<(const Task& other) const {
        return getDuration() > other.getDuration(); // For SJN (min-heap)
    }

private:
    int task_id;
    int task_priority;
    std::chrono::milliseconds task_duration;
    std::function<void()> taskFunction;
};

#endif // TASK_H
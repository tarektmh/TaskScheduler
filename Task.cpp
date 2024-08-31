#include "Task.h"

Task::Task(int task_id, int task_priority, std::chrono::milliseconds task_duration, std::function<void()> taskFunction)
    : task_id(task_id), task_priority(task_priority), task_duration(task_duration), taskFunction(taskFunction) {}

Task::~Task() {
    //implementation of task class destructor
}

int Task::getId() const {
    return task_id;
}

int Task::getPriority() const {
    return task_priority;
}

std::chrono::milliseconds Task::getDuration() const {
    return task_duration;
}

std::function<void()> Task::getTaskFunction() const {
    return taskFunction; 
}

void Task::execute() {
    taskFunction();
}
#ifndef TASK_H
#define TASK_H

#include <string>
#include <functional>

class Task {
public:
   using TaskHandler=std::function<void()>;
 
    Task(std::string name,TaskHandler handler);
    explicit Task(TaskHandler handler);
    ~Task()=default;
    
    const std::string& getName() const;
    void execute();
    

    Task(const Task&)=delete;
    Task& operator=(const Task&)=delete;
    Task(Task&&)=default;
    Task& operator=(Task&&)=default;

    private:
      std::string name;
      TaskHandler handler;
      static int taskNum;

};

#endif

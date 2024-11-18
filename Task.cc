#include "Task.h"
#include <iostream>

int Task::taskNum = 0;

  Task::Task(std::string name,TaskHandler handler)
          :name(std::move(name)),handler(std::move(handler))
          {
            ++taskNum;
          }
    Task::Task(TaskHandler handler)
    :Task("Unnamed Task",std::move(handler)){}
    
    const std::string&  Task::getName() const{
        return name;
    }
    void Task::execute(){
        if(handler){
            handler();
        }
        else{
            std::cerr<<"Error: Task handler is not set."<<std::endl;
        }
        --taskNum;
    }
    

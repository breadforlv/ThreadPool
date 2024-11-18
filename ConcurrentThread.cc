#include "ConcurrentThread.h"
#include <chrono>
#include <thread>
#include <iostream>

ConcurrentThread::ConcurrentThread(int id)
:threadId(id){}

void ConcurrentThread::operator()(){
    //excute task
    std::cout<<"Thread "<<threadId<<"is starting.\n";
    
   //excute long time task
   std::this_thread::sleep_for(std::chrono::seconds(2));

   std::cout<<"Thread "<<threadId<<"has finished.\n";

}
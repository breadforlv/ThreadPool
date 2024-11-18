#ifndef CONCURRENTTHREAD
#define CONCURRENTTHREAD



class ConcurrentThread{
    public:
        explicit ConcurrentThread(int id);
        void operator()();
    private:
        int threadId;
    
};

#endif
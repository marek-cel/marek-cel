#include <iostream>

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

class ThreadBase
{
public:

    ThreadBase() = delete;
    ThreadBase(const ThreadBase&) = delete;
    ThreadBase& operator=(const ThreadBase&) = delete;
    ThreadBase(ThreadBase&&) = delete;
    ThreadBase& operator=(ThreadBase&&) = delete;

    virtual ~ThreadBase()
    {
        quit();
    }

    ThreadBase(const char* name, int interval)
    {
        _name = name;
        _interval = interval;
    }

    void start()
    {
        if (!_thread)
        {
            _isRunning = true;
            _thread = std::make_unique<std::thread>(&ThreadBase::run, this);
        }
    }

    void quit()
    {
        _isRunning = false;

        if (_thread && _thread->joinable())
        {
            _thread->join();
        }
        _thread = nullptr;
    }

    void step()
    {
        std::cout << _name << " " << time(nullptr) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(_interval));
    }

private:

    std::unique_ptr<std::thread> _thread;

    std::atomic<bool> _isRunning = false;

    std::string _name;
    unsigned int _interval;

    void run()
    {
        while (_isRunning)
        {
            step();
        }
    }
};

int main()
{
    std::cout << __FILE__ << std::endl;
    std::cout << __cplusplus << std::endl;
    std::cout << std::endl;

    ThreadBase t1("t1", 1);
    ThreadBase t2("t2", 2);
    t1.start();
    t2.start();

    std::chrono::seconds delay(10);

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    std::this_thread::sleep_for(delay);
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    t1.quit();

    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    std::this_thread::sleep_for(delay);
    std::cout << __FILE__ << "(" << __LINE__ << ")" << std::endl;

    return 0;
}

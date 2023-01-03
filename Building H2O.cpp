#include <thread>

class H2O {
public:
    H2O() = default;
    
    void hydrogen(function<void()> releaseHydrogen) {
        auto lock = std::unique_lock{m_mutex};
        cv.wait(lock, [&]{ return m_state < 2; });
        
        releaseHydrogen();
        m_state++;

        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        auto lock = std::unique_lock{m_mutex};
        cv.wait(lock, [&]{ return m_state == 2; });
        
        releaseOxygen();
        m_state = 0;
        
        cv.notify_all();
    }
    
private:
    std::condition_variable cv;
    std:: mutex m_mutex;
    int m_state = 0;
};
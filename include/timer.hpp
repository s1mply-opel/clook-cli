#pragma once
#include <chrono>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>

class Timer {
public:
    using Clock = std::chrono::steady_clock;
    using Duration = std::chrono::duration<double>;
    using Callback = std::function<void()>;

    Timer();
    ~Timer();

    void setDuration(double seconds);
    void setCallback(Callback cb);

    void start();
    void stop() noexcept;
    void pause() noexcept;
    void resume();

    bool isRunning() const noexcept;
    bool isPaused() const noexcept;

    Duration getRemainingDuration();

private:
    std::atomic<bool> running{false};
    std::atomic<bool> paused{false};

    Duration duration{0.0};
    Duration elapsed{0.0};
    
    Callback onFinish{nullptr};
    std::thread worker;
    std::mutex mtx; 
};
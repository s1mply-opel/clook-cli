#include "timer.hpp"
#include <thread>

Timer::Timer() = default;
Timer::~Timer() { stop(); }

void Timer::setDuration(double seconds) {
    duration = Duration(seconds);
}

void Timer::setCallback(Callback cb) {
    std::lock_guard<std::mutex> lock(mtx);
    onFinish = std::move(cb);
}

void Timer::start() {
    std::lock_guard<std::mutex> lock(mtx);
    if (running) return;

    running = true;
    paused = false;
    elapsed = Duration(0);

    worker = std::thread([this] {
        auto startTime = Clock::now();
        
        while (running) {
            if (!paused) {
                auto now = Clock::now();
                elapsed = now - startTime;

                if (elapsed >= duration) {
                    running = false;
                    if (onFinish) onFinish();
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    worker.detach();
}

void Timer::pause() noexcept {
    if(running && !paused) {
        paused = true;
    }
}

void Timer::resume() {
    std::lock_guard<std::mutex> lock(mtx);
    if(running && paused) {
        paused = false;
        auto remaining = duration - elapsed;

        worker = std::thread([this, remaining] {
            auto startTime = Clock::now();
            while(running && !paused) {
                if((Clock::now() - startTime) >= remaining) {
                    running = false;
                    if(onFinish) onFinish();
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
        worker.detach();
    }
}

void Timer::stop() noexcept {
    running = false;
    paused = false;
}

bool Timer::isRunning() const noexcept {
    return running;
}

bool Timer::isPaused() const noexcept {
    return paused;
}

Timer::Duration Timer::getRemainingDuration() {
    return (duration - elapsed);
}
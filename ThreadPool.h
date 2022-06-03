#include <functional>
#include "MTQueue.h"
class ThreadPool {
  public:
    explicit ThreadPool(int num) {
        std::cout << num << std::endl;
        max_threads = num;

        for (int i = 0; i < max_threads; i++) {
            pool.push_back(std::thread([this] {
                while (true) {
                    /* code */
                    if (stopped && task_queue.empty()) {
                        return;
                    }

                    auto task = task_queue.pop();
                    task();
                }
            }));
        }
    }
    void create(std::function<void()> start) {
        // 作业要求3：如何让这个线程保持在后台执行不要退出？
        // 提示：改成 async 和 future 且用法正确也可以加分
        task_queue.push(start);
    }

    ~ThreadPool() {
        stopped = true;
        for (auto &&i : pool) {
            i.join();
        }
    }

  private:
    std::vector<std::thread> pool;
    MTQueue<std::function<void()>> task_queue;
    int max_threads;
    bool stopped = false;
};
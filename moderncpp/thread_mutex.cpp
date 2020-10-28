#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>

void test1()
{
    std::thread t([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "hello world." << std::endl;
    });
    t.join();
}

int v = 1;

void critical_section(int change_v)
{
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    // 执行竞争操作
    v = change_v;

    // 离开此作用域后 mtx 会被释放
}

int test_mutex()
{
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();

    std::cout << v << std::endl;
    return 0;
}

int test_future()
{
    // 将一个返回值为7的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return 7; });
    // 获得 task 的期物
    std::future<int> result = task.get_future(); // 在一个线程中执行 task
    std::cout << "waiting..." << std::endl;
    std::thread(std::move(task)).detach();
    result.wait(); // 在此设置屏障，阻塞到期物的完成
    // 输出执行结果
    std::cout << "done!" << std::endl
              << "future result is " << result.get() << std::endl;
    return 0;
}

void critical_section2(int change_v)
{
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // 执行竞争操作
    v = change_v;
    std::cout << v << std::endl;
    // 将锁进行释放
    lock.unlock();

    // 在此期间，任何人都可以抢夺 v 的持有权

    // 开始另一组竞争操作，再次加锁
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

int test_unique_lock()
{
    std::thread t1(critical_section2, 2), t2(critical_section2, 3);
    t1.join();
    t2.join();
    return 0;
}

#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

int test_condition_variable()
{
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false; // 通知信号

    // 生产者
    auto producer = [&]() {
        for (int i = 0;; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all(); // 此处也可以使用 notify_one
        }
    };
    // 消费者
    auto consumer = [&]() {
        while (true)
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified)
            { // 避免虚假唤醒
                cv.wait(lock);
            }
            // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 消费者慢于生产者
            lock.lock();
            while (!produced_nums.empty())
            {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    // 分别在不同的线程中运行
    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i)
    {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for (int i = 0; i < 2; ++i)
    {
        cs[i].join();
    }
    return 0;
}

int main()
{
    // test1();
    // test_mutex();
    // test_future();
    test_unique_lock();
    // test_condition_variable();
    return 0;
}
#include <iostream>
#include <boost/thread.hpp>

class TestCallable {
public:
  void operator()() {
    long long i {0};
    while(true) {
      std::cout << "Hello from thread " << boost::this_thread::get_id() << ", " << i << " times" << std::endl;
      boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
      i++;
    }
  }
};

int main()
{
  try
  {
    const TestCallable task1{};
    const TestCallable task2{};

    boost::thread t1(task1);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
    boost::thread t2(task2);

    t1.join();
    t2.join();
  }
  catch (std::exception& e)
  {
    std::printf("Exception: %s\n", e.what());
    return -1;
  }

  return 0;
}
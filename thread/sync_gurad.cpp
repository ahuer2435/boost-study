#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

boost::mutex mutex; 

void thread() 
{ 
  /*
  * boost::lock_guard是一个模板类， boost::mutex是一个对象类，可用于实例化模板类型，应该需要和mutex类型保持一致；
  * lock是一个对象，在此对象的构造函数和析构函数中分别调用boost::mutex类的lock和unlock方法，作用同sync_mutex文件。
  */
  /*
  * 从另一方面也可以看出一个对象的构造函数和析构函数的调用时机，在定义处调用构造函数，在作用域结束之后调用析构函数。
  */
  boost::lock_guard<boost::mutex> lock(mutex); 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    //boost::lock_guard<boost::mutex> lock(mutex); 
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
  } 
} 

int main() 
{ 
  boost::thread t1(thread); 
  boost::thread t2(thread); 
  t1.join(); 
  t2.join(); 
} 

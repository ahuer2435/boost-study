#include <boost/thread.hpp> 
#include <iostream> 
#include <stdio.h>
void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

boost::mutex mutex; 

void thread() 
{ 
  mutex.lock(); 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    //mutex.lock(); 
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
    //mutex.unlock(); 
  } 
  mutex.unlock(); 
} 

int main() 
{ 
  boost::thread t1(thread); 
  boost::thread t2(thread); 
  t1.join(); 
  t2.join(); 
  printf("mian end.\n");
} 

#include <boost/thread.hpp> 
#include <iostream> 
#include <stdio.h>

/*
*  boost::thread基础测试。
*/

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread() 
{ 
  //printf("in Thread.\n");
  std::cout << boost::this_thread::get_id() << std::endl; 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    std::cout << i << std::endl; 
  } 
} 

int main() 
{ 
  boost::thread t(thread); 	//在此开启一个新的线程，新线程中只有一个函数thread，函数返回时，则线程结束。
  //printf("in mian.\n");
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    std::cout << 900 << std::endl; 
  } 
  std::cout << boost::this_thread::get_id() << std::endl; 
  t.join(); 			//通过变量（对象）t可以操作线程thread，join函数表示在t所对应的线程结束之后，main线程再执行，之前会阻塞。
} 


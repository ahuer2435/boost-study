#include <boost/thread.hpp> 
#include <iostream> 
#include <stdio.h>
#include <time.h>

void wait(int seconds) 
{ 
  //boost::this_thread::sleep(boost::posix_time::seconds(seconds)); //2. 注掉try catch 只有包含中断点，才会响应中断，sleep函数本身就包含了中断点。
  sleep(seconds);							//3. 反面验证2
} 

void thread() 
{ 
//  try 						
  { 
    for (int i = 0; i < 5; ++i) 
    { 
      wait(1); 
      std::cout << i << std::endl; 
    } 
  } 
  //catch (boost::thread_interrupted&) 
  { 
      printf("cathe a interrupt.\n");
  } 
  printf("thread end.\n");
} 

int main() 
{ 
  boost::thread t(thread); 
  printf("in main.\n");
  wait(3); 
  printf("after 3s.\n");
  t.interrupt(); 			//1.利用变量t可以中断线程thread。
  printf("after interrupt.\n");
  t.join(); 
  printf("mian end.\n");
} 

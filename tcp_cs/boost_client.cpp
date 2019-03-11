//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_s;

    tcp::resolver resolver(io_s);
    tcp::resolver::query query(argv[1], "daytime");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_s);
    std::cout << "start connect..." << std::endl;
    boost::asio::connect(socket, endpoint_iterator);
    std::cout << "connected." << std::endl;

    for (;;)
    {
      boost::array<char, 128> buf;
      boost::system::error_code error;

      std::cout << "start raed." << std::endl;
      //size_t len = socket.read_some(boost::asio::buffer(buf), error);
      std::size_t len = boost::asio::read(socket,boost::asio::buffer(buf, 20));
      //if (error == boost::asio::error::eof){
        //std::cout << " eof." << std::endl;
        //break; // Connection closed cleanly by peer.
      //}
      //else if (error){
     if (error){
        std::cout << " error." << std::endl;
        throw boost::system::system_error(error); // Some other error.
      }

      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
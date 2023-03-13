//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0); // save the current time to a variable called now
  return ctime(&now); // returning the current time saved above
}

int main()
{
  try
  {
    boost::asio::io_context io_context; // making io_context variable containting information that data is sent between client and server

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13)); // prepares for connection to client

    while (true) // when request is received from client
    {
      tcp::socket socket(io_context); // creating socket to communicate with client
      acceptor.accept(socket); // accepts connection to client

      std::string message = make_daytime_string(); // calls timer function and stores the current time as a string called "message"

      boost::system::error_code ignored_error; // creates error code for system-specific errors
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error); // writes message (current time) to client
    }
  }
  catch (std::exception &e) // if error then run catch-function
  {
    std::cerr << e.what() << std::endl; // printing out the type of error that occured
  }

  return 0; // returns 0
}
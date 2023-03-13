//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp; // using tcp namespace

int main(int argc, char* argv[])
{
  try 
  {
    if (argc != 2) // checking for right argument, if not return string as error message
    {
      std::cerr << "Usage: client <host>" << std::endl; // error message
      return 1; // returning 1 and ending the function because of error
    }

    boost::asio::io_context io_context; // making io_context variable containting information that data is sent between client and server

    tcp::resolver resolver(io_context); // making a resolver based on the io_context made above
    tcp::resolver::results_type endpoints = // constructing a endpoint by using resolve function
      resolver.resolve(argv[1], "daytime"); // resolve function returns list of endpoints based on input query

    tcp::socket socket(io_context); // creating socket to communicate with server
    boost::asio::connect(socket, endpoints); // trying to establish connection with server through specified socket with our endpoints

    while(true) // if connection established then waiting for response
    {
      boost::array<char, 128> buf; // creating an array object
      boost::system::error_code error; // creating object that represents system-specific errors

      size_t len = socket.read_some(boost::asio::buffer(buf), error); // creates buffer that ensures too much data isn't received 

      if (error == boost::asio::error::eof) // checking for specific error
        break; // Connection closed cleanly by peer.
      else if (error) // if system-specific errors
        throw boost::system::system_error(error); // Some other error.

      std::cout.write(buf.data(), len); // printing out our message received from the server
    }
  }
  catch (std::exception& e) // if error then run catch-function
  {
    std::cerr << e.what() << std::endl; // printing out the type of error that occured
  }

  return 0; // returns 0
}


/***********************************************************
 * EZWIN2
 *
 * Name:      ezsocket.h
 * version:   0.1
 * date:      3 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 * NOTE: ezsocket is my oldest class, being around before I even
 * decided to start the ezwin project.
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezsocket_h

#define ezsocket_h

#ifndef USING_WINDOWS
 #ifdef __WIN32__
    #define USING_WINDOWS
 #else
    #ifdef  WIN32
      #define USING_WINDOWS 
    #endif
 #endif
#endif

#include <ezwin.h>

#ifndef USING_WINDOWS
 #include <netinet/in.h>
#else

 #include <string>
 #include <winsock.h> 
#endif



/**
 * @short simple TCP socket implementation
 * @author John Donoghue <donoghue@chariot.net.au>
 * @copyright 2000
 * @version 0.2
 *
 * Provides a basic c++ implementation of the TCP socket
 * functionality for creating a TCP server and clients,
 * both in windows and in UNIX..
 */
class DLL_EXP EZSocket
{
   private:
      /** 
       * the raw socket handle 
       */
      int sock;
      /**
       * the destinatation socket address
       */
      struct sockaddr_in sockin;
      /**
       * the src socket address
       */
      struct sockaddr_in srcsockin;

      /**
       * flag for whether this socket is a server or a
       * client
       */
      bool isserver;
      /**
       * flag for if winsock was required and successfully loaded
       */
      bool load_winsock;

   public:

      /**
       * create the server listener
       *
       * @param _port the port to listen on
       * @exception  const char * string for error that occured
       */
      EZSocket(int port);

      /**
       * create the a socket for  
       *
       * @param _ip the string holding the ipnumber or name of server to
       *        connect to.
       * @param _port the port to connect to
       * @exception const char * string for error that occured
       */ 
      EZSocket(const char *_ip,int _port); 

      /**
       * deconstructor - closes and removes the socket
       */
      ~EZSocket();

      /**
       * get the raw opened listen sock
       * @returns -1 if no socket was opened
       *          the socket descriptor is returned if the socket was created
       */
      int getSocket() { return sock; }

      /**
       * write a null terminated string to the socket ( but not the null byte ).
       *
       * This is a convenience function for the writeData function.
       *
       * @param _text the null terminated string to write to the socket.
       * @return the number of bytes written
       */
      int writeText(const char *_text);
      
      /**
       * write specified data through the socket.
       *
       * @param _buffer the buffer to write data from
       * @param _sz the number of bytes to write from the buffer
       *
       * @return the number of bytes written - may be negative in the case of an
       * error
       */
      int writeData(const void *_buffer,unsigned long _sz);

      /**
       * read up to _sz bytes of data from socket.
       *
       * @param _buffer the buffer to read data to
       * @param _sz the number of bytes to read to the buffer
       *
       * @return the number of byes read
       */
      int readData(void *_buffer,unsigned long _sz);

      /**
       * peek specified data from socket without actually removing it from
       * the queue
       *
       * @param _buffer the buffer to read data to
       * @param _sz the number of bytes to read to the buffer
       *
       * @return the number of bytes read
       */
      int peekData(void *_buffer,unsigned long _sz);

      /**
       * get the full specified data from the socket
       * This function will not return until the number of bytes is read or an
       * error occurs
       *
       * @param _buffer the buffer to read data to
       * @param _sz the number of bytes to read to the buffer
       *
       * @returns the number of bytes read or in the case of an error, this will
       * be less
       */
      int getFullData(void *_buffer,unsigned long _sz);

      /**
       * check whether there is data available on the read socket
       *
       * @return true if there is data waiting
       */
      bool hasData();

      /**
       * wait for data on the socket - will not return until there is data or an
       * error occurs
       *
       * @return true is there is data, false on an error
       */
      bool waitData();

      /**
       * wait up to x micoseconds for data to be come availble
       * @param _usec max microseconds to wait.
       * @return true if data bcomes available
       */
      bool waitTimeData(long _usec);

      /**
       * returns the current address of the server comunications.
       * For a client, this will be the address it is writing to,
       * for a server, this will be the last client that was read from, or
       * INADDR_ANY if none has been read.
       */
      unsigned long getDstIPAddress();

      /**
       * return the port that we are sending data to
       *
       * @returns the port we are connected to
       */
      int getDstPort();

      /**
       * returns the current address of the server comunications.
       * For a server, this will be the last client that was read from, or
       * INADDR_ANY if none has been read.
       */
      unsigned long getSrcIPAddress();

      /**
       * return the port that we recieved data from
       *
       * @returns the port number that we recieved data from
       */
      int getSrcPort();

      /**
       * clear the socket of pending data to be read
       */
      void clear();

      /**
       * wait and connect to an incoming connection
       * on this socket
       * if it is not a server socket the will return 0
       */
      EZSocket *waitConnection();

   private:
      /**
       * private function used by waitConnection to create a socket
       * @param _sock the raw socket descriptor
       @ @param _srcsockin the ip that the socket is from
       */
      EZSocket(int _sock,struct sockaddr_in _srcsockin);
      
      /**
       * lookup an ip number or host name and return the long encoded value of it
       *
       * private function called by constructors only
       *
       * @param _ip the string containing the ip number or host name to connect
       * to
       *
       * @return INADDR_ANY if invalid address, otherwise the ip as a long.
       */
      unsigned long lookupAddress(const char *_ip);

      /**
       * open a socket on a specified port
       *
       * private function called only by constructors
       *
       * @param _port the port to connect to
       * @param _addr the encoded address to connect - if this is INADDR_ANY then
       * this will be a server connection
       *
       * @exception EZNoConnectionException
       */
      void openSocket(int _port,unsigned long _addr=INADDR_ANY);

      /**
       * close opened socket
       *
       * private function called only by deconstructor
       *
       */
      void closeSocket();

      /**
       * private function that will open winsock if required
       */
      bool openWinSock();

      /* dont allow people to copy us */
      EZSocket(const EZSocket &) {}

      /* dont allow people to assign references to us */
      EZSocket& operator=(const EZSocket &) { return *this; }
};

#endif // ezsocket_h

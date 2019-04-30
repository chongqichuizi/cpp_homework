

#include "ezsocket.h"

#ifndef USING_WINDOWS
 #include <sys/time.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/socket.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <netinet/in.h>
 #include <cstring>
 #include <iostream>

 #define closesocket(x) close(x)

 typedef void BUFFTYPE;
#else
 // windows doesnt have this function
 #define NEED_INET_ATON
 typedef char BUFFTYPE;
 typedef int socklen_t;

// #include <iostream>
#endif

#include <errno.h>

#ifdef NEED_INET_ATON
/* convert a XXX.XXX.XXX.XXX string to a network long
   - needed by some sun machines and ppc's
 */
  static int inet_aton(const char *str,struct in_addr *to);
#endif // NEED_INET_ATON

//#include <exception.h>

/**
 * create the socket locally and listen on it at the
 * port
 *
 * @exception EZNoConnectionException
 */
EZSocket::EZSocket(int _port)
{

  sock = -1;
  isserver =  true;

  load_winsock = false;

  openWinSock();

  openSocket(_port);
}

/**
 * deconstructor - removes the socket
 */
EZSocket::~EZSocket()
{
  closeSocket();
#ifdef __WIN32__
  if(load_winsock) { WSACleanup(); }
#endif // __win32__

  load_winsock = false;
}

/**
 * create the socket for the specified port and address
 *
 * @exception EZNoConnectionException
 */

EZSocket::EZSocket(const char *_ip,int _port)
{
   sock = -1;
   unsigned long addr;

   load_winsock = false;

   openWinSock();

   if(_ip!=NULL)
   {
      addr = lookupAddress(_ip);
      isserver = false;
   }
   else
   {
      addr = INADDR_ANY;
      isserver = true;
   }

   openSocket(_port,addr);
}

/**
 * private constructor for makeing a bbsocket from preexisting 
 * data
 */
EZSocket::EZSocket(int _sock,struct sockaddr_in _srcsockin)
{
  isserver = false;
  sock = _sock;
  
  memset(&srcsockin,0,sizeof(srcsockin));
  memcpy(&sockin,&_srcsockin,sizeof(struct sockaddr_in));
}

bool EZSocket::openWinSock()
{
#ifdef USING_WINDOWS
  WSADATA WSAData;
  if(WSAStartup(0x101,&WSAData)) return false;

  load_winsock = true;

  return true;
#else
  return false;
#endif
}


/**
 * create the server listener
 *
 * @param _port the port to listen on
 * param _addr the encoded address to connect - if this is INADDR_ANY then
 * this will be a server connection
 *
 * @exception EZNoConnectionException
 */
void EZSocket::openSocket(int _port,unsigned long _addr) // INADDR_ANY
{

   // tcp socket
   sock=socket(PF_INET,SOCK_STREAM,0);
   if(sock<0)
   {
      throw "NO connection"; 
   }

   memset(&srcsockin,0,sizeof(srcsockin));

   memset(&sockin,0,sizeof(sockin));
   sockin.sin_family=AF_INET;
   sockin.sin_port=htons(_port);
   sockin.sin_addr.s_addr = _addr;

   if(_addr ==  INADDR_ANY) // this is a server
   {
      if(bind(sock, (const struct sockaddr *)&sockin, sizeof(sockin))) 
      {
	 closeSocket();
	 throw "No bind"; 
      }
   }
   else // client -  connect
   {
     int i = connect(sock,(sockaddr *)&sockin,sizeof(sockin));
     if(i<0) throw "No connection";
   }
   return;
}

/**
 * wait and connect to an incomin connection
 * on this socket
 * if it is not a server socket the will return 0
 */
EZSocket *EZSocket::waitConnection()
{
  EZSocket *conn=0;
  
  if(!isserver) return 0;

  if(listen(sock,0)==0)
  {
    //struct sockaddr_in connaddr;
    socklen_t addrlen = sizeof(srcsockin);  
    
    int connsock = accept(sock,(sockaddr *)&srcsockin,&addrlen); 
    conn = new EZSocket(connsock,srcsockin);
  }
  return conn;
}


/////////////////
/**
 * close the listener 
 */ 
void EZSocket::closeSocket()
{
   if(sock != -1) closesocket(sock);
   sock = -1;
}

unsigned long EZSocket::getDstIPAddress()
{
   return sockin.sin_addr.s_addr;
}
unsigned long EZSocket::getSrcIPAddress()
{
   return srcsockin.sin_addr.s_addr;
}

unsigned long EZSocket::lookupAddress(const char *_ip)
{
   struct sockaddr_in in;
   struct hostent *host=NULL;

   memset(&in,0,sizeof(in));

   if((inet_aton(_ip,(struct in_addr *)&in.sin_addr.s_addr))!=0) 
   {
      /* host is a ip number*/
   }                                                                                                    
   /* else must be a name*/
   else if(!(host=gethostbyname(_ip))) 
   {
#ifndef USING_WINDOWS
      cerr<<"couldn't find ipaddress\n";
#endif
      return(INADDR_ANY);
   }
   else 
   {
      memcpy(&in.sin_addr,host->h_addr,host->h_length);
   } 

   return in.sin_addr.s_addr;
}

int EZSocket::writeText(const char *text)
{
  if(text==0) return 0; 
  int len = strlen(text);
  return writeData(text,len);
}
   
bool EZSocket::waitData()
{
   fd_set rfds;
   int retval;

   if(sock == -1) return false;

   /* see if there is pending data aroud */
   FD_ZERO(&rfds);
   FD_SET(sock, &rfds);

   retval = select(sock+1, &rfds, NULL, NULL, NULL);

   return retval>0; 
}

bool EZSocket::hasData()
{
   fd_set rfds;
   struct timeval tv;
   int retval;

   if(sock == -1) return false;

   /* see if there is pending data aroud */
   FD_ZERO(&rfds);
   FD_SET(sock, &rfds);
   tv.tv_sec = 0; /* TODO - check that 0 wait doesn't wait */
   tv.tv_usec = 0; /* dont wait */

   retval = select(sock+1, &rfds, NULL, NULL, &tv);

   return retval>0;
}

int EZSocket::writeData(const void *_buffer,unsigned long _sz)
{
   int result;

   if(sock == -1 || _buffer == NULL) return 0;

   result = send(sock,(const BUFFTYPE *)_buffer,_sz, 0);

   // TODO check this is working .....
   //if((result < 0) && (errno == EINTR)) {
   //   //cerr<<"ERROR: send error\n"<<flush;
   //   //     goto retry;
   //}

   return result;
}

int EZSocket::readData(void *_buffer,unsigned long _sz)
{
   if(sock == -1) return -1;

   // TODO this is probally over written - need to know where it game from
   return recv(sock,(BUFFTYPE *)_buffer,_sz,0);
}

int EZSocket::peekData(void *_buffer,unsigned long _sz)
{
   if(sock == -1) return -1;

   if(hasData()==false) return 0;

   return recv(sock,(BUFFTYPE *)_buffer,_sz,MSG_PEEK);
}

int EZSocket::getFullData(void *_buffer,unsigned long _sz)
{
   fd_set rfds;
   struct timeval tv;
   int retval;

   if(sock == -1) return 0;

   /* see if there is pending data aroud */
   FD_ZERO(&rfds);
   FD_SET(sock, &rfds);
   tv.tv_sec = 0;  /* TODO - check that 0 wait doesn't wait */
   tv.tv_usec = 0; /* dont wait */

   retval = select(sock+1, &rfds, NULL, NULL, &tv);

   if(retval > 0)
   {
      retval = recv(sock,(BUFFTYPE *)_buffer,_sz,MSG_PEEK);

      if(retval <= 0) {
	 return -1; // may be bad error or lost connection -- CHECK it
      }
      else if(retval < _sz) {
	 // not the whole data yet
	 return 0;
      }

      retval = recv(sock,(BUFFTYPE *)_buffer,_sz,0);
   }

   return retval;
}

int EZSocket::getDstPort()
{
   return ntohs(sockin.sin_port);
}

int EZSocket::getSrcPort()
{
   return ntohs(srcsockin.sin_port);
}

void EZSocket::clear()
{
   char temp[1024];
   int i;

   while((i=peekData(temp,1024))>0)
   {
	  readData(temp,i);
   }
   return;
}
/**
 * wait up to x micoseconds for data to be come availble
 * @param _usec max microseconds to wait.
 * @return true if data bcomes available
 */
bool EZSocket::waitTimeData(long _usec)
{
   fd_set rfds;
   struct timeval tv;
   int retval;

   if(sock == -1) return false;

   /* see if there is pending data aroud */
   FD_ZERO(&rfds);
   FD_SET(sock, &rfds);
   tv.tv_sec = 0;
   tv.tv_usec = _usec; /* time to wait */

   retval = select(sock+1, &rfds, NULL, NULL, &tv);

   return retval>0; 
}

#ifdef NEED_INET_ATON
 #include <stdio.h>


/* convert a XXX.XXX.XXX.XXX string to a network long
   - needed by some sun machines and ppc's amongst others
 */
static int inet_aton(const char *str,struct in_addr *to)
{
  int n[4];
  int ok;

  if(!str) return 0;

  ok=sscanf(str,"%d.%d.%d.%d",&n[0],&n[1],&n[2],&n[3]);
  to->s_addr=(n[0] << 24) + (n[1]<<16)+(n[2]<<8)+n[3];

  if(ok<4) ok=0;

  to->S_un.S_addr = htonl(to->S_un.S_addr);

  return(ok);
}
#endif


/*
 * Copyright (c) 2016 Jackie Dinh <jackiedinh8@gmail.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  1 Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  2 Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 *  3 Neither the name of the <organization> nor the 
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @(#)socket.h
 */

#ifndef _CICE_SOCKET_H_
#define _CICE_SOCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cice/address.h"
#include "cice/types.h"

typedef enum {
  ICE_SOCKET_TYPE_UDP_BSD,
  ICE_SOCKET_TYPE_TCP_BSD,
  ICE_SOCKET_TYPE_PSEUDOSSL,
  ICE_SOCKET_TYPE_HTTP,
  ICE_SOCKET_TYPE_SOCKS5,
  ICE_SOCKET_TYPE_UDP_TURN,
  ICE_SOCKET_TYPE_UDP_TURN_OVER_TCP,
  ICE_SOCKET_TYPE_TCP_ACTIVE,
  ICE_SOCKET_TYPE_TCP_PASSIVE,
  ICE_SOCKET_TYPE_TCP_SO
} IceSocketType;

typedef int (*recvfrom_func)(int sockfd, void *buf, size_t len, int flags, 
                struct sockaddr *src_addr, socklen_t *addrlen);
typedef int (*sendto_func)( int sockfd, const void *buf, size_t len, int flags,
                      const struct sockaddr *dest_addr, socklen_t addrlen);   
typedef int (*read_func)(int fd, void *buf, size_t count);   
typedef int (*write_func)(int fd, const void *buf, size_t count);   

struct _socket {
   int   fd;
   IceSocketType type;
   address_t addr;
   void     *agent;
   void     *stream;
   void     *component;

   //define abstract methods
   recvfrom_func _recvfrom;
   sendto_func   _sendto;
   read_func     _read;
   write_func    _write;

#ifdef USE_LIBEVENT2
   /* TODO: abstract network layer 
    * to support epoll, select, kqueue etc */
   struct event *ev;
   struct bufferevent *bev;
#endif

#ifdef USE_ESP32
#endif

};

socket_t*
socket_new(IceSocketType type);

void
socket_free(socket_t *sock);

int
socket_is_reliable(socket_t *sock);
 
#ifdef __cplusplus
}
#endif

#endif //_CICE_EVENT_H_



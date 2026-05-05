#ifndef WRAPPERS_H
#define WRAPPERS_H

/**
 * Wrapper header that includes various system commands that are used in GenShell
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>

// There will be comments indicating which header file each wrapper requires

// uses unistd.h
pid_t Fork(void);

// uses unistd.h
int Pipe(int pipefd[2]);

// uses sys/wait.h
pid_t Wait(int *wstatus);

// uses sys/wait.h
pid_t Waitpid(pid_t pid, int *wstatus, int options);

// uses fcntl.h
int Open(const char *pathname, int flags, mode_t mode);

// uses unistd.h
int Close(int fd);

// uses unistd.h
int Write(int fd, const void *buf, size_t count);

// uses unistd.h
int Read(int fd, void *buf, size_t count);

// uses sys/socket.h
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// uses sys/socket.h
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// uses sys/socket.h
int Listen(int sockfd, int backlog);

// uses sys/socket.h
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// uses sys/socket.h
ssize_t Send(int sockfd, const void *buf, size_t len, int flags);

// uses sys/socket.h
ssize_t Recv(int sockfd, void *buf, size_t len, int flags);

// uses unistd.h
int Execvp(const char *file, char *const argv[]);

#endif // WRAPPERS_H
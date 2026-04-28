#include "wrappers.h"



/* PROCESSES AND IPC */


/**
 * Wrapper that handles forking errors
 * 
 * @return      the pid_t of the process
 */
pid_t Fork(void) {
   pid_t pid = fork();
   if (pid == -1) {
      perror("Forking error");
      exit(-1);
   }
   return pid;
}

/**
 * Wrapper that handles piping errors
 * 
 * @param pipefd        the file descriptors for the named pipe
 * @return              0 on success, exits otherwise
 */
int Pipe(int pipefd[2]) {
   int p = pipe(pipefd);
   if (p == -1) {
      perror("Pipe error");
      exit(1);
   }
   return 0;
}

/**
 * Wrapper that handles wait errors
 * 
 * @param wstatus       pointer to an int that stores the exit status of the child
 * @return              the pid_t of the terminated child, exits on failure
 */ 
pid_t Wait(int *wstatus) {
   pid_t pid = wait(wstatus);
   if (pid == -1) {
	  perror("Wait error");
	  exit(-1);
   }
   return pid;
}

/**
 * Wrapper that handles Waitpid errors
 * 
 * @param pid           the pid of the child process to wait for
 * @param wstatus       pointer to an int that stores the exit status of the child
 * @param options       bitwise OR of options that modify behavior (e.g. WNOHANG, WUNTRACED)
 * @return              the pid_t of the terminated child, exits on failure
 */
pid_t Waitpid(pid_t pid, int *wstatus, int options) {
   pid_t p = waitpid(pid, wstatus, options);
   if (p == -1) {
	  perror("Waitpid error");
	  exit(-1);
   }
   return p;
}

/**
 * Wrapper that handles execvp errors
 * 
 * @param file      the file containing the bash function
 * @param argv      argument vector for the specified bash function
 * @return          0 on success, exits on failure
 */
int Execvp(const char *file, char *const argv[]) {
   int e = execvp(file, argv);
   if (e == -1) {
      perror("Execvp error");
      exit(-1);
   }
   return e;
}


/* FILE I/O */


/**
 * Wrapper that handles open errors
 * 
 * @param pathname      the pathname of the file
 * @param flags         bitwise OR of access mode and file status flags (e.g. O_RDONLY, O_CREAT)
 * @param mode          permission bits to use if the file is created
 * @return              the file descriptor of the file, exits on failure
 */
int Open(const char *pathname, int flags, mode_t mode) {
   int o = open(pathname, flags, mode);
   if (o == -1) {
	  perror("Open error");
	  exit(-1);
   }
   return o;
}

/**
 * Wrapper that handles close errors
 * 
 * @param fd        the file desciptor of the file to be closed
 * @return          0 on success, exits otherwise
 */
int Close(int fd) {
   int c = close(fd);
   if (c == -1) {
	  perror("Close error");
	  exit(-1);
   }
   return c;
}

/**
 * Wrapper that handles write errors
 * 
 * @param fd            the file descriptor to write to
 * @param buf           pointer to the buffer containing the data to write
 * @param count         the number of bytes to write
 * @return              the number of bytes written, exits on failure
 */
int Write(int fd, const void *buf, size_t count) {
   int w = write(fd, buf, count);
   if (w == -1) {
      perror("Write error");
      exit(1);
   }
   return w;
}

/**
 * Wrapper that handles read errors
 * 
 * @param fd            the file descriptor to read from
 * @param buf           pointer to the buffer to store the read data
 * @param count         the maximum number of bytes to read
 * @return              the number of bytes read, exits on failure
 */
int Read(int fd, void *buf, size_t count) {
   int r = read(fd, buf, count);
   if (r == -1) {
      perror("Read error");
      exit(1);
   }
   return r;
}


/* SOCKETS AND NETWORKS */


/**
 * Wrapper that handles connect errors
 * 
 * @param sockfd        the file descriptor of the socket
 * @param addr          the socket address
 * @param addrlen       the length of the socket address
 * @return              0 on success, exits on failure
 */
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
   int c = connect(sockfd, addr, addrlen);
   if (c == -1) {
	  perror("Connect error");
	  exit(-1);
   }
   return c;
}

/**
 * Wrapper that handles bind errors
 * 
 * @param sockfd        the file descriptor of the socket
 * @param addr          the socket address
 * @param addrlen       the length of the socket address
 * @return              0 on success, exits on failure
 */
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
   int b = bind(sockfd, addr, addrlen);
   if (b == -1) {
	  perror("Bind error");
	  exit(-1);
   }
   return b;
}

/**
 * Wrapper that handles listen errors
 * 
 * @param sockfd        the file descriptor of the socket
 * @param backlog       the maximum length of the queue of pending connections
 * @return              0 on success, exits on failure
 */
int Listen(int sockfd, int backlog) {
   int l = listen(sockfd, backlog);
   if (l == -1) {
	  perror("Listen error");
	  exit(-1);
   }
   return l;
}

/**
 * Wrapper that handles accept errors
 * 
 * @param sockfd        the file descriptor of the socket
 * @param addr          the socket address
 * @param addrlen       the length of the socket address
 * @return              the file descriptor of the accepted socket, exits on failure
 */
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
   int a = accept(sockfd, addr, addrlen);
   if (a == -1) {
	  perror("Accept error");
	  exit(-1);
   }
   return a;
}

/**
 * Wrapper that handles send errors
 * 
 * @param sockfd        the file descriptor of the socket
 * @param buf           pointer to the buffer containing the data to send
 * @param len           the length of the data to send in bytes
 * @param flags         bitwise OR of flags that modify send behavior
 * @return              the number of bytes sent, exits on failure
 */
ssize_t Send(int sockfd, const void *buf, size_t len, int flags) {
   ssize_t s = send(sockfd, buf, len, flags);
   if (s == -1) {
     perror("Send error");
     exit(-1);
   }
   return s;
}

/**
 * Wrapper that handles recv errors
 * 
 * @param sockfd        the file descriptor of the socket
 * @param buf           pointer to the buffer to store the received data
 * @param len           the maximum number of bytes to receive
 * @param flags         bitwise OR of flags that modify recv behavior
 * @return              the number of bytes received, exits on failure
 */
ssize_t Recv(int sockfd, void *buf, size_t len, int flags) {
   ssize_t r = recv(sockfd, buf, len, flags);
   if (r == -1) {
     perror("Recv error");
     exit(-1);
   }
   return r;
}
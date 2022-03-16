# Minitalk

```
FINAL GRADE: 125/100
```

Pass a string of characters from one program to another, using only `kill()` with `SIGUSR1` and `SIGUSR2` (thus passing the data in binary form).

My first work was using usleep, to wait to receive the control bit. It was not working on MacOS (but perfectly on Linux). So I work again to implement the Minitalk whithout using usleep (whithout global variable too). It wasn't working on MacOS...
But after a long research time I was able to make my Minitalk work on MacOS by using the **sa_flags** `SA_SIGINFO | SA_RESTART | SA_NODEFER` instead of `SA_SIGINFO`. So my two implementation are perfectly working, and I kept the one with sleep. My work whithout sleep still exist on the `nosleep` branch.

The subject asked to pass a string of 100 characters in less than 1 second, my program does it in 0.015 seconds (I flex a little).

## Usage
Running `make` will create two binary, `server` and `client`.
### Running server
```
./server
```
*The server will continue to listen indefinitely.*
### Running client
```
./client <server pid> <string to send>
```

## Tests
- First test (tests the execution time)
	```
	sh tests.sh <server pid>
	```
- Second test (tests the behavior in time with an infinite loop)
	```
	sh test_loop.sh <server_pid>
	```

Subject dated January 2022.

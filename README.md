# Minitalk

Pass a string of characters from one program to another, using only `kill()` with `SIGUSR1` and `SIGUSR2` (thus passing the data in binary form).

The subject asked to pass a string of 100 characters in less than 1 second, my program does it in 0.12 seconds (I flex a little).

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

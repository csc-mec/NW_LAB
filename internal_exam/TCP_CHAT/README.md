# TCP CHAT program

- uses same algorithm as TCP socket program
- instead of sending one message send messages in loop 

### Issues

- can only send in order one message each for client and server 
- ~cannot handle blankspace might be solved by using `fgets()` instead of `scanf()`~ fixed
either use
```c
      fgets(buffer, BUFFER_SIZE, stdin);
      buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
```
or 
```c
      scanf("%s",buffer);
```
The second one fails on whitespaces for example if you use `Hello World` only  `Hello` gets into input

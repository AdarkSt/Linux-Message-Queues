# Message Queues in C

Message queues enable processes to exchange messages.

## `msgget()` System Call

The `msgget()` system call creates a new message queue or gets the ID of an already created queue. The function prototype is:

```c
#include <sys/msg.h>
int msgget(key_t key, int msgflag);
```

`key`: A key that can be generated using the IPC_PRIVATE constant or ftok() with the help of the function.

`msgflag` : Permission bits.

## Flags for msgflag:

`IPC_CREAT`: If there is no existing queue with the given key, then create a new one.

`IPC_EXCL`: If the `IPC_CREAT` flag is set and a queue with the given key already exists, then the call ends with an `EEXIST` error.

## message_create.c Program

The `message_create.c` program creates a new message queue using the `msgget()` call.

To complete the program, it is necessary:

```shell
gcc message_create.c init_queue.c -o message_create
./message_create
```

## Checking Generated Queues
```shell
The generated queues can be checked using the ipcs --q command.
```

## Write and read operations

The `msgsnd()` system call is used to write to the queue. Function prototype is as follows:

```c
#include <sys/msg.h>
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
```

`msqid` – queue id,

`msgp` – A structure object declared by the programmer (example:
presented in the `message_queue.h` file),

`msgsz` – The size of the message to be written, in bytes;

`msgflag` – Control bitmask. Can be 0, or accept the `IPC_NOWAIT` value,
which performs a non-blocking call.

An example of the `msgsnd()` call is shown in message_send.c. 
To execute the program

```shell
gcc message_send.c init_queue.c -o message_send
./message_send
```

To read from the queue, the `msgrcv()` system call is used.
The function prototype is:

```c
#include <sys/msg.h>
ssize_t msgrcv(int msqid, void *msgp, size_t maxmsgsz, long msgtyp, int msgflg);
```

`msqid` – queue id,

`msgp` – structure object declared by the programmer,

`maxmsgsz` – Maximum read message size in bytes;

`msgtyp` – message type defined in the structure,

`msgflag` – Control bitmask. Can be 0, or accept the following 3
one of the values.

`IPC_NOWAIT` - Perform a non-blocking call.

`MSG_EXCEPT` – Read the first message whose type is equal
not to msgtyp.

`MSG_NOERROR` – If message size is greater than maxmsgsz then
instead of returning an error, the msgrcv function returns
the first maxmsgsz bytes of the message.

An example of the `msgrcv()` call is shown in `message_receive.c.` 

To complete the program, it is necessary:
```shell
gcc message_receive.c init_queue.c -o message_receive
./message_receive
```

## Message queue management

The `msgctl()` function is used for queue management. The function prototype
is as follows:

```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

The `cmd` argument specifies the action to be performed. It is possible
the following 3 values:

`IPC_RMID` – immediately delete the message queue and with it
associated `msqid_ds` data structure. All available in the queue
messages are deleted, all writing (reading) processes
return `EIDRM` error. The 3rd argument is ignored (Example:
presented in `message_rm.c` program).

`IPC_STAT` – copy the `msqid_ds` associated with the message queue
data structure in the buf buffer (Example shown
in the program `message_chqbyes.c`)

`IPC_SET` – Modify queue-related data in the `msqid_ds` structure

## Data structure

Each message queue has data associated with it

```c
struct msqid_ds {
 struct ipc_perm msg_perm; /* Ownership and permissions */
 time_t msg_stime; /* Time of last msgsnd() */
 time_t msg_rtime; /* Time of last msgrcv() */
 time_t msg_ctime; /* Time of last change */
 unsigned long __msg_cbytes; /* Number of bytes in queue */
 msgqnum_t msg_qnum; /* Number of messages in queue */
 msglen_t msg_qbytes; /* Maximum bytes in queue */
 pid_t msg_lspid; /* PID of last msgsnd() */
 pid_t msg_lrpid; /* PID of last msgrcv() */
};
```


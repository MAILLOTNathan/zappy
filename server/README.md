## COMMAND IA

### Queues of commands

```c
typedef struct queue_command_s
{
    enum command_t command;
    char *arg;
    struct queue_command_s *next;
} queue_command_t;
```

| make | Command  | time | return | Description |
| ---- |:--------:|:----:|:------:|:-----------:|
| NO   | Forwards | 7/f  | ok     | move player one case forward |
| NO   | Right    | 7/f  | ok     | turn player right |
| NO   | Left     | 7/f  | ok     | turn player left |
| NO   | Look     | 7/f  | list of tile     | look around |
| NO   | Inventory| 1/f  | list the inventory of the ai     | look inventory |
| NO   | Broadcast *text* | 7/f  | ok     | send a message to all players |
| NO   | Connect_nbr | 0/f  | value | send the number of slots valid for the team |
| NO  | Fork     | 42/f | ok     | create a new player |
| NO  | Eject    | 7/f  | ok     | eject player from the tile |
| NO  | Take *object*   | 7/f  | ok/ko     | take an object on the tile |
| NO  | Set *object*    | 7/f  | ok/ko     | set an object on the tile |
| NO  | Incantation    | 300/f | ok/ko     | start the incantation |

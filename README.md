# Nick's Brainfuck Interpreter (NBI)

An interpreter for [brainfuck](https://en.wikipedia.org/wiki/Brainfuck), the
(in)famous [esolang](https://en.wikipedia.org/wiki/Esoteric_programming_language)
created by Urban Müller in 1993. This is meant to be a personal learning
exercise so I can develop my understanding of how interpreters work.

## Language Design

brainfuck programs consist of eight instructions, which manipulate a sequential
number of cells using a pointer. From
[Wikipedia](https://en.wikipedia.org/wiki/Brainfuck#Language_design):

Character | Description |
|---------|-------------|
| `>`     | Increment the data pointer by one (to point to the next cell to the right). |
| `<`     | Decrement the data pointer by one (to point to the next cell to the left). |
| `+`     | Increment the byte at the data pointer by one. |
| `-`     | Decrement the byte at the data pointer by one. |
| `.`     | Output the byte at the data pointer. |
| `,`     | Accept one byte of input, storing its value in the byte at the data pointer. |
| `[`     | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching `]` command. |
| `]`     | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching `[` command. |

## Using the Interpreter

### Prerequisites

First, ensure the following tools are installing on your machine:
1. [The GNU Compiler Collection](https://gcc.gnu.org/)
2. [GNU Make](https://www.gnu.org/software/make/)
3. [Git](https://git-scm.com/downloads)

Run the following in your terminal to clone this repository, navigate to its
root directory, and compile `nbi`:

```
git clone https://github.com/nsdigirolamo/nbi.git && cd nbi && make
```

### Running

After compiling `nbi`, you can run it on any file that contains brainfuck source
code. Brainfuck source code typically uses the `.b` file extension:

```sh
./nbi samples/hello_world.b
```

## References:

- [Yet another brainfuck reference.](https://brainfuck.org/brainfuck.html)

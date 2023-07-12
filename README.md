Inter-Process Communication

This repository contains three programs that demonstrate inter-process communication using different mechanisms: FIFOs, Unix Sockets, and Shared Memory. Each mechanism involves sending and receiving strings between two programs.

Program Descriptions

FIFO: This program implements inter-process communication using FIFOs (named pipes). It consists of two programs, FIFO1 and FIFO2, which communicate with each other by sending and receiving strings.

Socket: This program demonstrates inter-process communication using Unix Sockets. Similar to FIFO IPC, it also consists of two programs, socket1 and socket2, that exchange strings between each other.

SharedMem: This program showcases inter-process communication using Shared Memory. It includes two programs, memory1 and memory2, that share strings by utilizing shared memory segments.

How to Run the Programs

To run the programs, follow these steps:

Clone the entire repository and navigate to the respective folders.

Compile the programs by running make in the corresponding directories:

For FIFO IPC:
cd FIFO
make

For Socket IPC:
cd Socket
make

For Shared Memory IPC:
cd SharedMem
make


Open two separate terminals for each mechanism and navigate to the respective directories.

In one terminal, run the receiving program (P2). In the other terminal, run the sending program (P1). Execute the following commands in the respective terminals:

For FIFO IPC:

Terminal 1:
./FIFO1

Terminal 2:
./FIFO2

For Socket IPC:

Terminal 1:
./socket2

Terminal 2:
./socket1

For Shared Memory IPC:

Terminal 1:
./memory2

Terminal 2:
./memory1


Make sure to start the receiving program (P2) before the sending program (P1) to establish proper communication.

Observe the inter-process communication results in the terminals.

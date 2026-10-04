# Replicator a proof of concept project

## What do you mean by "replicator"?

So I was watching about signals in Unix/Linux systems and also was learning a bit of fork() too, then suddenly it clicked me.
Why not combine both and make something that replicates itself?

So I learnt more, handling signals, different types of signals. How to safely exit on a specific signal as well and etc.
So this is a proof of concept project I made currently purely in C with the Unix API.

## How does it work?

Compile both files separately and you get something called the "supervisor" and the "worker". Now the supervisor looks over the worker.
If the worker terminates first then the supervisor intercepts its exit or termination and simultaneously creates a new process of it,
until supervisor itself is terminated as well.

This is pretty much enough but this taught me a lot about the Unix API and also OS internals/concepts in general and I am happy for that.
Probably the reason why I am uploading it here altogether too.

## Get started with this

Make sure you have the clang/g++/gcc compiler above I would say C17. And also a Unix/Unix-like system which can be your Linux system,
Mac system or for cracked fellas BSD systems. Sorry Windows people but you have to wait on that.

Now separately compile each file into its own executable, do not feel free to name them whatever except the files themselves.

```bash
clang supervisor.c -o supervisor
clang worker.c -o worker
```
Now that being done, go ahead and run the supervisor. For now worker does not do anything but wait for a signal, try Ctrl+C on it, that
you usually would be doing.

```bash
./supervisor
```
And you would be greeted with the said output:
```bash
supervisor: Supervisor running with PID:<supervisor_pid>

worker: Worker running with PID:<worker_pid>
```
```
```
```
```
```
```
```
```
```
```
And I believe that is enough, feel free to go nuts and experiment(P.S. I hear this can be used for anti-viruses or for something else)

## Anything in the near future for this?

Absolutely, I am planning to make this compatible with Windows firstly then secondly, build an anti-virus on top of it too. A very ambitious project indeed. So stay tuned!

## What about contributing

I almost forgot, well I am not sure I feel I should build this on my own, I rather would like you to have the liberty to use it on your own codebase or project and in your own repository. So no contribution as such I am accepting :(

# PratBal4

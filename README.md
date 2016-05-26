# System V init system based daemon with several child processes

## The main goal

This sample is designed to show how to create Linux System V init based daemon, which is able to control several child processes.

We have three interpreted (Python) scripts (servers). These servers depend on each other and must be started and stopped simultaneously. If one of them crushes, all others must be terminated.

Servers must start on system startup as a single system service (daemon). Service must support Debian and Ubuntu platforms (this is the reason of traditional System V init system choice).

## Used tools

To start and control several interpreted processes we need use Linux system calls such as fork() or waitpid(). So, the service itself is an executable binary (C++ based). This executable binary will be compiled and installed as a system service during the project installation.

## Installation

Enter the project directory and run:

`sudo ./install.sh`

**daemon-p3** system service will be installed and started.

## Management

To discover **daemon-p3** service status:

`sudo service daemon-p3 status`

To start **daemon-p3** service:

`sudo service daemon-p3 start`

To stop **daemon-p3** service:

`sudo service daemon-p3 stop`

## Testing

When **daemon-p3** service is running, enter the project directory and run:

`./client.py "Some test message"`

Message string argument is optional.

The client calls all of the servers and prints messages from them with your request echo.

## Deinstallation

Enter the project directory and run:

`sudo ./uninstall.sh`

**daemon-p3** service will be stopped and removed.
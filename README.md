# Robot-Racing-2020
Codebase for the UWRT robot racing team 2020

# Basic Overview

For more in depth information and reading, take a look at the individual README files in the appropriate folder.

## Machine Vision

We are using something... with a fancy camera that I dont know the name of at the time of writing.



## Jetson

I'm putting the stuff I learned about the jetson here because im not sure where else it should go.

### About

I beleive that we have the [Jetson TX2 Developer Kit](https://developer.nvidia.com/embedded/jetson-tx2-developer-kit)

The Jetson is the brain of the robot. It will handle all of the machine vision stuff.

The Jetson is running ubuntu... Not sure what version. We might look into using a different distro in the future for better performance (somthing lighter). For now what we have works, but we should definately make sure to disable X (the desktop server) on startup because that is a significant amount of overhead that we have no need for (We should only need the command line to make everything work.)

### SSH

Whoever was using the jetson last year set up SSH (so Im not sure how to set it up.)

SSH is used to remotely control the jetson (ie from a seperate computer) over a network.

### Network

I am pretty sure that the jetson is using DHCP. We probably want to set it up to have a static ip.

Also not sure why we are using the goodlife router for wifi instead of the wireless adaptor that is onboard the jetson... (im pretty sure there is one onboard?).

### Serial (Arduino)

The jetson is able to control the robot through the arduino. The Jetson simply sends/reads data through serial (via USB) to the arduino. This is acheived through the stty command (try `stty -F /dev/DEVICENAME`)

If that doesn't work `cat -F /dev/DEVICENAME` or `tail -f /dev/DEVICENAME` may be needed to read the arduino output and `echo "your text here" > /dev/DEVICENAME` to send data to the arduino.

## Drive Control

We are using an arduino to control the steering & drive capabilities of the robot. The remote transmitter we have must be connected for the robot to function. Setting the transmitter to auto mode will relinquish control to the jetson, otherwise the transmitter has full control of the car. If ESTOP is on, the bot will not move at all.

We also plan to connect an IMU (Intertial measurement unit) to the arduino to give the jetson more telemetry data.

# Credentials

## Jetson

uname: `nvidia`

password: `nvidia`

## The SSH network

SSID: `Hummingbot`

password: `hummingbot`

router ip: `192.168.8.1`
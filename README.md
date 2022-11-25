Blinky_Nucleo_H7A3
==================

[![Build Status](https://github.com/chalandi/Blinky_Nucleo_H7A3/actions/workflows/Blinky_Nucleo_H7A3.yml/badge.svg)](https://github.com/chalandi/Blinky_Nucleo_H7A3/actions)

This repository implements an entirely manually-written, pure
_bare_ _metal_ Blinky Project for the STM32H7A3ZIT6Q (NUCLEO-144-H7A3).

Features include:
  - CPU, power, chip, clock and PLL initialization,
  - D/I cache and FPU initialization,
  - timebase derived from SysTick,
  - blinky LED show on three bits,
  - implementation in C99 with absolute minimal use of assembly.

A clear and easy-to-understand build system based on GNUmake
completes this fun and educational project.

This repository provides keen insight on starting up
a _bare_ _metal_ ARM(R) Cortex(R)-M7 controller.

## Details on the Application

The application boots from memory address and stack location
in the first two entries of the interrupt vector table.
Subsequent initialization brings the CPU up to full speed
at 280 MHz with the appropriate number of flash-access wait states.

Following low-level chip initialization, the program jumps to
the `main()` subroutine. Here the data and instruction caches
are initialized to produce full CPU performance capabilities
of the microcontroller.

The blinky LED show utilizes three LED ports to _count_
in binary in a visual fashion. The SysTick interrupt
is enabled to provide the timebase for the blinky LED show,
with the LED toggling action in the interrupt handler.

## Building the Application

Build on `*nix*` is easy using an installed `gcc-arm-none-eabi`

```sh
cd Blinky_Nucleo_H7A3
bash Rebuild.sh
```

The build results including ELF-file, HEX-mask, MAP-file
and assembly list file are created in the `Output`directory.

If `gcc-arm-none-eabi` is not installed, it can easily
be installed with

```sh
sudo apt install gcc-arm-none-eabi
```

## Continuous Integration

CI runs on pushes and pull-requests with a simple
build and result verification on `ubuntu-latest`
using GutHub Actions.

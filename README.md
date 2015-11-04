
about
-----

ticketsolver is a program that finds combination of arithmetical operation signs
and brackets between given digits to obtain the required expression result.
Operations can be "+", "-" , "/", "*", "^" (power) and concatenation (combining
digits into multi-digit number).

This program can be useful to verify one's own calculations when finding a
combination of operations and brackets between digits of public transport ticket
number which gives an expression with a result of 100, that is an amazing
mathematical game during a commute.

Any number of digits is supported but only calculations for up to 7 can be done
on modern processor for reasonable time.

classes
-------

This program takes string of digits as a parameter and finds expression with a
result of 100. TicketSolver class is rather flexible and can be used separately
in other projects.

platforms and compilers
-----------------------

The following operation systems and compilers are supported:

* Windows / Borland C++ Builder 6
* Windows / Microsoft Visual Studio 2013
* Linux / g++
* Mac OS / LLVM

Project for C++ Builder 6 creates executable with GUI. Others create executable
with CLI.

compiling
---------

For Windows open project file with corresponding IDE and select Build from the
menu. For Linux Makefile is provided, go to linux directory and run make.
  cd linux
  make

license
-------

This program is distributed under the terms of the GNU GPLv2.

GUI icons are from Fugue Icons set by Yusuke Kamiyamane.
<http://p.yusukekamiyamane.com/>

contact
-------

Author of this program is Alexander Yampolsky.
For questions, bug reports, ideas, contributions etc. please contact
yampa@yandex.ru.

For source distribution and binary releases see
https://github.com/ayampolsky/TicketSolver

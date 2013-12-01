======
please
======

-------------------------
execute a command as root
-------------------------

:Manual section: 1


Synopsis
========

| **please** <command>
| **please** -

Description
===========

**Please** aims to be little sudo without bells and whistles.
Only pam authentication and executing command.

Name **please** fits into unix naming conventions.
Where we have daemon instead of background process.
We are killing processes, not closing processes.
Now we can please to run privileged process.


Exit value
==========
Upon successful execution of a program, the exit status will be
the exit status of the program that was executed.

Otherwise, **please** exits with non-zero value.


Files
=====

/etc/pam.d/please or /usr/local/etc/pam.d/please    PAM configuration for please.
It's recommend to create this file on the basis of /etc/pam.d/su


Examples
========

| Reboot system by unprivileged user:
|
|   $ please reboot
|
| To get a file listing of an unreadable directory:
|
|   $ please ls /usr/local/protected
|
| Run a root login shell:
|
|   $ please -

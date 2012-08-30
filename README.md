Please - really tiny sudo replacement
=====================================

'Please' aims to be little sudo without bells and whistles.
Only pam authentication and executing command.


Installation on Ubuntu 12.04
----------------------------
1. Install git, compiler and libpam-dev: __apt-get install git build-essential libpam0g-dev__
2. Clone repository: __git clone git://github.com/MagikBSD/please.git__
3. Build and install __make && make install__


Installation on FreeBSD 9.0
---------------------------
1. Install git: __cd /usr/ports/git && make install clean__
2. Clone repository: __git clone git://github.com/MagikBSD/please.git__
3. Build and install __make && make install__

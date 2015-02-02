Please - really tiny sudo replacement
=====================================

'Please' aims to be little sudo without bells and whistles.
Only pam authentication and executing command.


Installation on Debian 7.8.0
----------------------------
1. Install git, compiler and libpam-dev: __apt-get install git build-essential libpam0g-dev__
2. Install docutils: __apt-get install python-docutils__
3. Clone repository: __git clone https://github.com/MagikBSD/please.git__
4. Build and install: __make && make install__
5. (optional) Install pam rules: __make install-pam__


Installation on FreeBSD 10.1
---------------------------
1. Install git: __make install clean -C /usr/ports/devel/git__
2. Install docutils: __make install clean -C /usr/ports/textproc/py-docutils__
3. Clone repository: __git clone https://github.com/MagikBSD/please.git__
4. Build and install: __make && make install__
5. (optional) Install pam rules: __make install-pam__

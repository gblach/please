Please - really tiny sudo replacement
=====================================

'Please' aims to be little sudo without bells and whistles.
Only pam authentication and executing command.


Installation on Debian / Ubuntu
-------------------------------
1. Install git, compiler and libpam-dev: __apt-get install git build-essential libpam0g-dev__
2. Clone repository: __git clone https://github.com/MagikBSD/please.git__
3. Build and install: __make && make install__
4. Install (and edit) pam rules: __cp pam.d/please.Debian /etc/pam.d/please__


Installation on FreeBSD
-----------------------
1. Install git: __pkg install git__ or __make install clean -C /usr/ports/devel/git__
2. Clone repository: __git clone https://github.com/MagikBSD/please.git__
3. Build and install: __make && make install__
4. Install (and edit) pam rules: __cp pam.d/please.FreeBSD /usr/local/etc/pam.d/please__

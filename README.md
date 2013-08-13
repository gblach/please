Please - really tiny sudo replacement
=====================================

'Please' aims to be little sudo without bells and whistles.
Only pam authentication and executing command.


Installation on Debian 7.1.0
----------------------------
1. Install git, compiler and libpam-dev: __apt-get install git build-essential libpam0g-dev__
2. Install docultis: __apt-get install python-docutils__
3. Clone repository: __git clone https://github.com/MagikBSD/please.git__
4. Build and install: __make && make install__
5. Copy (and edit) pam rules: __cp /etc/pam.d/su /etc/pam.d/please__


Installation on FreeBSD 9.2
---------------------------
1. Install git: __make install clean -C /usr/ports/devel/git__
2. Install docultis: __make install clean -C /usr/ports/textproc/py-docutils__
3. Clone repository: __git clone https://github.com/MagikBSD/please.git__
4. Build and install: __make && make install__
5. Copy (and edit) pam rules: __cp /etc/pam.d/su /usr/local/etc/pam.d/please__

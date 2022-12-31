Please - really tiny sudo replacement
=====================================

'Please' aims to be little sudo without bells and whistles.
Only pam authentication and executing command.

Name **please** fits into unix naming conventions.
Where we have daemon instead of background process.
We are killing processes, not closing processes.
Now we can please to run privileged process.


Examples
--------

Reboot system by unprivileged user:

    $ please reboot

To get a file listing of an unreadable directory:

    $ please ls /usr/local/protected

Run a root shell:

    $ please -


Installation on Debian / Ubuntu
-------------------------------
```
apt-get install git build-essential libpam0g-dev
git clone https://github.com/gblach/please.git
cd please/
make && make install
cp pam.d/please.Debian /etc/pam.d/please
```

Installation on Fedora / CentOS / Alma / Rocky
----------------------------------------------
```
dnf install git gcc pam-devel
git clone https://github.com/gblach/please.git
cd please/
make && make install
cp pam.d/please.Fedora /etc/pam.d/please
```

Installation on openSUSE
------------------------
```
zypper install git gcc make pam-devel
git clone https://github.com/gblach/please.git
cd please/
make && make install
cp pam.d/please.openSUSE /etc/pam.d/please
```

Installation on ArchLinux
-------------------------
```
pacman -S git gcc make
git clone https://github.com/gblach/please.git
cd please/
make && make install
cp pam.d/please.Fedora /etc/pam.d/please
```

Installation on FreeBSD / DragonFly
-----------------------------------

### From package
```
pkg install please
```

### From source
```
make install clean -C /usr/ports/devel/git
git clone https://github.com/gblach/please.git
cd please/
make && make install
mkdir -p /usr/local/etc/pam.d/
cp pam.d/please.BSD /usr/local/etc/pam.d/please
```

Installation on NetBSD
----------------------
```
pkgin install git ca-certificates
git clone https://github.com/gblach/please.git
cd please/
make && make install
cp pam.d/please.BSD /etc/pam.d/please
```

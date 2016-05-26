#! /bin/bash

if ! g++ -o sbin/daemon-p3 source/daemon-p3.cpp ; then
    exit 1
fi

mkdir /opt/daemon-p3
chown root:root /opt/daemon-p3
chmod 755 /opt/daemon-p3

cp opt/server-1.py /opt/daemon-p3/server-1.py
chown root:root /opt/daemon-p3/server-1.py
chmod 755 /opt/daemon-p3/server-1.py

cp opt/server-2.py /opt/daemon-p3/server-2.py
chown root:root /opt/daemon-p3/server-2.py
chmod 755 /opt/daemon-p3/server-2.py

cp opt/server-3.py /opt/daemon-p3/server-3.py
chown root:root /opt/daemon-p3/server-3.py
chmod 755 /opt/daemon-p3/server-3.py

cp sbin/daemon-p3 /usr/sbin/daemon-p3
chown root:root /usr/sbin/daemon-p3
chmod 755 /usr/sbin/daemon-p3

cp init.d/daemon-p3 /etc/init.d/daemon-p3
chown root:root /etc/init.d/daemon-p3
chmod 755 /etc/init.d/daemon-p3

update-rc.d daemon-p3 defaults

service daemon-p3 start

#! /bin/bash

service daemon-p3 stop

rm /etc/init.d/daemon-p3

update-rc.d daemon-p3 remove

rm /usr/sbin/daemon-p3

rm -r /opt/daemon-p3

rm sbin/daemon-p3

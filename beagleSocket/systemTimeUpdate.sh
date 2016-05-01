#!/bin/bash
# add in /etc/rc.local

( /etc/init.d/ntp stop
until ping -nq -c3 8.8.8.8; do
   echo "Waiting for network..."
done
ntpdate -s time.nist.gov
/etc/init.d/ntp start )&
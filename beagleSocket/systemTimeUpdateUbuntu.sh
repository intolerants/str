#!/bin/bash
# add in /etc/rc.local

(until ping -nq -c3 8.8.8.8; do
   echo "Waiting for network..."
done
ntpdate-debian)&
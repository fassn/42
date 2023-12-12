#!/bin/bash

cat /etc/crontab | mail -s "Changes in file /etc/crontab" root

#!/bin/sh
# timestamp

date +%F_%T.%N | sed 's/\s//g'

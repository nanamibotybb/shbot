#!/bin/sh

i=$1

if grep GroupMessage $i > /dev/null
then
    grpno=$(cat $i | json_pp | grep \"group\" -A 1 | grep id | sed 's/[^0-9]//g')
    echo $grpno
    out=groupmsg/$grpno
    mkdir -p $out
    mv $i $out
else
    mv $i other
fi


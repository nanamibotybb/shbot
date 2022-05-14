#!/bin/sh

i=$1

if grep GroupMessage $i > /dev/null
then
    grpno=`jq .data[0].sender.group.id $i`
    echo $grpno
    out=groupmsg/$grpno
    mkdir -p $out
    mv $i $out
else
    mv $i other
fi



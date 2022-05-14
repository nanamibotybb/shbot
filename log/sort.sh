#!/bin/sh

i=$1

if grep '"data":\[\]' $i > /dev/null
then
        mv $i empty/
        exit
fi

event=`jq -r .data[0].type $i`
mkdir -p $event
echo $i $event
mv $i $event

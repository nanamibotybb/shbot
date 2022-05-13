#!/bin/sh

i=$1

if grep '"data":\[\]' $i > /dev/null
then
        mv $i empty/
        exit
fi

event=$(cat $i | jq .data[0].type | sed 's/\"//g') 
mkdir -p $event
echo $i $event
mv $i $event

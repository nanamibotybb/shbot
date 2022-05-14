#!/bin/sh

JSON=~/cache/mymblog.json
NEW=~/cache/weibomsg.tmp
OLD=~/cache/weibomsg

# extracting message into $NEW
if python3 we.py < $JSON > $NEW
then
    touch $OLD # create if not exists

    if diff $OLD $NEW
    then
        echo same msg
    else
        # changed. broadcast
        cat $NEW
        ~/shbot/broadcast $NEW
        
        # update
        cp $NEW $OLD
    fi
else
    echo we.py failed
fi

rm $NEW

#!/bin/sh
# fetch new weibo. if there is new, broadcast.

JSON=~/cache/mymblog.json
JSON_OLD=~/cache/mymblog.json.last

cp $JSON $JSON_OLD 

if timeout 60 python3 ~/shbot/weibo/wd.py > $JSON
then
    if diff $JSON $JSON_OLD > /dev/null
    then
        # same
        echo no news
    else
        # diffs, update & backup
        cp $JSON $JSON_OLD
        cp $JSON ~/log.wb/`~/ts`
        . ~/shbot/weibo/check_new_mymblog.sh
    fi
else
    echo wd.py failed
fi

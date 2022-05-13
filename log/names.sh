#!/bin/sh

for i in */
do
    echo $i

    for j in $i/*
    do
        grep \"name\" $j && break
    done
done

#!/usr/bin/env bash

count=0
meet_fail=0
until [[ meet_fail -eq 1 ]]
do
    count=$((count+1)) 
    ./random_fail.sh
    meet_fail=$?
done
echo "after $count times fail"

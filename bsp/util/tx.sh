#!/bin/bash

code=$1
while read -r ins; do
    hex=($(sed 's/../\\x& /g' <<< $ins))
    echo -en "${hex[3]}${hex[2]}${hex[1]}${hex[0]}" > /dev/ttyS3
done < "$code"

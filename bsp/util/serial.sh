code="/home/waleed/Documents/PlatformIO/Projects/azadi-test/.pio/build/artix7_35t/firmware.hex"
while read -r ins; do
    hex=($(sed 's/../\\x& /g' <<< $ins))
    echo -en "${hex[0]}${hex[1]}${hex[2]}${hex[3]}" > /dev/ttyUSB1
done < "$code"
echo -en '\x00\x00\x0f\xff' > /dev/ttyUSB1
echo -en '\x00\x00\x0f\xff' > /dev/ttyUSB1
echo -en '\x00\x00\x0f\xff' > /dev/ttyUSB1 
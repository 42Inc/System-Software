#/usr/bin/env bash
if (( $# < 3 ))
then
  echo "Usage:"
  echo "\$1 - hash alghoritm (md5 for example)"
  echo "\$2 - out digest file prefix"
  echo "\$3 - file name"
  echo "aborted"
  exit
fi

echo "Get digest $3"
openssl dgst -$1 -out $3.dgst $3
echo "Change first byte in $3"
byte_hex=$[16#$(xxd -seek 0 -l 1 -ps $3)]
byte_dec=0
echo "$byte_hex -> $byte_dec"
printf "0: %02x" $byte_dec | xxd -r - $3
hexdump -C $3
openssl dgst -$1 -out "$2"_"$3".dgst $3

echo "Change first byte to old value in $3"
printf "0: %02x" $byte_hex | xxd -r - $3

echo "Diff hash for $3"
diff "$2"_"$3".dgst $3.dgst --color=auto

echo "Complete."

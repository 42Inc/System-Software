#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - hash alghoritm (md5 for example)"
  echo "\$2 - out digest file prefix"
  echo "aborted"
  exit
fi

echo "Get digest testfile_1.dat"
openssl dgst -$1 -out testfile_1.dat.dgst testfile_1.dat
echo "Get digest testfile_2.bin"
openssl dgst -$1 -out testfile_2.bin.dgst testfile_2.bin
echo "Change first byte in testfile_1.dat"
byte_hex=$[16#$(xxd -seek 0 -l 1 -ps testfile_1.dat)]
byte_dec=0
echo "$byte_hex -> $byte_dec"
printf "0: %02x" $byte_dec | xxd -r - testfile_1.dat
hexdump -C testfile_1.dat
openssl dgst -$1 -out "$2"_testfile_1.dat.dgst testfile_1.dat

echo "Change first byte to old value in testfile_1.dat"
printf "0: %02x" $byte_hex | xxd -r - testfile_1.dat

echo "Change first byte in testfile_2.bin"
byte_hex=$[16#$(xxd -seek 0 -l 1 -ps testfile_2.bin)]
byte_dec=0
echo "$byte_hex -> $byte_dec"
printf "0: %02x" $byte_dec | xxd -r - testfile_2.bin
hexdump -C testfile_2.bin
openssl dgst -$1 -out "$2"_testfile_2.bin.dgst testfile_2.bin
echo "Change first byte to old value in testfile_2.bin"
printf "0: %02x" $byte_hex | xxd -r - testfile_2.bin
echo "Complete."

echo "Diff hash for testfile_1.dat"
diff "$2"_testfile_1.dat.dgst testfile_1.dat.dgst --color=auto

echo "Diff hash for testfile_2.bin"
diff "$2"_testfile_2.bin.dgst testfile_2.bin.dgst --color=auto

echo "Complete."

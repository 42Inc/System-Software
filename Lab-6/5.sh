#/usr/bin/env bash
if (( $# < 1 ))
then
  echo "Usage:"
  echo "\$1 - key file"
  echo "aborted"
  exit
fi
echo "Encrypt testfile_1.dat"
openssl rsautl -encrypt -inkey $1.pub -pubin -in testfile_1.dat -out task2_testfile_1.dat.enc
echo "Encrypt testfile_2.bin"
openssl rsautl -encrypt -inkey $1.pub -pubin -in testfile_2.bin -out task2_testfile_2.bin.enc
echo "Complete."

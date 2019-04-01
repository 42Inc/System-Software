#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - encryption (aes-128-cbc for example. ./manual.sh for help)"
  echo "\$2 - secret"
  echo "aborted"
  exit
fi
echo "Encrypt testfile_1.dat"
openssl enc -e -$1 -in testfile_1.dat -out task1_testfile_1.dat.enc -k $2
echo "Encrypt testfile_2.bin"
openssl enc -e -$1 -in testfile_2.bin -out task1_testfile_2.bin.enc -k $2
echo "Complete."

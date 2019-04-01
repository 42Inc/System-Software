#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - encryption (-aes-128-cbc for example)"
  echo "\$2 - secret"
  echo "aborted"
  exit
fi
openssl enc -e $1 -in testfile_1.dat -out task1_testfile_1.dat.enc -k $2
openssl enc -e $1 -in testfile_2.bin -out task1_testfile_2.bin.enc -k $2

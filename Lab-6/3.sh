#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - encryption (-aes-128-cbc for example)"
  echo "\$2 - secret"
  echo "aborted"
  exit
fi
openssl enc -d $1 -in task1_testfile_1.dat.enc -out task1_testfile_1.dat.dec -k $2
openssl enc -d $1 -in task1_testfile_2.bin.enc -out task1_testfile_2.bin.dec -k $2

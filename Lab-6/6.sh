#/usr/bin/env bash
if (( $# < 1 ))
then
  echo "Usage:"
  echo "\$1 - key file"
  echo "aborted"
  exit
fi
echo "Decrypt task2_testfile_1.dat.enc with public-key"
openssl rsautl -decrypt -inkey $1.pub -in task2_testfile_1.dat.enc -out task2_testfile_1.dat.dec.pub
echo "Decrypt task2_testfile_2.bin.enc with public-key"
openssl rsautl -decrypt -inkey $1.pub -in task2_testfile_2.bin.enc -out task2_testfile_2.bin.dec.pub

echo "Decrypt task2_testfile_1.dat.enc with private-key"
openssl rsautl -decrypt -inkey $1 -in task2_testfile_1.dat.enc -out task2_testfile_1.dat.dec
echo "Decrypt task2_testfile_2.bin.enc with private-key"
openssl rsautl -decrypt -inkey $1 -in task2_testfile_2.bin.enc -out task2_testfile_2.bin.dec
echo "Complete."

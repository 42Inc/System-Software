#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - key file"
  echo "\$2 - file name"
  echo "aborted"
  exit
fi
echo "Decrypt task2_$2.enc with public-key"
openssl rsautl -decrypt -inkey $1.pub -in task2_"$2".enc -out task2_"$2".dec.pub

echo "Decrypt task2_$2.enc with private-key"
openssl rsautl -decrypt -inkey $1 -in task2_"$2".enc -out task2_"$2".dec
echo "Complete."

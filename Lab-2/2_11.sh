#!/usr/bin/env bash
ls -lahX | grep .c

printf "Enter filename: "
read FILE

if [[ $FILE == "" ]]
then
  echo "Aborted"
  exit 1
else
  if [ -f $FILE ]
  then
    gcc $FILE
    ./a.out
  fi
fi

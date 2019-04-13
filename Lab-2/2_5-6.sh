#!/usr/bin/env bash
printf "Enter command: "

read cmd

if [[ $cmd == "" ]]
then
  echo "Aborted"
  exit 1
else
  $cmd
fi

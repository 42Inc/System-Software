#!/usr/bin/env bash

while `./cmpl $1`
do
  echo "Param, $1"
  shift
done

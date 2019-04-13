#!/usr/bin/env bash

echo "1:"
ls 1_7 | grep -E "file." --color=auto
echo "----"
ls 1_7 | grep -E "file[[:digit:]]" --color=auto
echo "2:"
ls 1_7 | grep -E "f[iar][liox](.){0,1}" --color=auto
echo "----"
ls 1_7 | grep -E "f..?" --color=auto
echo "3:"
ls 1_7 | grep -E "[adqfj][sfwk][dgeals]" --color=auto
echo "4:"
ls 1_7 | grep -E "a[dewl]ks" --color=auto
echo "----"
ls 1_7 | grep -E "a.ks" --color=auto

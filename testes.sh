#!/bin/sh

bold="\033[1m"
yellow="\033[33m"
red="\033[31m"
green="\033[32m"
white="\033[37m"
default="\033[30m"

test_dir=$1
target=$2

make TARGET=$target > /dev/null

for test_file in $test_dir/*.in
do
  base_name="${test_file%.*}"
  test_name="${base_name##*/}"
  sol_file="$base_name.sol"
  out_file="$base_name.out"
  diff_file="$base_name.diff"

  ./$target < $test_file > $out_file

  echo -n "${bold}${yellow}Test: ${white}$test_name "
  if diff -y -W 80 $out_file $sol_file > $diff_file
  then
    echo -n "${green}passed"
  else
    echo "${red}failed${white}"
    cat $diff_file
  fi
  echo "$default"

  rm $out_file $diff_file
done

make purge TARGET=$target

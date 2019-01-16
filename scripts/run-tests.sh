#!/bin/bash

for_all_books() {
  echo "> ALICE’S ADVENTURES IN WONDERLAND: 170 KB"
  for i in {1..10}; do
    ./find-pattern -a "$2" -c "$1" -t "$3" -p ../res/books/matching-alice.txt -d ../res/books/alice_in_the_wonderland.txt
  done

  echo "> PRIDE AND PREJUDICE: 708 KB"
  for i in {1..10}; do
    ./find-pattern -a "$2" -c "$1" -t "$3" -p ../res/books/matching-pride.txt -d ../res/books/pride_and_prejudice.txt
  done

  echo "> WAR AND PEACE: 3.2 MB"
  for i in {1..10}; do
    ./find-pattern -a "$2" -c "$1" -t "$3" -p ../res/books/matching-war.txt -d ../res/books/war_and_peace.txt
  done
}

test() {
  echo ">>> $1"

  COUNTER=1
  if [ "$1" == "multithreaded" ]; then
    COUNTER=3
  fi

  for k in $(eval echo {"1..$COUNTER"}); do
    echo "> Naive: $k thread(s)"
    for_all_books $1 "naive" $k
  done

  for k in $(eval echo {"1..$COUNTER"}); do
    echo "> Winnowing: $k thread(s)"
    for_all_books $1 "winnowing" $k
  done
}

test "sequential"
test "multithreaded"
test "gpu"

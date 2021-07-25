#! /bin/bash
set -x

docker build -f $1 . -t $2

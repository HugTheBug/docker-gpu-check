#! /bin/bash
set -x

docker build . -t $1

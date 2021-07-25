#! /bin/bash
set -x

docker run -it --rm --gpus all $1

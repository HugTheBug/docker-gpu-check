#! /bin/bash
set -x

docker run -it --rm --gpus all -v /etc/vulkan/icd.d/nvidia_icd.json:/etc/vulkan/icd.d/nvidia_icd.json:ro $1

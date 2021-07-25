FROM ubuntu:20.04

RUN apt update && apt -y install lshw pciutils

ADD check.sh /

RUN chmod +x check.sh

CMD ["./check.sh"]

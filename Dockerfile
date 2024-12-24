# Start from a clean Ubuntu base image
FROM ubuntu:24.04

RUN apt-get update -y && apt-get install -y \
    lib32z1 xinetd libcapstone-dev \
    && rm -rf /var/lib/apt/lists/*

RUN useradd hacker

# Create necessary directories
RUN mkdir -p /pwn/challenge
RUN echo "You've been blocked by our server,try again, and report if this repeats." > /etc/banner_fail

# Copy precompiled challenge binary and necessary files
COPY ./ctf.xinetd /etc/xinetd.d/pwn
COPY ./start.sh /start.sh
COPY ./setup.sh /setup.sh
COPY ./chal /pwn/
COPY ./challenge/chal.c /pwn/challenge/
COPY ./challenge/val.c /pwn/challenge/
COPY ./challenge/validator.h /pwn/challenge/
COPY ./flag.txt /pwn/flag.txt

RUN chown -R root:hacker /pwn && chmod -R 750 /pwn
RUN chmod +x /setup.sh
RUN chmod +x /setup.sh
RUN chown root:hacker /start.sh && chmod 750 /start.sh

CMD ["/setup.sh"]

EXPOSE 8001

FROM ubuntu:16.04
RUN apt-get update && apt-get -y install python socat
COPY sandbox-runner .
COPY flag.txt .
COPY flag.txt flag
EXPOSE 9001
CMD socat TCP-LISTEN:9001,reuseaddr,fork EXEC:"./sandbox-runner"

FROM ubuntu:latest as env

RUN apt update
RUN apt install -y gcc g++ libboost-dev cmake
RUN apt install -y libpq-dev postgresql-server-dev-all

FROM env as build

COPY . /app

WORKDIR /app/bin

RUN cmake ..
RUN cmake --build . --target server

WORKDIR /app

RUN groupadd -r sample && useradd -r -g sample sample
USER sample

EXPOSE 8080

ENTRYPOINT ./bin/server

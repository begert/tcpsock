# tcp socket client / server

## install build environment

    sudo apt install linux-headers-$(uname -r)
    sudo apt install build-essentials

## compile them with

    make

## in terminal one, start the server with

    ./server 8888

## in terminal two, start the client with

    ./client 127.0.0.1 esel 8888

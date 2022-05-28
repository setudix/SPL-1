#!/bin/bash

#g++ -std=c++17 -Wshadow -Wall -o main src/* -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

g++ -std=c++17 -g -o main src/* -lpthread -lX11 -fconcepts

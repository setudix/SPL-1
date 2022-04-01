#!/bin/bash

#g++ -std=c++17 -Wshadow -Wall -o main src/* -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

g++ -std=c++17 -o main src/* -lpthread -fconcepts

#!/bin/bash

echo "Installing doxygen if not already installed"

sudo apt-get install doxygen

echo "Running doxygen documentation generation"

mkdir doc
doxygen stm32f2_cube/Doxyfile


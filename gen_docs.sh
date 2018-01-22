#!/bin/bash

echo "Installing doxygen if not already installed"

sudo apt-get install doxygen

echo "Running doxygen documentation generation"

mkdir doc
cd stm32f2_cube
doxygen Doxyfile


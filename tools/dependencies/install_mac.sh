#!/bin/bash

echo "This script will install Boost libraries required for the distributed-kv-store project"
read -p "Do you want to proceed with the installation? (y/n): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo "Installing Boost libraries..."
    brew install boost cmake
    echo "Checking Boost installation..."
    brew list boost
    echo "Installation completed!"
else
    echo "Installation cancelled."
fi
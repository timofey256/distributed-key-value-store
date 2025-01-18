#!/bin/bash

echo "This script will install Boost libraries required for the distributed-kv-store project"
echo "This will require sudo privileges."
read -p "Do you want to proceed with the installation? (y/n): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo "Installing Boost libraries..."
    sudo apt-get update
    sudo apt-get install -y build-essential cmake libboost-all-dev
    echo "Checking Boost installation..."
    dpkg -l | grep libboost
    echo "Installation completed!"
else
    echo "Installation cancelled."
fi

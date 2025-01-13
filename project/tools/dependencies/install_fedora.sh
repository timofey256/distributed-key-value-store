#!/bin/bash

echo "This script will install Boost libraries required for the distributed-kv-store project"
echo "This will require sudo privileges."
read -p "Do you want to proceed with the installation? (y/n): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo "Installing Boost libraries..."
    sudo dnf install -y boost boost-devel cmake gcc-c++
    echo "Checking Boost installation..."
    rpm -qa | grep boost
    echo "Installation completed!"
else
    echo "Installation cancelled."
fi
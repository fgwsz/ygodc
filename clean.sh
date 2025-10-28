#!/bin/bash
root_path=$(dirname "$(readlink -f "$0")")
build_path="$root_path/build/linux"
project_name="ygodc"
binary_release_path="$root_path/$project_name"

if [ -d "$build_path" ]; then
    rm -rf "$build_path"
fi

if [ -e "$binary_release_path" ]; then
    rm -rf "$binary_release_path"
fi

#!/usr/bin/env python3
import os
import subprocess

os.chdir(os.getcwd())
subprocess.run("clang-format *.hpp ./tests/*.cpp ./tests/*.hpp -i".split(" "))

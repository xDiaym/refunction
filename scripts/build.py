#!/usr/bin/env python3
import os
import shutil
import subprocess

PATH = os.getcwd()
BUILD_DIR = os.path.join(PATH, "build")

if os.path.exists(BUILD_DIR):
    shutil.rmtree(BUILD_DIR)
os.mkdir(BUILD_DIR)
os.chdir(BUILD_DIR)
subprocess.run("cmake ..".split(" "))
subprocess.run("cmake --build .".split(" "))

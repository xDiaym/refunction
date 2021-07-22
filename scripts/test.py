#!/usr/bin/env python3
import os
import subprocess

PATH = os.getcwd()
BUILD_DIR = os.path.join(PATH, "build")

subprocess.run("scripts/build.py")
os.chdir(BUILD_DIR)
subprocess.run("ctest ./bui".split())

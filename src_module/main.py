from __future__ import print_function
import sys
import os

import faulthandler
faulthandler.enable()


build_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../build')
print(build_dir)
sys.path.append(build_dir)

import kakoune


print(kakoune.get_kak_binary_path())
print(kakoune.parse_filename('$HOME/hi/world'))
#print(kakoune.list_files('./'))

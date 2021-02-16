#!  /bin/sh
#   tools/gen-source.py
#
#       Generate source files for OpenGL
#       interface and embedded data.
#
#   Copyright (c) 2021 Mitya Selivanov
#
#   This file is part of the Laplace project.
#
#   Laplace is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty
#   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
#   the MIT License for more details.

./update-gl.sh

echo "[ Generate OpenGL interface ]"
python ./gen-gl.py

echo "[ Generate embedded data code ]"
python ./embed.py

#!/bin/bash

find ./src -iname *.h -o -iname *.cpp | xargs clang-format-12 -i -style=Google
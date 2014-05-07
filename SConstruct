# coding=utf-8
# Author: Mathias Hablützel <habl@zhaw.ch>
# Copyright: 2014 ZHAW
#
# Tested under:
#   * LINUX
#     * FC20 sec spin, scons 2.3.0
#   * OSX
#     * 10.9.2 Mavericks, 2.3.0
#
# IMPORTANT:
# Linux requires you to indicate the shared library path
# or to put the .so in a ldconfig included path. For dev
# purposes you can use the environmental variable. It is
# explicitly not mentioned here and it also require you to
# actually understand what this does and implies!

VariantDir('build', 'src')
SConscript(['build/core/SConscript', 'build/examples/SConscript', 'build/demo/SConscript'])

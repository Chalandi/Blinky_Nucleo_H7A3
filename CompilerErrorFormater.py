#####################################################################################
# 
# Filename    : CompilerErrorFormater.py
# 
# Author      : Chalandi Amine
#
# Owner       : Chalandi Amine
# 
# Date        : 28.04.2021
# 
# Description : Format the compiler error output into the Visual studio style
# 
#####################################################################################

import sys
import re
import os

os.system("")

# ANSI color code definition
class Style:
    BLACK = '\033[30m'
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    BLUE = '\033[34m'
    MAGENTA = '\033[35m'
    CYAN = '\033[36m'
    WHITE = '\033[37m'
    UNDERLINE = '\033[4m'
    RESET = '\033[0m'

# Command-line syntax :  py  <InputFile>  <{-COLOR|-NOCOLOR}>

# Get command-line parameters
Cmd, InputFile, ColorFlag = sys.argv

warning_pattern = ": warning:"
error_pattern = ": error:"
note_pattern = ": note:"
warning_pattern_U = ": Warning:"
error_pattern_U = ": Error:"
note_pattern_U = ": Note:"


def vs_format_msg(text, pattern, color):
    compiler_msg = text[(text.find(pattern) + len(pattern)):]
    file_path = (re.search("\D.*\.\w", text)).group(0)
    if (re.search("\:\d+\:", text)) != None:
      line_number = "(" + (re.search("\d+", (re.search("\:\d+\:", text)).group(0))).group(0) +")"
    else:
      line_number = ""
    vs_msg = file_path + line_number + pattern + compiler_msg
    if ColorFlag=="-COLOR":
      print(color + vs_msg.strip() + Style.RESET)
    else:
      print(vs_msg.strip())


err_file = open(InputFile, 'r')

lines = err_file.readlines()

for line in lines:

    if line.find(warning_pattern) > 0:
        vs_format_msg(line, warning_pattern, Style.YELLOW)

    if line.find(error_pattern) > 0:
        vs_format_msg(line, error_pattern, Style.RED)

    if line.find(note_pattern) > 0:
        vs_format_msg(line, note_pattern, Style.BLUE)

    if line.find(warning_pattern_U) > 0:
        vs_format_msg(line, warning_pattern_U, Style.YELLOW)

    if line.find(error_pattern_U) > 0:
        vs_format_msg(line, error_pattern_U, Style.RED)

    if line.find(note_pattern_U) > 0:
        vs_format_msg(line, note_pattern_U, Style.BLUE)

err_file.close()


# Use this script to compile the test.cpp source code
# You can specify a command-line parameter for the output binary file name

import os
import sys

output_bin_name = 'test'

if len(sys.argv) == 2:
  output_bin_name = sys.argv[1]

os.system('g++ -Wall -std=c++11 '
          'test.cpp memory_unit.cpp '
          'task.cpp page.cpp memory_management.cpp -o "%s"' % (output_bin_name))
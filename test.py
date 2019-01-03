#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import os
import signal
import subprocess
import argparse
import textwrap



def execute(cmd):
    proc = subprocess.Popen(cmd, shell=True, stdin=subprocess.DEVNULL, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = proc.communicate()
    output = output.decode('unicode-escape').rstrip()
    error = error.decode('unicode-escape').rstrip()
    rc = proc.returncode
    return (output, rc, error)


def title(str):
    print('-' * (len(str) + 4))
    print('| ' + str + ' |')
    print('-' * (len(str) + 4))
    print()


def tests_nm(tests_array, args, opt):

    errors = 0

    if len(tests_array) == 0 :
        return errors
    # get the longest test name, useful for padding
    max_len = max(tests_array, key=len)
    max_len = len(max_len)

    for t in tests_array:

        # execute nm and ft_nm
        if opt:
            nm_out , nm_rc , _ = execute("{} -{} {}".format("nm", opt, t))
            out , rc , err = execute("{} -{} {}".format(NM_PATH, opt, t))
        else:
            nm_out , nm_rc , _ = execute("{} {}".format("nm", t))
            out , rc , err = execute("{} {}".format(NM_PATH, t))

        # compare their return value and output
        if rc == -signal.SIGSEGV:
            result = "\033[91mSEGMENTATION FAULT\033[0m"
            errors += 1
        elif nm_rc != 0 and rc != 0:
            result = "\033[92mOK\033[0m: \033[93mWARNING\033[0m nm returned {} and ft_nm returned {} but the error messages were not compared for more flexibility".format(nm_rc, rc)
        elif rc != nm_rc:
            result = "\033[91mERROR\033[0m: nm returned {}, ft_nm returned {}.".format(nm_rc, rc)
            errors += 1
        elif nm_out != out:
            result = "\033[91mERROR\033[0m: output differs"
            errors += 1
        else:
            result = "\033[92mOK\033[0m"

        if args.errors and "OK" in result:
           continue
        print("\t+ {:{length}} {result}".format(t, length=max_len, result=result))

    return errors




def tests_main(args):

    errors = 0
    strings = ["toto", "a", "pickle rick"]

    if errors:
        print("\n[!] total amount of errors: \033[91m{}\033[0m".format(errors))
    else:
        print("\n[T]/ no error occured, \033[92mgood job!\033[0m")

    return errors


if __name__ == '__main__':



    # if len(sys.argv[1:]) == 0:
    #     parser.print_usage() # for just the usage line
    #     parser.exit()

    args = {}#parser.parse_args()


    sys.exit(tests_main(args))

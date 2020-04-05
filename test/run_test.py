# -*- coding: utf-8 -*-
import sys, io, os, json, subprocess
from generate_test import generate_test_file

def handle_no_test_file(cwd, arg):
    dirs = cwd.split('/')
    contest_type = dirs[-2]
    contest_num = dirs[-1]
    task = arg.split('.')[0]

    print('No test file found.')
    generate_test_file(test_file, contest_type, contest_num, task)
    print('Test file has been created.\n')

def handle_cpe(cpe):
    print('Exited with return code {}.'.format(cpe.returncode))
    print(cpe.stderr.decode(encoding='utf-8'))

def compile_cpp(src, exe):
    try:
        subprocess.run(
            ["g++", "-std=c++14", "-o", exe_file, src_file],
            stderr=subprocess.PIPE,
            check=True)
    except subprocess.CalledProcessError as cpe:
        handle_cpe(cpe)
        exit()

def get_test_json(test_file):
    test_json = {}
    with open(test_file, 'r', encoding='utf-8') as f:
        test_json = json.load(f)
    return test_json

def print_test_result(exe_file, case):
    print("Test case {}".format(case['num']))

    expected = case['output']
    print('Expected:\n{}'.format(expected))

    print('Actual:')
    try:
        completed_process = subprocess.run(
            [exe_file], 
            input=bytearray(case['input'], 'utf8'), 
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True)
        actual = completed_process.stdout.decode(encoding='utf-8')
        print(actual)
        print('Judge: {}'.format('AC' if actual == expected else 'WA'))
    except subprocess.CalledProcessError as cpe:
        handle_cpe(cpe)
    finally:
        print("----------")

cwd = os.getcwd()
arg = sys.argv[1]

src_file = cwd + '/' + arg
exe_file = src_file.replace('.cpp', '.out')
test_file = src_file.replace('.cpp', '.json')

# create test file
if not os.path.exists(test_file):
   handle_no_test_file(cwd, arg)

# compile c++ code
compile_cpp(src_file, exe_file)

# run test
for case in get_test_json(test_file)['test_cases']:
    print_test_result(exe_file, case)
# -*- coding: utf-8 -*-
from bs4 import BeautifulSoup
import requests
import sys, json
import config

def login(session):
    LOGIN_URL = 'https://atcoder.jp/login'
    UN = config.username
    PW = config.password

    # csrf_token取得
    res = session.get(LOGIN_URL)
    soup = BeautifulSoup(res.text, 'lxml')
    csrf_token = soup.find(attrs={'name': 'csrf_token'}).get('value')

    # パラメータセット
    login_info = {
        "csrf_token": csrf_token,
        "username": UN,
        "password": PW
    }

    result = session.post(LOGIN_URL, data=login_info)
    result.raise_for_status()

    return result.status_code

def parse_html(body):
    soup = BeautifulSoup(body, 'lxml')

    # 入力例・出力例のリスト作成
    sections = soup.find_all('section')
    input_list = []
    output_list = []

    for section in sections:
        if section.find('h3') and section.find('pre'):
            label = section.find('h3').text.replace('\r', '')
            value = section.find('pre').text.replace('\r', '')
            if label.startswith('Sample Input'):
                input_list.append(value)
            elif label.startswith('Sample Output'):
                output_list.append(value)

    test_cases = []

    for i in range(0, len(input_list)):
        test_case = {
            'num': i + 1,
            'input': input_list[i],
            'output': output_list[i]
        }
        test_cases.append(test_case)

    test_cases_obj = { 'test_cases': test_cases }

    return test_cases_obj

def get_task_url(contest_type, contest_num, task):
    return 'https://atcoder.jp/contests/{contest_type}{contest_num}/tasks/{contest_type}{contest_num}_{task}?lang=en'.format(
        contest_type=contest_type, contest_num=contest_num, task=task)

def create_test_file(path, test_cases_obj):
    json_str = json.dumps(test_cases_obj)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(json_str)

def generate_test_file(path, contest_type, contest_num, task):
    with requests.Session() as session:
        response_code = login(session)
        if response_code == 200:
            res = session.get(get_task_url(contest_type, contest_num, task))
            test_cases_obj = parse_html(res.text)
            create_test_file(path, test_cases_obj)
        else:
            print("Failed to log in...")
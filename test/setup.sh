# sourceで実行する

# run_test.pyを実行するためのモジュール
pip3 install -r ~/atcoder/test/requirements.txt

# test aliasの設定
source ~/.bashrc
if test $(alias | grep -c 'alias test=') -lt 1 ; then
    echo "alias test='python3 -B ~/atcoder/test/run_test.py'" >> ~/.bashrc
    echo 'Test alias has been created.'
else
    echo 'Test alias already exists.'
fi
source ~/.bashrc
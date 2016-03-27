set -e
cd `dirname $0`
cd ../../
rm -fr *.tar *.bz2
tar -cf engine.tar engine
bzip2 engine.tar

gen(){
    echo "set -e"
    echo "mkdir -p ~/tmp"
    echo "cd ~/tmp"
    echo "rm -fr engine"
    echo "p='"
    echo "`base64 engine.tar.bz2 | ./engine/install/chunk.py`"
    echo "'"
    echo 'echo $p | tr -d " " | base64 --decode | tar -xj'
    echo 'cd engine && ./configure && . ./go-cfg && make all'
    echo "./script/worker.sh"
}

gen > engine/install/install-engine.sh

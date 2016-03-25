rs=build/bin/render-server
ps=build/bin/server.out

run(){
    port1=7777
    port2=8080

    $rs $port1 &
    pid1=$!

    addr="localhost:$port1"
    self="localhost:$port2"
    $ps --addr "$addr" --addrs "" --port $port2 &
    pid2=$!
}

run

echo "render server pid=$pid1"
echo "proxy server pid=$pid2"

q(){
    echo quit
    kill -s TERM $pid2
    kill -s INT $pid1
}

trap q INT

wait

rs=build/bin/render-server
ps=build/bin/server.out

run(){
    port=7777
    $rs $port &
    p1=$!
    $ps --addr "localhost:$port" --port 8080 &
    p2=$!
}

run

echo "render server: " $p1
echo "proxy server: " $p2

q(){
    echo quit
    kill -s TERM $p2
    kill -s INT $p1
}

trap q INT

wait

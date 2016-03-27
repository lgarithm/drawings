render_server=build/bin/render-server
proxy_server=build/bin/server.out

port=8080

run(){
    internal_port=7777
    $render_server $internal_port &
    pid1=$!
    $proxy_server --addr "localhost:$internal_port" --port $port &
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

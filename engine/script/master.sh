rs=build/bin/render-server
ps=build/bin/server.out

master(){
    port=9999
    $ps --addrs "$1" --port $port
}

master $@

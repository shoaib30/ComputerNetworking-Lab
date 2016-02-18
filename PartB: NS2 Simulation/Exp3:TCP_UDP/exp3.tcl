set netSimInstance [new Simulator]

set namFile [open namOutput.nam w]
set traceFile [open traceOutput.tr w]
$netSimInstance trace-all $traceFile
$netSimInstance namtrace-all $namFile

exec echo "Starting Simulation" &

proc finish {}   {
    global netSimInstance namFile traceFile
    $netSimInstance flush-trace
    close $namFile
    close $traceFile
    exec gawk -f exp3.awk traceOutput.tr &
    exec nam namOutput.nam &
    exit 0
}

exec echo "Creating Nodes" &
set node0 [$netSimInstance node]
set node1 [$netSimInstance node]
set node2 [$netSimInstance node]
set node3 [$netSimInstance node]

$netSimInstance color 1 blue
$netSimInstance color 2 red

exec echo "Setting Colors for each node" &
$node0 color blue
$node1 color red
$node2 color purple
$node3 color orange

exec echo "Creating duplex links between nodes" &
$netSimInstance duplex-link $node0 $node2 1Mb 10ms DropTail
$netSimInstance duplex-link $node1 $node2 1Mb 10ms DropTail
$netSimInstance duplex-link $node2 $node3 1Mb 10ms DropTail

#set positions for each node on nam
$netSimInstance duplex-link-op $node0 $node2 orient right-up
$netSimInstance duplex-link-op $node1 $node2 orient right-down
$netSimInstance duplex-link-op $node2 $node3 orient right

#set queue size at node2
$netSimInstance queue-limit $node2 $node3 10
#set queue monitor at node2
$netSimInstance duplex-link-op $node2 $node3 queuePos 0.5

$node0 label TCP
$node1 label UDP
$node2 label TCPSink/NullSink

exec echo "Creating TCP agent at node0" &
set TCPAgent0 [new Agent/TCP]
$netSimInstance attach-agent $node0 $TCPAgent0

$TCPAgent0 set fid_ 1
$TCPAgent0 set class_ 1

exec echo "Creating FTP application at node0" &
set FTPApplication0 [new Application/FTP]
$FTPApplication0 attach-agent $TCPAgent0

exec echo "Creating UDP agent at node1" &
set UDPAgent0 [new Agent/UDP]
$netSimInstance attach-agent $node1 $UDPAgent0

$UDPAgent0 set fid_ 2
$UDPAgent0 set class_ 2

exec echo "Creating CBR traffic from node1" &
set CBRTrafficAgent0 [new Application/Traffic/CBR]
$CBRTrafficAgent0 set packetSize_ 500
$CBRTrafficAgent0 set interval_ 0.005
$CBRTrafficAgent0 attach-agent $UDPAgent0

exec echo "Creating TCP sink at node3" &
set TCPSink0 [new Agent/TCPSink]
$netSimInstance attach-agent $node3 $TCPSink0
$netSimInstance connect $TCPAgent0 $TCPSink0

exec echo "Creating Null Sink at node3" &
set nullSink0 [new Agent/Null]
$netSimInstance attach-agent $node3 $nullSink0
$netSimInstance connect $UDPAgent0 $nullSink0

exec echo "Setting time for each node" &
$netSimInstance at 0.5 "$FTPApplication0 start"
$netSimInstance at 1.0 "$CBRTrafficAgent0 start"
$netSimInstance at 9.5 "$FTPApplication0 stop"
$netSimInstance at 9.0 "$CBRTrafficAgent0 stop"
$netSimInstance at 10.0 "finish"

exec echo "Running the Script" &
$netSimInstance run

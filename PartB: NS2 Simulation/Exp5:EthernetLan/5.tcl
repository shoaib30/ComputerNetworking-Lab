set netSimInstance [new Simulator]
set namFile [open namOutput.nam w]
set traceFile [open traceOutput.tr w]
$netSimInstance trace-all $traceFile
$netSimInstance namtrace-all $namFile

proc finish {}   {
    global netSimInstance traceFile namFile
    $netSimInstance flush-trace
    close $traceFile
    close $namFile
    exec gawk -f 5.awk traceOutput.tr &
    exec nam namOutput.nam &
    exit 0
}

set node0 [$netSimInstance node]
set node1 [$netSimInstance node]
set node2 [$netSimInstance node]
set node3 [$netSimInstance node]
set node4 [$netSimInstance node]
set node5 [$netSimInstance node]

$netSimInstance color 1 red
$netSimInstance color 2 blue

$node1 color blue
$node1 shape box
$node5 color blue
$node5 shape box
$node0 color red
$node4 color red

$netSimInstance duplex-link $node0 $node2 1Mb 10ms DropTail
$netSimInstance duplex-link $node1 $node2 1Mb 10ms DropTail
$netSimInstance simplex-link $node2 $node3 0.3Mb 100ms DropTail
$netSimInstance simplex-link $node3 $node2 0.3Mb 100ms DropTail

set lan [$netSimInstance newLan "$node3 $node4 $node5" 0.5Mb 40ms LL Queue/DropTail MAC/Csma/Cd Channel]

$netSimInstance duplex-link-op $node0 $node2 orient right-down
$netSimInstance duplex-link-op $node1 $node2 orient right-up
$netSimInstance simplex-link-op $node2 $node3 orient right
$netSimInstance simplex-link-op $node3 $node2 orient left

set TCPAgent [new Agent/TCP/Newreno]
$netSimInstance attach-agent $node0 $TCPAgent
$TCPAgent set fid_ 1
$TCPAgent set packetSize_ 552

set TCPSink [new Agent/TCPSink/DelAck]
$netSimInstance attach-agent $node4 $TCPSink
$netSimInstance connect $TCPAgent $TCPSink

set FTPApplication [new Application/FTP]
$FTPApplication attach-agent $TCPAgent

set UDPAgent [new Agent/UDP]
$netSimInstance attach-agent $node1 $UDPAgent
$UDPAgent set fid_ 2
set nullSink [new Agent/Null]
$netSimInstance attach-agent $node5 $nullSink
$netSimInstance connect $UDPAgent $nullSink

set CBRApplication [new Application/Traffic/CBR]
$CBRApplication attach-agent $UDPAgent
$CBRApplication set type_ CBR
$CBRApplication set packetSize_ 1000
$CBRApplication set rate_ 0.05Mb
$CBRApplication set random_ false

$netSimInstance at 0.0 "$node0 label TCP_Traffic"
$netSimInstance at 0.0 "$node1 label UDP_Traffic"
$netSimInstance at 0.3 "$CBRApplication start"
$netSimInstance at 0.8 "$FTPApplication start"
$netSimInstance at 7.0 "$FTPApplication stop"
$netSimInstance at 7.5 "$CBRApplication stop"
$netSimInstance at 8.0 "finish"
$netSimInstance run

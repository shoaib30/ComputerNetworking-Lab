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
    exec gawk -f 6.awk traceOutput.tr > awkop.txt &
    exec nam namOutput.nam &
    exit 0
}

set node0 [$netSimInstance node]
set node1 [$netSimInstance node]
set node2 [$netSimInstance node]
set node3 [$netSimInstance node]
set node4 [$netSimInstance node]
set node5 [$netSimInstance node]
set node6 [$netSimInstance node]

$netSimInstance make-lan "$node0 $node1 $node2 $node3 $node4 $node5 $node6" 0.2Mb 40ms LL Queue/DropTail Mac/802_3

set TCPAgent [new Agent/TCP]
$netSimInstance attach-agent $node0 $TCPAgent
set TCPSink [new Agent/TCPSink]
$netSimInstance attach-agent $node5 $TCPSink
$netSimInstance connect $TCPAgent $TCPSink

set FTPApplication [new Application/FTP]
$FTPApplication attach-agent $TCPAgent

$netSimInstance at 1.0 "$FTPApplication start"
$netSimInstance at 5.0 "$FTPApplication stop"
$netSimInstance at 5.5 "finish"
$netSimInstance run

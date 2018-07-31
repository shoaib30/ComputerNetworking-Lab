#Creating an instance of network simulator
set netSimInstance [new Simulator]

#defining the NAM file and setting netSim to trace to that file
set namFile [open namOutput.nam w]
$netSimInstance namtrace-all $namFile
set traceFile [open traceOutput.tr w]
$netSimInstance trace-all $traceFile

#procedure is called at the end of simulation to flush the trace to nam file and execute the command to run Nam
proc finish {}   {
    global netSimInstance namFile traceFile
    $netSimInstance flush-trace
    close $namFile
    close $traceFile
    exec nam namOutput.nam &
    exit 0
}

#defining nodes
set node0 [$netSimInstance node]
set node1 [$netSimInstance node]

#settings the link between the two nodes. duplex link of 1mbps bw, 1ms delay, and a droptail queue
$netSimInstance duplex-link $node0 $node1 1Mb 10ms DropTail


#create a UDP agent to attach to node0
set UDPAgent0 [new Agent/UDP]
$netSimInstance attach-agent $node0 $UDPAgent0

#a constant bit rate traffic source is attached to the UDP client on node0
set CBRAgent0 [new Application/Traffic/CBR]
#setting the packet size of traffic to 500bytes
$CBRAgent0 set packetSize_ 500
#setting the interval between packets to 0.005seconds or 200packets/second
$CBRAgent0 set interval_ 0.005
#attaching traffic source to UDPAgent
$CBRAgent0 attach-agent $UDPAgent0

#create a sink at node1 to receive the packets being sent by node0
set nullSink0 [new Agent/Null]
$netSimInstance attach-agent $node1 $nullSink0

#create a connection between the two agents
$netSimInstance connect $UDPAgent0 $nullSink0

#setting the time of start and finish and the time for the agent to send data
$netSimInstance at 0.5 "$CBRAgent0 start"
$netSimInstance at 4.5 "$CBRAgent0 stop"
$netSimInstance at 5.0 "finish"
$netSimInstance run

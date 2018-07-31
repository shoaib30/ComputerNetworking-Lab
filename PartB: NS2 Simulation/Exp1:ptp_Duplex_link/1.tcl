set ns [new Simulator]
set nf [open exp1.nam w]
$ns namtrace-all $nf
set nd [open exp1.tr w]
set f0 [open xgphtrace.tr w]
$ns trace-all $nd

proc finish { } {
    global ns nf nd
    $ns flush-trace
    exec gawk -f 1.awk exp1.tr &
    close $nf
    close $nd
    exec nam exp1.nam &
    #exec xgraph xgphtrace.tr -geometry 800x400 &
    exit 0
}



set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 512Kb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns queue-limit $n1 $n2 10

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0
set sink [new Agent/LossMonitor]
$ns attach-agent $n2 $sink
$ns connect $udp0 $sink

proc record {} {
        global sink f0
        #Get an instance of the simulator
        set ns [Simulator instance]
        #Set the time after which the procedure should be called again
        set time 0.5
        #How many bytes have been received by the traffic sinks?
        set bw0 [$sink set bytes_]
        #Get the current time
        set now [$ns now]
        #Calculate the bandwidth (in MBit/s) and write it to the files
        puts $f0 "$now [expr $bw0/$time*8/1000000]"
        #Reset the bytes_ values on the traffic sinks
        $sink set bytes_ 0
        #Re-schedule the procedure
        $ns at [expr $now+$time] "record"
}
$ns at 0.0 "record"
$ns at 0.5 "$cbr0 start"
$ns at 9.5 "$cbr0 stop"
$ns at 10.0 "finish"
$ns run

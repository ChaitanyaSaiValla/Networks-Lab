set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red
$ns color 3 Green

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n3 10Mb 10ms DropTail
$ns duplex-link $n1 $n3 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 10Mb 10ms DropTail
$ns duplex-link $n3 $n4 10Mb 10ms DropTail

$ns duplex-link-op $n0 $n3 orient right-down
$ns duplex-link-op $n1 $n3 orient right
$ns duplex-link-op $n2 $n3 orient right-up
$ns duplex-link-op $n3 $n4 orient right

set udp0 [new Agent/UDP]
set udp1 [new Agent/UDP]
set udp2 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$ns attach-agent $n1 $udp1
$ns attach-agent $n2 $udp2


set null0 [new Agent/Null]
set null1 [new Agent/Null]
set null2 [new Agent/Null]
$ns attach-agent $n4 $null0
$ns attach-agent $n4 $null1
$ns attach-agent $n4 $null2

$ns connect $udp0 $null0
$ns connect $udp1 $null1
$ns connect $udp2 $null2

$udp0 set fid_ 1
$udp1 set fid_ 2
$udp2 set fid_ 3

set cbr0 [new Application/Traffic/CBR]
set cbr1 [new Application/Traffic/CBR]
set cbr2 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr1 attach-agent $udp1
$cbr2 attach-agent $udp2

$cbr0 set type_ CBR
$cbr1 set type_ CBR
$cbr2 set type_ CBR

$cbr0 set packetSize_ 5000
$cbr1 set packetSize_ 5000
$cbr2 set packetSize_ 5000

$ns at 0.0 "$cbr0 start"
$ns at 0.0 "$cbr1 start"
$ns at 0.0 "$cbr2 start"
$ns at 150.0 "$cbr0 stop"
$ns at 150.0 "$cbr1 stop"
$ns at 150.0 "$cbr2 stop"

$ns at 150.0 "finish"

$ns run
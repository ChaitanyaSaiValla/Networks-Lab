set ns [new Simulator]
set nr [open tr1.tr w]
$ns trace-all $nr
set nf [open nam1.nam w]
$ns namtrace-all $nf

proc finish { } {
    global ns nr nf
    $ns flush-trace
    close $nr
    close $nf
    exec nam nam1.nam &
    exec awk -f awk_file.awk tr1.tr &
    exit 0
}

for {set i 0} { $i < 10} {incr i} {
    set n($i) [$ns node]
}

for {set i 0} { $i < 9} {incr i} {
    $ns duplex-link $n($i) $n([expr $i + 1]) 1Mb 10ms DropTail
}

set udp0 [new Agent/TCP]
$ns attach-agent $n(0) $udp0

set cbr0 [new Application/FTP]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

set null0 [new Agent/TCPSink]
$ns attach-agent $n(5) $null0
$ns connect $udp0 $null0

set udp1 [new Agent/TCP]
$ns attach-agent $n(8) $udp1

set cbr1 [new Application/FTP]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
$cbr1 attach-agent $udp1

set null0 [new Agent/TCPSink]
$ns attach-agent $n(5) $null0
$ns connect $udp1 $null0

$ns rtproto LS
$ns rtmodel-at 10.0 down $n(4) $n(5) 
$ns rtmodel-at 30.0 down $n(7) $n(6)
$ns rtmodel-at 50.0 up $n(4) $n(5)
$ns rtmodel-at 75.0 up $n(7) $n(6)

$udp0 set fid_ 1
$udp1 set fid_ 2
$ns color 1 Red
$ns color 2 Green

$ns at 1.0 "$cbr0 start"
$ns at 2.0 "$cbr1 start"

$ns at 100 "finish"
$ns run

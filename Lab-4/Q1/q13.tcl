set ns [new Simulator]
set nf [open q1.nam w]
$ns namtrace-all $nf

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam q1.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n0 $n2 10Mb 10ms DropTail
$ns duplex-link $n1 $n3 10Mb 10ms DropTail
$ns duplex-link $n2 $n4 10Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient left-down
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n3 orient left-down
$ns duplex-link-op $n2 $n4 orient right-down

set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP
$ftp set packet_size_ 1000
$ftp set rate_ 1mb

$ns at 1.0 "$ftp start"
$ns at 2.0 "$ftp stop"

$ns at 5.0 "finish"

$ns run

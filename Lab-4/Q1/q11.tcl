set ns [new Simulator]
set nf [open q11.nam w]
$ns namtrace-all $nf

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam q11.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n2 10Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n3 $n2 10Mb 10ms SFQ
$ns duplex-link $n2 $n4 10Mb 10ms DropTail
$ns duplex-link-op $n0 $n2 orient down
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n3 $n2 orient left
$ns duplex-link-op $n2 $n4 orient down

set tcp0 [new Agent/TCP]
$tcp0 set fid_ 1
$tcp0 set window_ 8
$ns attach-agent $n0 $tcp0


set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp0 set type_ FTP
$ftp0 set packet_size_ 1000
$ftp0 set rate_ 1mb

set tcp1 [new Agent/TCP]
$tcp1 set fid_ 2
$tcp1 set window_ 8
$ns attach-agent $n1 $tcp1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP
$ftp1 set packet_size_ 1000
$ftp1 set rate_ 1mb

set s1 [new Agent/TCPSink]
set s2 [new Agent/TCPSink]
$ns attach-agent $n3 $s1
$ns attach-agent $n3 $s2

$ns connect $tcp0 $s1
$ns connect $tcp1 $s2

$ns at 0.5 "$ftp0 start"
$ns at 1.0 "$ftp1 start"
$ns at 4.0 "$ftp1 stop"
$ns at 4.5 "$ftp0 stop"
$ns at 5.0 "finish"

$ns run

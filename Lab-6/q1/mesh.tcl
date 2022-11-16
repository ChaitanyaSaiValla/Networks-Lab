set ns [new Simulator]

puts "Give N"
gets stdin N
puts "Give Packet Size"
gets stdin PS 
set ptf [open ptfout.dat w]
$ns trace-all $ptf

set nf [open nfout.nam w]
$ns namtrace-all $nf

set n(0) [$ns node]
$n(0) color white

for {set i 1} {$i <= $N} {incr i} {
    set n($i) [$ns node]
    $n($i) shape box
    $n($i) color green
}

set K [expr $N - 1]

for {set i 1} { $i <= $K } {incr i} {
    for {set j [expr $i + 1]} {$j <= $N} {incr j} {
        if {$i == $j} {continue}
        $ns duplex-link $n($i) $n($j) 5Mb 10ms DropTail
        $ns duplex-link-op $n($i) $n($j) color "blue"
    }
}

for {set i 1} { $i <= $N } {incr i} {
    if { [expr $i%2] == 0 } {continue}
    for {set j 1} { $j <= $N } {incr j} {
        if { [expr $j%2] == 1 } {continue}

        set udp($i,$j) [new Agent/UDP]
        $ns attach-agent $n($i) $udp($i,$j)
        set null($i,$j) [new Agent/Null]
        $ns attach-agent $n($j) $null($i,$j)
        $ns connect $udp($i,$j) $null($i,$j)

        set cbr($i,$j) [new Application/Traffic/CBR]
        $cbr($i,$j) set packetSize_ $PS
        $cbr($i,$j) set rate_ 1mb
        $cbr($i,$j) set interval 0.010
        $cbr($i,$j) attach-agent $udp($i,$j)

        $ns at 0.0 "$cbr($i,$j) start"
        $ns at 2.0 "$cbr($i,$j) stop"
    }
}

$ns at 2.0 "finish"
proc finish {} {
    global ns nf ptf
    $ns flush-trace 
    close $nf
    close $ptf
    exec nam nfout.nam &
    exit 0
}

$ns run
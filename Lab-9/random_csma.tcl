#This is the simulation of a network with MAC Protocol = slotted aloha.
set ns [new Simulator]

puts "Ente no of nodes : "

gets stdin no



#Tell the simulator to use dynamic routing
$ns rtproto DV
$ns macType MAC/Csma

#Open the nam trace file
set nf [open slotted_aloha.nam w]
$ns namtrace-all $nf

#Open the output files
set f0 [open slotted_aloha.tr w]
$ns trace-all $f0

#Define a finish procedure
proc finish {} {
  global ns f0 nf
  $ns flush-trace
  close $f0
  close $nf
  exec nam slotted_aloha.nam &
  exec awk -f cal.awk slotted_aloha.tr > ans &
  exit 0
}

for {set i 0} {$i < $no} {incr i} {
    set n($i) [$ns node]
    $n($i) shape box
    $n($i) color green
}

proc findRand { min max } {
	set randVar [ expr int(($max - $min)* rand() + $min) ]
	return $randVar
}
set k [expr $no - 1]
#Create duplex links between nodes with bandwidth and distance
for {set i 0} { $i < $k} {incr i} {
    set j [findRand 0 $k]
    if {$i == $j} {
    set i [expr $i - 1]
    continue
    }
    $ns duplex-link $n($i) $n($j) 1Mb 1ms DropTail
    #$ns duplex-link-op $n($i) $n($j) color "blue"
    $ns queue-limit $n($i) $n($j) 6
      
}

#$ns duplex-link-op $n4 $n5 queuePos 0.5

#Create a UDP agent and attach it to node n(0)
set udp0 [new Agent/TCP]
$ns attach-agent $n(0) $udp0

# Create a CBR traffic source and attach it to udp0
set ftp0 [new Application/FTP]
$ftp0 set packetSize_ 500
$ftp0 set interval_ 0.5
$ftp0 attach-agent $udp0

#Create a Null agent (a traffic sink) and attach it to node n(3)
set null0 [new Agent/TCPSink]
set des [findRand 0 $k]
$ns attach-agent $n($des) $null0

#Connect the traffic source with the traffic sink
$ns connect $udp0 $null0

#Schedule events for the CBR agent and the network dynamics
$ns at 0.5 "$ftp0 start"
#$ns rtmodel-at 1.0 down $n(5) $n(2)
#$ns rtmodel-at 2.0 up $n(5) $n(2)
$ns at 4.5 "$ftp0 stop"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Run the simulation
$ns run

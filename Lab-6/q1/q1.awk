BEGIN {
	thput = 0 
	simtime = 0
}
{
event = $1
time = $2 
intSrc = $3
intDest = $4
src = $9
dest = $10
size = $6

if(event == "r" && intDest == dest) {
thput += size
simtime = time
}

}
END {
thput = (thput*8)/(1000000*simtime)
printf("Throughtput = %g Mbps\n",thput)

}

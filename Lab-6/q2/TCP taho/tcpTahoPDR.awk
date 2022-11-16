
BEGIN {
	rsize = 0 ;
	lsize = 0;
	interval = 10 ;
	Time = 0 ;
	throughput =0;
	printf time "\t" throughtput "\n" 
}

{ 
	event = $1;
	time = $2;
	from = $3;
	to = $4 ;
	src = $9;
	dest = $10 ;

if(time-Time <= interval) {
if(event =="r") {
if(to == dest) {
rsize += 1 ;
}
}
else if(event =="d") {
dsize += 1 ;
}
}
else {
	throughtput = rsize/(rsize+dsize) ;

	printf time "\t" throughtput "\n"
	Time = Time + interval;
	rsize = 0;
	dsize = 0 ;
}
}


BEGIN {
	size = 0 ;
	interval = 10 ;
	Time = 0 ;
	throughput =0;
}

{ 
	event = $1;
	time = $2;
	from = $3;
	to = $4 ;
	src = $9;
	dest = $10 ;

if(time-Time <= interval) {
if(event !="r") {
size += time ;
}
}
else {
	throughtput = size/interval ;

	printf time "\t" throughtput "\n"
	Time = Time + interval;
	size = 0;
}
}

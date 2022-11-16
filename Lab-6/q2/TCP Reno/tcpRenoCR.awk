
BEGIN {
	size = 0 ;
	interval = 10 ;
	Time = 0 ;
	throughput =0;
}

{ 
	cnwd = $2;
	time = $1;

if(time-Time <= interval) {

size += cnwd ;

}
else {
	throughtput = size/interval ;

	printf time "\t" throughtput "\n"
	Time = Time + interval;
	size = 0;
}
}

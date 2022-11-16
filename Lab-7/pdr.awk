BEGIN {
    tot = 0
    rec = 0
    drop = 0
    time = 10
    pdr_ratio = 0
    routing_packets = 0
    plr_ratio = 0
}
{
    #2 is the receiving node
    if($1=="r" && $4==5)
    {
        rec++;
    }
    if($1=="d" && $4==5)
    {
        drop++;
    }
    if($2 > time)
    {
        tot = rec + drop
        pdr_ratio = 100*(rec/tot);
        plr_ratio = 100*(drop/tot);
        printf("total no of packents sent : %d\n",tot)
        printf("no of packets received : %d\n",rec)
        printf("no of packets dropped : %d\n",drop)
        printf("pdr ratio : %f\n",pdr_ratio)
        printf("plr ratio : %f\n",plr_ratio)
        printf("\n")
        time += 10;

        rec = 0;
        tot = 0;
        drop = 0;
    }
    if (($1 == "s" || $1 == "f") && ($4=="RTR") && ($7 == "message" || $7 == "DSDV" || $7 == "MDART" || $7 == "AOMDV" ||$7 =="REQUEST" || $7 =="REPLY"|| $7 == "AODV" ||
       $7 == "DSR" ||  $7 =="BEACON" || $7 =="FRIP" || $7 =="RSUP" || $7 =="ROUTE_REQ" || $7 =="ROUTE_REP"))
		routing_packets++;
}
END {
    tot = rec + drop
    pdr_ratio = 100*(rec/tot);
    plr_ratio = 100*(drop/tot);
    printf("total no of packents sent : %d\n",tot)
    printf("no of packets received : %d\n",rec)
    printf("no of packets dropped : %d\n",drop)
    printf("pdr ratio : %f\n",pdr_ratio)
    printf("plr ratio : %f\n",plr_ratio)
    printf("rounting overhead: %d\n", routing_packets)
    printf("\n")
}

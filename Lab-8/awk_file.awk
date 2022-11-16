BEGIN {
    tot = 0
    rec = 0
    drop = 0
    pdr_ratio = 0
    plr_ratio = 0
    time = 20
    cp = 0
    rcvsiz = 0
}
{
    #4,5 are the receiving nodes
    if($2>time)
    {
        pdr_ratio = 100*(rec/(rec+drop));
        plr_ratio = 100*(drop/(rec+drop));
        printf("total no of packents sent : %d\n",rec+drop)
        printf("no of packets received : %d\n",rec)
        printf("no of packets dropped : %d\n",drop)
        printf("pdr ratio : %f\n",pdr_ratio)
        printf("plr ratio : %f\n",plr_ratio)
        printf("control overhead : %f\n",(cp/tot))
        printf("energy consumption : %f\n",8*(rcvsiz)/100000)
        printf("\n\n")
        rec = 0
        drop = 0
        tot = 0
        time = time + 20
        cp = 0
        rcvsiz = 0
    }
    if($1=="r" && ($4==5))
    {
        rec++;
        rcvsiz += $6
    }
    if($1=="d" && ($4==5))
    {
        drop++;
    }
    if (($1 == "+")) {
		tot++;
		
		if (($5 == "ack"))
			cp++;
    }
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
    printf("control overhead : %f\n",(cp/tot))
    printf("energy consumption : %f\n",8*(rcvsiz)/100000)
    printf("\n")
}

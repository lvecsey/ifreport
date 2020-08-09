
*Introduction*

Retrieve the LAN speed and also the number of errors and dropped packets for the given interface.
Do this across an entire network or cluster and then report back in a pdf file.
Each host will use *ifconfig* and *ethtool* to collect information.

*Testing the ifreport command*

Just run

```console
ifreport eth0
```

replacing your interface name with the correct one.

*List of hosts*

You can fill out a *reportbody_in.csv* file which contains each hostname, followed by the ifreport command to run (via ssh). You can even run additional ifreport commands per hosts if you want information on multiple interfaces. The first line of the .csv file is a header line.

```
Host, Command
pluto, "~/src/ifreport/ifreport eth0"
jupiter, "~/src/ifreport/ifreport eth0"
```

You can also just place the binary to a location such as ~/bin/ifreport on each machine.

*Generating the body pulling bash script*

Run

```console
make csvhosts2sh
./csvhosts2sh < ./reportbody_in.csv > ./gen_reportbody.sh
chmod 755 ./gen_reportbody.sh
```

to generate a gen_reportbody.sh script.

*Generating the pdf*

```console
make output_ifreport.pdf
```

This uses the gen_reportbody.sh script to contact each host over ssh, run ifreport on the given machine(s), and then finally output the result with pdflatex.


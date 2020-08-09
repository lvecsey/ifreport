
CC=gcc

CFLAGS=-O3 -Wall -g -pg

all : ifreport

ifreport : ifreport.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

csvhosts2sh : csvhosts2sh.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

reportbody.tex : gen_reportbody.sh
	@./$^ > $@.new
	mv $@.new $@

output_ifreport.tex : ifreport_header.tex reportbody.tex ifreport_footer.tex
	cat $^ > $@.new
	mv $@.new $@

output_ifreport.pdf : output_ifreport.tex 
	@pdflatex $^


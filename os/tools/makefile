objects = uoko_tcpclient.o remotecmd.o
remotecmd: $(objects)
    cc -o remotecmd $(objects)
uoko_tcpclient.o: uoko_tcpclient.h
remotecmd.o:
.PHONY : clean
clean :
    @echo remove ...
    -rm remotecmd $(objects)
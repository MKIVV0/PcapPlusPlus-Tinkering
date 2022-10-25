include /usr/local/etc/PcapPlusPlus.mk

# All Target
all:
	g++	$(PCAPPP_INCLUDES)	-c	-o	exercise2.o	exercise2.cpp
	g++	$(PCAPPP_LIBS_DIR)	-static-libstdc++	-o	Main	exercise2.o	$(PCAPPP_LIBS)

# Clean Target
clean:
	rm exercise2.o
	xrm Main
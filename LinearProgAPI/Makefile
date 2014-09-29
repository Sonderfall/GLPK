PROJECT=PLNE
PROJECT_APP=LinearProgAPI
LEADER=macher_v
TARFILES=src resources lib AUTHORS doc README Makefile configure CMakeLists.txt
CURDIR='.'

.PHONY: all clean doc distclean dist ${PROJECT_APP} check

all:
	make -C ${CURDIR}/build/
	mv ${CURDIR/}build/${PROJECT_APP} ${CURDIR}

clean:
	rm -rf build

distclean: clean
	rm -rf doc/latex doc/html
	rm -f ${PROJECT_APP}
	rm -rf $(LEADER)-$(PROJECT).tar.bz2
	rm -rf $(LEADER)-$(PROJECT)

dist: distclean
	mkdir -p $(LEADER)-$(PROJECT)
	cp -R ${TARFILES} $(LEADER)-$(PROJECT)
	tar -cvjf $(LEADER)-$(PROJECT).tar.bz2 $(LEADER)-$(PROJECT)
	rm -rf $(LEADER)-$(PROJECT)
doc:
	doxygen doc/Doxyfile

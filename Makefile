.PHONY : all run plot clean

all ::
	mkdir -p build
	( cd build && cmake .. )
	$(MAKE) -C build

run :: all
	build/lansort

plot :: measurements.svg

measurements.svg : measurements.gp measurements.dat
	gnuplot measurements.gp

clean ::
	$(RM) -r build measurements.dat measurements.svg

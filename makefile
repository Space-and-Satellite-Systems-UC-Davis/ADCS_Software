CC := gcc
CFLAGS := -I. -lm -Wswitch

# Source files
SOURCES := determination/determination.c determination/IGRF_C/igrf.c determination/TRIAD/triad.c \
           determination/sun_lookup/sun_lookup.c adcs_math/vector.c adcs_math/matrix.c \
           determination/sun_lookup/spa.c determination/pos_lookup/pos_lookup.c \
           determination/pos_lookup/sgp4/src/c/SGP4.c determination/pos_lookup/sgp4/src/c/TLE.c \
           determination/novasc3.1/novas.c determination/novasc3.1/novascon.c \
           determination/novasc3.1/solsys1.c determination/novasc3.1/eph_manager.c \
           determination/novasc3.1/readeph0.c determination/pos_lookup/ECEF_to_geodetic.c \
           determination/novasc3.1/nutation.c

# Target executable name
TARGET := altitude_determination

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)


.PHONY: all clean

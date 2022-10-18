# Component Makefile
#
## These include paths would be exported to project level
COMPONENT_ADD_INCLUDEDIRS += include

## not be exported to project level
COMPONENT_PRIV_INCLUDEDIRS :=

## This component's src


COMPONENT_SRCDIRS := driver \
					 cista_c2399 \
					 cista_c2490 \
					 cista_c2496 \
					 galaxycore_gc1054 \
					 galaxycore_gc2053 \
					 galaxycore_gc2093 \
					 galaxycore_gc0308 \
					 galaxycore_gc0328 \
					 omnivision_ov9732 \
					 omnivision_ov2685 \
					 smartsens_sc1245 \
					 smartsens_sc2232 \
					 smartsens_sc2336 \
					 opnous_opnm8508pa \
					 byd_bf2013

COMPONENT_ADD_LDFLAGS_HEAD := -Wl,--whole-archive
COMPONENT_ADD_LDFLAGS_TAIL := -Wl,--no-whole-archive




##
#CPPFLAGS +=

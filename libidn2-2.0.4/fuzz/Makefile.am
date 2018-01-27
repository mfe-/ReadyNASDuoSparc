AM_CFLAGS = $(WERROR_CFLAGS) $(WARN_CFLAGS) -Wno-vla
AM_CPPFLAGS = -I$(top_srcdir)/lib -I../lib -I$(top_srcdir)/gl -I../gl -DSRCDIR=\"$(abs_srcdir)\" -DTEST_RUN
AM_LDFLAGS = -no-install

LDADD = ../lib/libidn2.la ../gl/libgnu.la

IDN_TESTS = \
 libidn2_to_ascii_8z_fuzzer$(EXEEXT) \
 libidn2_to_unicode_8z8z_fuzzer$(EXEEXT)

check_PROGRAMS = $(IDN_TESTS)

libidn2_to_ascii_8z_fuzzer_SOURCES = libidn2_to_ascii_8z_fuzzer.c main.c fuzzer.h
libidn2_to_unicode_8z8z_fuzzer_SOURCES = libidn2_to_unicode_8z8z_fuzzer.c main.c fuzzer.h

dist-hook:
	find . -name '*.options' -exec cp -v '{}' $(distdir) ';'
	find . -name '*.dict' -exec cp -v '{}' $(distdir) ';'
	find . -name '*.in' -exec cp -vr '{}' $(distdir) ';'
	find . -name '*.repro' -exec cp -vr '{}' $(distdir) ';'

TESTS = $(IDN_TESTS)

clean-local:
	rm -rf *.gc?? *.log lcov *_fuzzer coverage.info *.o

oss-fuzz:
	if test "$$OUT" != ""; then \
	for ccfile in *_fuzzer.c; do \
	fuzzer=$$(basename $$ccfile .c); \
	$$CXX $$CXXFLAGS -I$(top_srcdir)/lib -I$(top_srcdir) \
	"$${fuzzer}.c" -o "$${fuzzer}" \
	../lib/.libs/libidn2.a $${LIB_FUZZING_ENGINE} -Wl,-Bstatic \
	-Wl,-Bdynamic; \
	done; \
	fi

.PHONY: oss-fuzz

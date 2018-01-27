# Copyright (C) 2011-2017 Simon Josefsson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DISTCHECK_CONFIGURE_FLAGS ?= --enable-gtk-doc --disable-gcc-warnings

SUBDIRS =

if !HAVE_LIBUNISTRING
SUBDIRS += unistring
endif

SUBDIRS += gl lib src examples tests fuzz po
ACLOCAL_AMFLAGS = -I m4 -I unistring/m4
EXTRA_DIST = m4/gnulib-cache.m4

if ENABLE_DOC
SUBDIRS += doc
endif

EXTRA_DIST += cfg.mk maint.mk CONTRIBUTING.md README.md COPYING COPYING.LESSERv3 \
	COPYING.unicode COPYINGv2 AUTHORS NEWS ChangeLog INSTALL

check-valgrind:
	TESTS_ENVIRONMENT="valgrind --error-exitcode=301 --leak-check=yes --show-reachable=yes --track-origins=yes" $(MAKE) check

clean-local:
	rm -rf */*.gc?? */*/*.gc??

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libidn2.pc

@CODE_COVERAGE_RULES@

local-code-coverage-output: code-coverage-capture
	@cat libidn2-$(VERSION)-coverage/index.html|grep headerCovTableEntryHi|head -1|sed 's/^.*>\([0-9]\+\.[0-9]\+\s*%\)<.*$$/ coverage lines: \1/' || true

ABI_TMPDIR="headers.abi.tmp"
ABI_TMPFILE="abi-temp.xml"
abi-check: lib/idn2.h lib/libidn2.la
	@rm -f $(ABI_TMPFILE)
	@echo "Checking libidn2 ABI"
	@echo "<version>$(VERSION)</version>" >$(ABI_TMPFILE)
	@echo "<headers>$(srcdir)/lib/idn2.h" >>$(ABI_TMPFILE)
	@echo "$(builddir)/lib/idn2.h</headers>" >>$(ABI_TMPFILE)
	@echo "<libs>$(builddir)/lib/.libs</libs>" >>$(ABI_TMPFILE)
	for i in 2.0.2; do \
	  test ! -f "$(srcdir)/devel/ABI-$$i-$$(uname -m).dump" || \
	  abi-compliance-checker --v1=2.0.2 -abi -lib libidn2 -old "$(srcdir)/devel/ABI-$$i-$$(uname -m).dump" -new $(ABI_TMPFILE); \
	done
	@rm -f $(ABI_TMPFILE)

abi-dump: lib/idn2.h lib/libidn2.la
	@rm -rf $(ABI_TMPDIR)
	@mkdir -p $(ABI_TMPDIR)
	@mkdir -p devel
	@cp lib/idn2.h $(ABI_TMPDIR)
	@abi-dumper lib/.libs/libidn2.so -o "./devel/ABI-$(VERSION)-$$(uname -m).dump" -public-headers $(ABI_TMPDIR)
	@rm -rf $(ABI_TMPDIR)

dist-hook: abi-check
	rm -f ChangeLog
	make ChangeLog

.PHONY: abi-dump abi-check

LCOV_INFO=libidn2.info
fuzz-coverage: clean
	$(MAKE) -C gl CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	$(MAKE) -C unistring CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	$(MAKE) -C lib CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	$(MAKE) -C fuzz check CFLAGS="$(CFLAGS) --coverage" LDFLAGS="$(LDFLAGS) --coverage"
	lcov --capture --initial --directory lib --directory fuzz --output-file $(LCOV_INFO)
	lcov --capture --directory lib --directory fuzz --output-file $(LCOV_INFO)
#	lcov --remove $(LCOV_INFO) '*/test_linking.c' '*/css_tokenizer.lex' '*/<stdout>' -o $(LCOV_INFO)
	genhtml --prefix . --ignore-errors source $(LCOV_INFO) --legend --title "fuzz coverage" --output-directory=lcov
	@echo
	@echo "You can now view the coverage report with 'xdg-open lcov/index.html'"

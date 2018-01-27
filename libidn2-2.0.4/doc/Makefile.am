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

SUBDIRS = reference

EXTRA_DIST = gdoc libidn2.html libidn2.pdf texinfo.css idn2.md
BUILT_SOURCES = idn2.1
info_TEXINFOS = libidn2.texi
libidn2_TEXINFOS = libidn2.texi example-tounicode.c example-toascii.c decode.c lookup.c register.c $(gdoc_TEXINFOS)

AM_MAKEINFOHTMLFLAGS = $(AM_MAKEINFOFLAGS) \
	--no-split --number-sections --css-include=texinfo.css

decode.c: $(top_srcdir)/examples/decode.c
	tail -n +18 $< > $@.tmp
	mv $@.tmp $@

lookup.c: $(top_srcdir)/examples/lookup.c
	tail -n +18 $< > $@.tmp
	mv $@.tmp $@

register.c: $(top_srcdir)/examples/register.c
	tail -n +18 $< > $@.tmp
	mv $@.tmp $@

example-tounicode.c: $(top_srcdir)/examples/example-tounicode.c
	cp $< $@

example-toascii.c: $(top_srcdir)/examples/example-toascii.c
	cp $< $@

dist_man_MANS = $(gdoc_MANS)
dist_man_MANS += idn2.1

idn2.1: idn2.md
	ronn -r $^ >$@

CLEANFILES = $(dist_man_MANS) decode.c example-tounicode.c example-toascii.c lookup.c \
	register.c stamp-vti version.texi $(srcdir)/libidn2.info

# GDOC

GDOC_SRC = $(top_srcdir)/lib/decode.c $(top_srcdir)/lib/lookup.c $(top_srcdir)/lib/register.c \
	$(top_srcdir)/lib/error.c $(top_srcdir)/lib/version.c $(top_srcdir)/lib/free.c
GDOC_TEXI_PREFIX = texi/
GDOC_MAN_PREFIX = man/
GDOC_MAN_EXTRA_ARGS = -module $(PACKAGE) -sourceversion $(VERSION) \
	-includefuncprefix -seeinfo $(PACKAGE)
include $(srcdir)/Makefile.gdoci

clean-local:
	rm -rf man texi manual

manual:
	../build-aux/gendocs.sh --html --css-include=texinfo.css -o manual $(PACKAGE) "$(PACKAGE_NAME)"

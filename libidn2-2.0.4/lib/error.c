/* error.c - libidn2 error handling helpers.
   Copyright (C) 2011-2017 Simon Josefsson

   Libidn2 is free software: you can redistribute it and/or modify it
   under the terms of either:

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version.

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version.

   or both in parallel, as here.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>

#include "idn2.h"

/* Prepare for gettext. */
#define _(x) x
#define bindtextdomain(a,b)

/**
 * idn2_strerror:
 * @rc: return code from another libidn2 function.
 *
 * Convert internal libidn2 error code to a humanly readable string.
 * The returned pointer must not be de-allocated by the caller.
 *
 * Return value: A humanly readable string describing error.
 **/
const char *
idn2_strerror (int rc)
{
  const char *p;

  bindtextdomain (PACKAGE, LOCALEDIR);

  switch (rc)
    {
    case IDN2_OK:
      p = _("success");
      break;

    case IDN2_MALLOC:
      p = _("out of memory");
      break;

    case IDN2_NO_CODESET:
      p = _("could not determine locale encoding format");
      break;

    case IDN2_ICONV_FAIL:
      p = _("could not convert string to UTF-8");
      break;

    case IDN2_ENCODING_ERROR:
      p = _("string encoding error");
      break;

    case IDN2_NFC:
      p = _("string could not be NFC normalized");
      break;

    case IDN2_PUNYCODE_BAD_INPUT:
      p = _("string contains invalid punycode data");
      break;

    case IDN2_PUNYCODE_BIG_OUTPUT:
      p = _("punycode encoded data will be too large");
      break;

    case IDN2_PUNYCODE_OVERFLOW:
      p = _("punycode conversion resulted in overflow");
      break;

    case IDN2_TOO_BIG_DOMAIN:
      p = _("domain name longer than 255 characters");
      break;

    case IDN2_TOO_BIG_LABEL:
      p = _("domain label longer than 63 characters");
      break;

    case IDN2_INVALID_ALABEL:
      p = _("input A-label is not valid");
      break;

    case IDN2_UALABEL_MISMATCH:
      p = _("input A-label and U-label does not match");
      break;

    case IDN2_NOT_NFC:
      p = _("string is not in Unicode NFC format");
      break;

    case IDN2_2HYPHEN:
      p = _("string contains forbidden two hyphens pattern");
      break;

    case IDN2_HYPHEN_STARTEND:
      p = _("string start/ends with forbidden hyphen");
      break;

    case IDN2_LEADING_COMBINING:
      p = _("string contains a forbidden leading combining character");
      break;

    case IDN2_DISALLOWED:
      p = _("string contains a disallowed character");
      break;

    case IDN2_CONTEXTJ:
      p = _("string contains a forbidden context-j character");
      break;

    case IDN2_CONTEXTJ_NO_RULE:
      p = _("string contains a context-j character with null rule");
      break;

    case IDN2_CONTEXTO:
      p = _("string contains a forbidden context-o character");
      break;

    case IDN2_CONTEXTO_NO_RULE:
      p = _("string contains a context-o character with null rule");
      break;

    case IDN2_UNASSIGNED:
      p = _("string contains unassigned code point");
      break;

    case IDN2_BIDI:
      p = _("string has forbidden bi-directional properties");
      break;

    default:
      p = _("Unknown error");
      break;
    }

  return p;
}

#define ERR2STR(name) #name

/**
 * idn2_strerror_name:
 * @rc: return code from another libidn2 function.
 *
 * Convert internal libidn2 error code to a string corresponding to
 * internal header file symbols.  For example,
 * idn2_strerror_name(IDN2_MALLOC) will return the string
 * "IDN2_MALLOC".
 *
 * The caller must not attempt to de-allocate the returned string.
 *
 * Return value: A string corresponding to error code symbol.
 **/
const char *
idn2_strerror_name (int rc)
{
  const char *p;

  switch (rc)
    {
    case IDN2_OK:
      p = ERR2STR (IDN2_OK);
      break;

    case IDN2_MALLOC:
      p = ERR2STR (IDN2_MALLOC);
      break;

    case IDN2_NO_CODESET:
      p = ERR2STR (IDN2_NO_NODESET);
      break;

    case IDN2_ICONV_FAIL:
      p = ERR2STR (IDN2_ICONV_FAIL);
      break;

    case IDN2_ENCODING_ERROR:
      p = ERR2STR (IDN2_ENCODING_ERROR);
      break;

    case IDN2_NFC:
      p = ERR2STR (IDN2_NFC);
      break;

    case IDN2_PUNYCODE_BAD_INPUT:
      p = ERR2STR (IDN2_PUNYCODE_BAD_INPUT);
      break;

    case IDN2_PUNYCODE_BIG_OUTPUT:
      p = ERR2STR (IDN2_PUNYCODE_BIG_OUTPUT);
      break;

    case IDN2_PUNYCODE_OVERFLOW:
      p = ERR2STR (IDN2_PUNYCODE_OVERFLOW);
      break;

    case IDN2_TOO_BIG_DOMAIN:
      p = ERR2STR (IDN2_TOO_BIG_DOMAIN);
      break;

    case IDN2_TOO_BIG_LABEL:
      p = ERR2STR (IDN2_TOO_BIG_LABEL);
      break;

    case IDN2_INVALID_ALABEL:
      p = ERR2STR (IDN2_INVALID_ALABEL);
      break;

    case IDN2_UALABEL_MISMATCH:
      p = ERR2STR (IDN2_UALABEL_MISMATCH);
      break;

    case IDN2_NOT_NFC:
      p = ERR2STR (IDN2_NOT_NFC);
      break;

    case IDN2_2HYPHEN:
      p = ERR2STR (IDN2_2HYPHEN);
      break;

    case IDN2_HYPHEN_STARTEND:
      p = ERR2STR (IDN2_HYPHEN_STARTEND);
      break;

    case IDN2_LEADING_COMBINING:
      p = ERR2STR (IDN2_LEADING_COMBINING);
      break;

    case IDN2_DISALLOWED:
      p = ERR2STR (IDN2_DISALLOWED);
      break;

    case IDN2_CONTEXTJ:
      p = ERR2STR (IDN2_CONTEXTJ);
      break;

    case IDN2_CONTEXTJ_NO_RULE:
      p = ERR2STR (IDN2_CONTEXTJ_NO_RULE);
      break;

    case IDN2_CONTEXTO:
      p = ERR2STR (IDN2_CONTEXTO);
      break;

    case IDN2_CONTEXTO_NO_RULE:
      p = ERR2STR (IDN2_CONTEXTO_NO_RULE);
      break;

    case IDN2_UNASSIGNED:
      p = ERR2STR (IDN2_UNASSIGNED);
      break;

    case IDN2_BIDI:
      p = ERR2STR (IDN2_BIDI);
      break;

    default:
      p = "IDN2_UNKNOWN";
      break;
    }

  return p;
}

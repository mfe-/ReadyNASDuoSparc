/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf -m 10 ./unictype/scripts_byname.gperf  */
/* Computed positions: -k'1,3,5,8' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 4 "./unictype/scripts_byname.gperf"
struct named_script { int name; unsigned int index; };

#define TOTAL_KEYWORDS 131
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 22
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 199
/* maximum key range = 196, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
scripts_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200,   5,   2,  19,  31,  12,
      200,  24,  46,   4,  51,  42,   7,   4,   2,  16,
       35, 200,  71,  16,  10,  32,  51,  30, 200,   2,
      200, 200, 200, 200, 200,  34, 200,   5,  57,  50,
       64,  12,  44,  18,  36,   9,  19,  40,  31,   4,
        2,   2,  75, 200,   9,  73,  38,  33,  41,  10,
      200,  24, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
      200, 200, 200, 200, 200, 200
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
      case 6:
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

struct script_stringpool_t
  {
    char script_stringpool_str4[sizeof("Yi")];
    char script_stringpool_str7[sizeof("Nko")];
    char script_stringpool_str9[sizeof("Mro")];
    char script_stringpool_str11[sizeof("Ahom")];
    char script_stringpool_str12[sizeof("Lao")];
    char script_stringpool_str13[sizeof("Miao")];
    char script_stringpool_str15[sizeof("Bamum")];
    char script_stringpool_str16[sizeof("Bengali")];
    char script_stringpool_str17[sizeof("Brahmi")];
    char script_stringpool_str18[sizeof("Mandaic")];
    char script_stringpool_str19[sizeof("Thai")];
    char script_stringpool_str20[sizeof("Myanmar")];
    char script_stringpool_str21[sizeof("Armenian")];
    char script_stringpool_str22[sizeof("Mongolian")];
    char script_stringpool_str23[sizeof("Thaana")];
    char script_stringpool_str24[sizeof("Linear_B")];
    char script_stringpool_str25[sizeof("Arabic")];
    char script_stringpool_str27[sizeof("Linear_A")];
    char script_stringpool_str28[sizeof("Cham")];
    char script_stringpool_str29[sizeof("Osmanya")];
    char script_stringpool_str30[sizeof("Sinhala")];
    char script_stringpool_str31[sizeof("Common")];
    char script_stringpool_str32[sizeof("Tai_Le")];
    char script_stringpool_str33[sizeof("Sharada")];
    char script_stringpool_str34[sizeof("Chakma")];
    char script_stringpool_str35[sizeof("Oriya")];
    char script_stringpool_str36[sizeof("Syriac")];
    char script_stringpool_str37[sizeof("Shavian")];
    char script_stringpool_str38[sizeof("Anatolian_Hieroglyphs")];
    char script_stringpool_str39[sizeof("Carian")];
    char script_stringpool_str40[sizeof("Mende_Kikakui")];
    char script_stringpool_str41[sizeof("Tai_Tham")];
    char script_stringpool_str42[sizeof("Buginese")];
    char script_stringpool_str43[sizeof("Samaritan")];
    char script_stringpool_str44[sizeof("Meetei_Mayek")];
    char script_stringpool_str45[sizeof("Braille")];
    char script_stringpool_str46[sizeof("Tagbanwa")];
    char script_stringpool_str47[sizeof("Multani")];
    char script_stringpool_str48[sizeof("Cuneiform")];
    char script_stringpool_str49[sizeof("Limbu")];
    char script_stringpool_str50[sizeof("Tamil")];
    char script_stringpool_str51[sizeof("Han")];
    char script_stringpool_str52[sizeof("Latin")];
    char script_stringpool_str53[sizeof("Cherokee")];
    char script_stringpool_str54[sizeof("Georgian")];
    char script_stringpool_str55[sizeof("Balinese")];
    char script_stringpool_str56[sizeof("Kannada")];
    char script_stringpool_str57[sizeof("Hanunoo")];
    char script_stringpool_str58[sizeof("Phoenician")];
    char script_stringpool_str59[sizeof("Tirhuta")];
    char script_stringpool_str60[sizeof("Khmer")];
    char script_stringpool_str61[sizeof("Ogham")];
    char script_stringpool_str62[sizeof("Avestan")];
    char script_stringpool_str63[sizeof("Vai")];
    char script_stringpool_str64[sizeof("Takri")];
    char script_stringpool_str65[sizeof("Telugu")];
    char script_stringpool_str66[sizeof("Tagalog")];
    char script_stringpool_str67[sizeof("New_Tai_Lue")];
    char script_stringpool_str68[sizeof("Lycian")];
    char script_stringpool_str69[sizeof("Gujarati")];
    char script_stringpool_str70[sizeof("Inherited")];
    char script_stringpool_str71[sizeof("Warang_Citi")];
    char script_stringpool_str72[sizeof("Modi")];
    char script_stringpool_str73[sizeof("Malayalam")];
    char script_stringpool_str74[sizeof("Grantha")];
    char script_stringpool_str75[sizeof("Sora_Sompeng")];
    char script_stringpool_str76[sizeof("Mahajani")];
    char script_stringpool_str77[sizeof("Gothic")];
    char script_stringpool_str78[sizeof("Manichaean")];
    char script_stringpool_str79[sizeof("Glagolitic")];
    char script_stringpool_str80[sizeof("Caucasian_Albanian")];
    char script_stringpool_str81[sizeof("Greek")];
    char script_stringpool_str82[sizeof("Lydian")];
    char script_stringpool_str83[sizeof("Gurmukhi")];
    char script_stringpool_str84[sizeof("Lisu")];
    char script_stringpool_str85[sizeof("Batak")];
    char script_stringpool_str86[sizeof("Hiragana")];
    char script_stringpool_str87[sizeof("Hangul")];
    char script_stringpool_str88[sizeof("Meroitic_Cursive")];
    char script_stringpool_str89[sizeof("Devanagari")];
    char script_stringpool_str90[sizeof("Khojki")];
    char script_stringpool_str91[sizeof("Bopomofo")];
    char script_stringpool_str92[sizeof("Meroitic_Hieroglyphs")];
    char script_stringpool_str93[sizeof("Kaithi")];
    char script_stringpool_str94[sizeof("Bassa_Vah")];
    char script_stringpool_str95[sizeof("Hatran")];
    char script_stringpool_str96[sizeof("Egyptian_Hieroglyphs")];
    char script_stringpool_str97[sizeof("Kharoshthi")];
    char script_stringpool_str98[sizeof("Rejang")];
    char script_stringpool_str99[sizeof("Syloti_Nagri")];
    char script_stringpool_str100[sizeof("Tifinagh")];
    char script_stringpool_str101[sizeof("Palmyrene")];
    char script_stringpool_str102[sizeof("Saurashtra")];
    char script_stringpool_str103[sizeof("Ol_Chiki")];
    char script_stringpool_str104[sizeof("Ugaritic")];
    char script_stringpool_str105[sizeof("Sundanese")];
    char script_stringpool_str106[sizeof("Canadian_Aboriginal")];
    char script_stringpool_str107[sizeof("Buhid")];
    char script_stringpool_str108[sizeof("Ethiopic")];
    char script_stringpool_str109[sizeof("Coptic")];
    char script_stringpool_str110[sizeof("Cypriot")];
    char script_stringpool_str111[sizeof("Nabataean")];
    char script_stringpool_str112[sizeof("Tibetan")];
    char script_stringpool_str113[sizeof("SignWriting")];
    char script_stringpool_str114[sizeof("Javanese")];
    char script_stringpool_str116[sizeof("Tai_Viet")];
    char script_stringpool_str117[sizeof("Cyrillic")];
    char script_stringpool_str118[sizeof("Duployan")];
    char script_stringpool_str119[sizeof("Kayah_Li")];
    char script_stringpool_str120[sizeof("Deseret")];
    char script_stringpool_str121[sizeof("Hebrew")];
    char script_stringpool_str123[sizeof("Siddham")];
    char script_stringpool_str124[sizeof("Lepcha")];
    char script_stringpool_str125[sizeof("Old_Italic")];
    char script_stringpool_str126[sizeof("Phags_Pa")];
    char script_stringpool_str127[sizeof("Psalter_Pahlavi")];
    char script_stringpool_str128[sizeof("Runic")];
    char script_stringpool_str129[sizeof("Old_Permic")];
    char script_stringpool_str132[sizeof("Pau_Cin_Hau")];
    char script_stringpool_str133[sizeof("Katakana")];
    char script_stringpool_str135[sizeof("Imperial_Aramaic")];
    char script_stringpool_str137[sizeof("Old_North_Arabian")];
    char script_stringpool_str139[sizeof("Pahawh_Hmong")];
    char script_stringpool_str140[sizeof("Old_Turkic")];
    char script_stringpool_str145[sizeof("Inscriptional_Pahlavi")];
    char script_stringpool_str146[sizeof("Inscriptional_Parthian")];
    char script_stringpool_str149[sizeof("Elbasan")];
    char script_stringpool_str151[sizeof("Old_South_Arabian")];
    char script_stringpool_str153[sizeof("Khudawadi")];
    char script_stringpool_str157[sizeof("Old_Hungarian")];
    char script_stringpool_str199[sizeof("Old_Persian")];
  };
static const struct script_stringpool_t script_stringpool_contents =
  {
    "Yi",
    "Nko",
    "Mro",
    "Ahom",
    "Lao",
    "Miao",
    "Bamum",
    "Bengali",
    "Brahmi",
    "Mandaic",
    "Thai",
    "Myanmar",
    "Armenian",
    "Mongolian",
    "Thaana",
    "Linear_B",
    "Arabic",
    "Linear_A",
    "Cham",
    "Osmanya",
    "Sinhala",
    "Common",
    "Tai_Le",
    "Sharada",
    "Chakma",
    "Oriya",
    "Syriac",
    "Shavian",
    "Anatolian_Hieroglyphs",
    "Carian",
    "Mende_Kikakui",
    "Tai_Tham",
    "Buginese",
    "Samaritan",
    "Meetei_Mayek",
    "Braille",
    "Tagbanwa",
    "Multani",
    "Cuneiform",
    "Limbu",
    "Tamil",
    "Han",
    "Latin",
    "Cherokee",
    "Georgian",
    "Balinese",
    "Kannada",
    "Hanunoo",
    "Phoenician",
    "Tirhuta",
    "Khmer",
    "Ogham",
    "Avestan",
    "Vai",
    "Takri",
    "Telugu",
    "Tagalog",
    "New_Tai_Lue",
    "Lycian",
    "Gujarati",
    "Inherited",
    "Warang_Citi",
    "Modi",
    "Malayalam",
    "Grantha",
    "Sora_Sompeng",
    "Mahajani",
    "Gothic",
    "Manichaean",
    "Glagolitic",
    "Caucasian_Albanian",
    "Greek",
    "Lydian",
    "Gurmukhi",
    "Lisu",
    "Batak",
    "Hiragana",
    "Hangul",
    "Meroitic_Cursive",
    "Devanagari",
    "Khojki",
    "Bopomofo",
    "Meroitic_Hieroglyphs",
    "Kaithi",
    "Bassa_Vah",
    "Hatran",
    "Egyptian_Hieroglyphs",
    "Kharoshthi",
    "Rejang",
    "Syloti_Nagri",
    "Tifinagh",
    "Palmyrene",
    "Saurashtra",
    "Ol_Chiki",
    "Ugaritic",
    "Sundanese",
    "Canadian_Aboriginal",
    "Buhid",
    "Ethiopic",
    "Coptic",
    "Cypriot",
    "Nabataean",
    "Tibetan",
    "SignWriting",
    "Javanese",
    "Tai_Viet",
    "Cyrillic",
    "Duployan",
    "Kayah_Li",
    "Deseret",
    "Hebrew",
    "Siddham",
    "Lepcha",
    "Old_Italic",
    "Phags_Pa",
    "Psalter_Pahlavi",
    "Runic",
    "Old_Permic",
    "Pau_Cin_Hau",
    "Katakana",
    "Imperial_Aramaic",
    "Old_North_Arabian",
    "Pahawh_Hmong",
    "Old_Turkic",
    "Inscriptional_Pahlavi",
    "Inscriptional_Parthian",
    "Elbasan",
    "Old_South_Arabian",
    "Khudawadi",
    "Old_Hungarian",
    "Old_Persian"
  };
#define script_stringpool ((const char *) &script_stringpool_contents)

static const struct named_script script_names[] =
  {
    {-1}, {-1}, {-1}, {-1},
#line 51 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str4, 36},
    {-1}, {-1},
#line 80 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str7, 65},
    {-1},
#line 129 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str9, 114},
    {-1},
#line 140 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str11, 125},
#line 35 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str12, 20},
#line 113 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str13, 98},
    {-1},
#line 98 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str15, 83},
#line 25 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str16, 10},
#line 108 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str17, 93},
#line 109 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str18, 94},
#line 34 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str19, 19},
#line 37 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str20, 22},
#line 19 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str21, 4},
#line 46 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str22, 31},
#line 23 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str23, 8},
#line 62 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str24, 47},
#line 21 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str25, 6},
    {-1},
#line 124 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str27, 109},
#line 91 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str28, 76},
#line 65 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str29, 50},
#line 33 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str30, 18},
#line 15 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str31, 0},
#line 61 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str32, 46},
#line 114 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str33, 99},
#line 110 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str34, 95},
#line 28 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str35, 13},
#line 22 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str36, 7},
#line 64 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str37, 49},
#line 141 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str38, 126},
#line 89 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str39, 74},
#line 127 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str40, 112},
#line 92 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str41, 77},
#line 68 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str42, 53},
#line 96 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str43, 81},
#line 100 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str44, 85},
#line 67 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str45, 52},
#line 59 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str46, 44},
#line 143 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str47, 128},
#line 77 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str48, 62},
#line 60 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str49, 45},
#line 29 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str50, 14},
#line 50 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str51, 35},
#line 16 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str52, 1},
#line 41 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str53, 26},
#line 38 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str54, 23},
#line 76 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str55, 61},
#line 31 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str56, 16},
#line 57 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str57, 42},
#line 78 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str58, 63},
#line 138 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str59, 123},
#line 45 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str60, 30},
#line 43 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str61, 28},
#line 94 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str62, 79},
#line 84 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str63, 69},
#line 116 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str64, 101},
#line 30 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str65, 15},
#line 56 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str66, 41},
#line 70 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str67, 55},
#line 88 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str68, 73},
#line 27 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str69, 12},
#line 55 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str70, 40},
#line 139 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str71, 124},
#line 128 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str72, 113},
#line 32 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str73, 17},
#line 121 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str74, 106},
#line 115 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str75, 100},
#line 125 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str76, 110},
#line 53 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str77, 38},
#line 126 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str78, 111},
#line 71 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str79, 56},
#line 117 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str80, 102},
#line 17 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str81, 2},
#line 90 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str82, 75},
#line 26 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str83, 11},
#line 97 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str84, 82},
#line 107 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str85, 92},
#line 47 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str86, 32},
#line 39 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str87, 24},
#line 111 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str88, 96},
#line 24 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str89, 9},
#line 123 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str90, 108},
#line 49 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str91, 34},
#line 112 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str92, 97},
#line 106 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str93, 91},
#line 118 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str94, 103},
#line 142 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str95, 127},
#line 95 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str96, 80},
#line 75 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str97, 60},
#line 87 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str98, 72},
#line 73 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str99, 58},
#line 72 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str100, 57},
#line 132 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str101, 117},
#line 85 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str102, 70},
#line 83 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str103, 68},
#line 63 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str104, 48},
#line 81 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str105, 66},
#line 42 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str106, 27},
#line 58 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str107, 43},
#line 40 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str108, 25},
#line 69 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str109, 54},
#line 66 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str110, 51},
#line 131 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str111, 116},
#line 36 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str112, 21},
#line 145 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str113, 130},
#line 99 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str114, 84},
    {-1},
#line 93 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str116, 78},
#line 18 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str117, 3},
#line 119 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str118, 104},
#line 86 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str119, 71},
#line 54 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str120, 39},
#line 20 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str121, 5},
    {-1},
#line 136 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str123, 121},
#line 82 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str124, 67},
#line 52 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str125, 37},
#line 79 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str126, 64},
#line 135 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str127, 120},
#line 44 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str128, 29},
#line 134 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str129, 119},
    {-1}, {-1},
#line 133 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str132, 118},
#line 48 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str133, 33},
    {-1},
#line 101 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str135, 86},
    {-1},
#line 130 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str137, 115},
    {-1},
#line 122 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str139, 107},
#line 105 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str140, 90},
    {-1}, {-1}, {-1}, {-1},
#line 104 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str145, 89},
#line 103 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str146, 88},
    {-1}, {-1},
#line 120 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str149, 105},
    {-1},
#line 102 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str151, 87},
    {-1},
#line 137 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str153, 122},
    {-1}, {-1}, {-1},
#line 144 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str157, 129},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
    {-1}, {-1}, {-1}, {-1}, {-1},
#line 74 "./unictype/scripts_byname.gperf"
    {(int)(long)&((struct script_stringpool_t *)0)->script_stringpool_str199, 59}
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct named_script *
uc_script_lookup (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = scripts_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = script_names[key].name;
          if (o >= 0)
            {
              register const char *s = o + script_stringpool;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &script_names[key];
            }
        }
    }
  return 0;
}

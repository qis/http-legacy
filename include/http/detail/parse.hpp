/* Generated by re2c 1.0.1 on Wed Nov  6 15:51:49 2019 */
#line 1 "parse.hpp.re"
// Compile this file with re2c version >= 0.16:
//
//   re2c -o parse.hpp parse.hpp.re
//

#pragma once
#include <http/types.hpp>
#include <string>

namespace http {
namespace detail {

inline header parse_header(const std::string& name) {
  const char* YYCURSOR = name.data();
  const char* YYMARKER = YYCURSOR;

  
#line 21 "parse.hpp"
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy4;
	case 'C':
	case 'c':	goto yy5;
	case 'D':
	case 'd':	goto yy6;
	case 'E':
	case 'e':	goto yy7;
	case 'H':
	case 'h':	goto yy8;
	case 'I':
	case 'i':	goto yy9;
	case 'L':
	case 'l':	goto yy10;
	case 'O':
	case 'o':	goto yy11;
	case 'P':
	case 'p':	goto yy12;
	case 'R':
	case 'r':	goto yy13;
	case 'S':
	case 's':	goto yy14;
	case 'T':
	case 't':	goto yy15;
	case 'U':
	case 'u':	goto yy16;
	case 'X':
	case 'x':	goto yy17;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
yy3:
#line 22 "parse.hpp.re"
	{ return header::none; }
#line 61 "parse.hpp"
yy4:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'C':
	case 'c':	goto yy18;
	default:	goto yy3;
	}
yy5:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'A':
	case 'a':	goto yy20;
	case 'O':
	case 'o':	goto yy21;
	default:	goto yy3;
	}
yy6:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'A':
	case 'a':	goto yy22;
	default:	goto yy3;
	}
yy7:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy3;
	}
yy8:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'O':
	case 'o':	goto yy24;
	default:	goto yy3;
	}
yy9:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'F':
	case 'f':	goto yy25;
	default:	goto yy3;
	}
yy10:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'A':
	case 'a':	goto yy26;
	case 'O':
	case 'o':	goto yy27;
	default:	goto yy3;
	}
yy11:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'R':
	case 'r':	goto yy28;
	default:	goto yy3;
	}
yy12:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'R':
	case 'r':	goto yy29;
	default:	goto yy3;
	}
yy13:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy30;
	default:	goto yy3;
	}
yy14:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'E':
	case 'e':	goto yy31;
	default:	goto yy3;
	}
yy15:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'R':
	case 'r':	goto yy32;
	default:	goto yy3;
	}
yy16:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'S':
	case 's':	goto yy33;
	default:	goto yy3;
	}
yy17:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '-':	goto yy34;
	default:	goto yy3;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy35;
	default:	goto yy19;
	}
yy19:
	YYCURSOR = YYMARKER;
	goto yy3;
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy36;
	default:	goto yy19;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy37;
	case 'O':
	case 'o':	goto yy38;
	default:	goto yy19;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy39;
	default:	goto yy19;
	}
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'P':
	case 'p':	goto yy40;
	default:	goto yy19;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy41;
	default:	goto yy19;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy42;
	default:	goto yy19;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy43;
	default:	goto yy19;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy44;
	default:	goto yy19;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy45;
	default:	goto yy19;
	}
yy29:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy46;
	default:	goto yy19;
	}
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy47;
	default:	goto yy19;
	}
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy48;
	case 'T':
	case 't':	goto yy49;
	default:	goto yy19;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy50;
	default:	goto yy19;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy51;
	default:	goto yy19;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy52;
	case 'S':
	case 's':	goto yy53;
	default:	goto yy19;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy54;
	default:	goto yy19;
	}
yy36:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy55;
	default:	goto yy19;
	}
yy37:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy56;
	case 'T':
	case 't':	goto yy57;
	default:	goto yy19;
	}
yy38:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'K':
	case 'k':	goto yy58;
	default:	goto yy19;
	}
yy39:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy59;
	default:	goto yy19;
	}
yy40:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy61;
	case 'I':
	case 'i':	goto yy62;
	default:	goto yy19;
	}
yy41:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy63;
	default:	goto yy19;
	}
yy42:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'M':
	case 'm':	goto yy65;
	default:	goto yy19;
	}
yy43:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy66;
	default:	goto yy19;
	}
yy44:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy67;
	default:	goto yy19;
	}
yy45:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy68;
	default:	goto yy19;
	}
yy46:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy69;
	default:	goto yy19;
	}
yy47:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy70;
	default:	goto yy19;
	}
yy48:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'V':
	case 'v':	goto yy71;
	default:	goto yy19;
	}
yy49:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy72;
	default:	goto yy19;
	}
yy50:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy73;
	default:	goto yy19;
	}
yy51:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy74;
	default:	goto yy19;
	}
yy52:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy75;
	default:	goto yy19;
	}
yy53:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy76;
	default:	goto yy19;
	}
yy54:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'P':
	case 'p':	goto yy77;
	default:	goto yy19;
	}
yy55:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy78;
	default:	goto yy19;
	}
yy56:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy79;
	default:	goto yy19;
	}
yy57:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy80;
	default:	goto yy19;
	}
yy58:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy81;
	default:	goto yy19;
	}
yy59:
	++YYCURSOR;
#line 30 "parse.hpp.re"
	{ return header::date; }
#line 458 "parse.hpp"
yy61:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy82;
	default:	goto yy19;
	}
yy62:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy83;
	default:	goto yy19;
	}
yy63:
	++YYCURSOR;
#line 33 "parse.hpp.re"
	{ return header::host; }
#line 477 "parse.hpp"
yy65:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy84;
	default:	goto yy19;
	}
yy66:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy85;
	default:	goto yy19;
	}
yy67:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy86;
	default:	goto yy19;
	}
yy68:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy87;
	default:	goto yy19;
	}
yy69:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'M':
	case 'm':	goto yy88;
	default:	goto yy19;
	}
yy70:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy89;
	default:	goto yy19;
	}
yy71:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy90;
	default:	goto yy19;
	}
yy72:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy91;
	default:	goto yy19;
	}
yy73:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy92;
	default:	goto yy19;
	}
yy74:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy93;
	default:	goto yy19;
	}
yy75:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy94;
	default:	goto yy19;
	}
yy76:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy95;
	default:	goto yy19;
	}
yy77:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy96;
	default:	goto yy19;
	}
yy78:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy97;
	default:	goto yy19;
	}
yy79:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy98;
	default:	goto yy19;
	}
yy80:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy99;
	default:	goto yy19;
	}
yy81:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy100;
	default:	goto yy19;
	}
yy82:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy102;
	default:	goto yy19;
	}
yy83:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy104;
	default:	goto yy19;
	}
yy84:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy105;
	default:	goto yy19;
	}
yy85:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'M':
	case 'm':	goto yy106;
	default:	goto yy19;
	}
yy86:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy107;
	default:	goto yy19;
	}
yy87:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy108;
	default:	goto yy19;
	}
yy88:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy110;
	default:	goto yy19;
	}
yy89:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy112;
	default:	goto yy19;
	}
yy90:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy113;
	default:	goto yy19;
	}
yy91:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy115;
	default:	goto yy19;
	}
yy92:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy116;
	default:	goto yy19;
	}
yy93:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'A':
	case 'a':	goto yy117;
	default:	goto yy19;
	}
yy94:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy118;
	default:	goto yy19;
	}
yy95:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'V':
	case 'v':	goto yy119;
	default:	goto yy19;
	}
yy96:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy120;
	default:	goto yy19;
	}
yy97:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy121;
	default:	goto yy19;
	}
yy98:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy122;
	default:	goto yy19;
	}
yy99:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy123;
	default:	goto yy19;
	}
yy100:
	++YYCURSOR;
#line 29 "parse.hpp.re"
	{ return header::cookie; }
#line 723 "parse.hpp"
yy102:
	++YYCURSOR;
#line 31 "parse.hpp.re"
	{ return header::expect; }
#line 728 "parse.hpp"
yy104:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy124;
	default:	goto yy19;
	}
yy105:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy126;
	default:	goto yy19;
	}
yy106:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy127;
	default:	goto yy19;
	}
yy107:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy128;
	default:	goto yy19;
	}
yy108:
	++YYCURSOR;
#line 37 "parse.hpp.re"
	{ return header::origin; }
#line 761 "parse.hpp"
yy110:
	++YYCURSOR;
#line 38 "parse.hpp.re"
	{ return header::pragma; }
#line 766 "parse.hpp"
yy112:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy129;
	default:	goto yy19;
	}
yy113:
	++YYCURSOR;
#line 40 "parse.hpp.re"
	{ return header::server; }
#line 778 "parse.hpp"
yy115:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy131;
	default:	goto yy19;
	}
yy116:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy132;
	default:	goto yy19;
	}
yy117:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy133;
	default:	goto yy19;
	}
yy118:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy134;
	default:	goto yy19;
	}
yy119:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy135;
	default:	goto yy19;
	}
yy120:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy136;
	default:	goto yy19;
	}
yy121:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy137;
	default:	goto yy19;
	}
yy122:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy138;
	default:	goto yy19;
	}
yy123:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy139;
	default:	goto yy19;
	}
yy124:
	++YYCURSOR;
#line 32 "parse.hpp.re"
	{ return header::expires; }
#line 845 "parse.hpp"
yy126:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy140;
	default:	goto yy19;
	}
yy127:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy141;
	default:	goto yy19;
	}
yy128:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy142;
	default:	goto yy19;
	}
yy129:
	++YYCURSOR;
#line 39 "parse.hpp.re"
	{ return header::refresh; }
#line 871 "parse.hpp"
yy131:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'K':
	case 'k':	goto yy144;
	default:	goto yy19;
	}
yy132:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy145;
	default:	goto yy19;
	}
yy133:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy146;
	default:	goto yy19;
	}
yy134:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy147;
	default:	goto yy19;
	}
yy135:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy149;
	default:	goto yy19;
	}
yy136:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy151;
	default:	goto yy19;
	}
yy137:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy152;
	default:	goto yy19;
	}
yy138:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy153;
	default:	goto yy19;
	}
yy139:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy154;
	case 'L':
	case 'l':	goto yy155;
	case 'T':
	case 't':	goto yy156;
	default:	goto yy19;
	}
yy140:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy157;
	default:	goto yy19;
	}
yy141:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy158;
	default:	goto yy19;
	}
yy142:
	++YYCURSOR;
#line 36 "parse.hpp.re"
	{ return header::location; }
#line 957 "parse.hpp"
yy144:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy159;
	default:	goto yy19;
	}
yy145:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy160;
	default:	goto yy19;
	}
yy146:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy161;
	default:	goto yy19;
	}
yy147:
	++YYCURSOR;
#line 44 "parse.hpp.re"
	{ return header::x_client; }
#line 982 "parse.hpp"
yy149:
	++YYCURSOR;
#line 45 "parse.hpp.re"
	{ return header::x_server; }
#line 987 "parse.hpp"
yy151:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy162;
	default:	goto yy19;
	}
yy152:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy163;
	default:	goto yy19;
	}
yy153:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy164;
	default:	goto yy19;
	}
yy154:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy166;
	default:	goto yy19;
	}
yy155:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy167;
	default:	goto yy19;
	}
yy156:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'Y':
	case 'y':	goto yy168;
	default:	goto yy19;
	}
yy157:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy169;
	default:	goto yy19;
	}
yy158:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'F':
	case 'f':	goto yy170;
	default:	goto yy19;
	}
yy159:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy171;
	default:	goto yy19;
	}
yy160:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy173;
	default:	goto yy19;
	}
yy161:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy174;
	default:	goto yy19;
	}
yy162:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy176;
	default:	goto yy19;
	}
yy163:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'R':
	case 'r':	goto yy177;
	default:	goto yy19;
	}
yy164:
	++YYCURSOR;
#line 25 "parse.hpp.re"
	{ return header::connection; }
#line 1083 "parse.hpp"
yy166:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy178;
	default:	goto yy19;
	}
yy167:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy179;
	default:	goto yy19;
	}
yy168:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'P':
	case 'p':	goto yy180;
	default:	goto yy19;
	}
yy169:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy181;
	default:	goto yy19;
	}
yy170:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy182;
	default:	goto yy19;
	}
yy171:
	++YYCURSOR;
#line 41 "parse.hpp.re"
	{ return header::set_cookie; }
#line 1123 "parse.hpp"
yy173:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy183;
	default:	goto yy19;
	}
yy174:
	++YYCURSOR;
#line 43 "parse.hpp.re"
	{ return header::user_agent; }
#line 1135 "parse.hpp"
yy176:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy184;
	default:	goto yy19;
	}
yy177:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy185;
	default:	goto yy19;
	}
yy178:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy186;
	default:	goto yy19;
	}
yy179:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy187;
	default:	goto yy19;
	}
yy180:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy188;
	default:	goto yy19;
	}
yy181:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy190;
	default:	goto yy19;
	}
yy182:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy191;
	default:	goto yy19;
	}
yy183:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy192;
	default:	goto yy19;
	}
yy184:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy193;
	default:	goto yy19;
	}
yy185:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'l':	goto yy194;
	default:	goto yy19;
	}
yy186:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy196;
	default:	goto yy19;
	}
yy187:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'T':
	case 't':	goto yy197;
	default:	goto yy19;
	}
yy188:
	++YYCURSOR;
#line 27 "parse.hpp.re"
	{ return header::content_type; }
#line 1223 "parse.hpp"
yy190:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'S':
	case 's':	goto yy198;
	default:	goto yy19;
	}
yy191:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy199;
	default:	goto yy19;
	}
yy192:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'O':
	case 'o':	goto yy201;
	default:	goto yy19;
	}
yy193:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy202;
	default:	goto yy19;
	}
yy194:
	++YYCURSOR;
#line 24 "parse.hpp.re"
	{ return header::cache_control; }
#line 1256 "parse.hpp"
yy196:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy203;
	default:	goto yy19;
	}
yy197:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'H':
	case 'h':	goto yy204;
	default:	goto yy19;
	}
yy198:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy206;
	default:	goto yy19;
	}
yy199:
	++YYCURSOR;
#line 35 "parse.hpp.re"
	{ return header::last_modified; }
#line 1282 "parse.hpp"
yy201:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'D':
	case 'd':	goto yy207;
	default:	goto yy19;
	}
yy202:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy208;
	default:	goto yy19;
	}
yy203:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy210;
	default:	goto yy19;
	}
yy204:
	++YYCURSOR;
#line 28 "parse.hpp.re"
	{ return header::content_length; }
#line 1308 "parse.hpp"
yy206:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy211;
	default:	goto yy19;
	}
yy207:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'I':
	case 'i':	goto yy212;
	default:	goto yy19;
	}
yy208:
	++YYCURSOR;
#line 23 "parse.hpp.re"
	{ return header::accept_encoding; }
#line 1327 "parse.hpp"
yy210:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy213;
	default:	goto yy19;
	}
yy211:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':
	case 'c':	goto yy215;
	default:	goto yy19;
	}
yy212:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'N':
	case 'n':	goto yy216;
	default:	goto yy19;
	}
yy213:
	++YYCURSOR;
#line 26 "parse.hpp.re"
	{ return header::content_encoding; }
#line 1353 "parse.hpp"
yy215:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':
	case 'e':	goto yy217;
	default:	goto yy19;
	}
yy216:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'G':
	case 'g':	goto yy219;
	default:	goto yy19;
	}
yy217:
	++YYCURSOR;
#line 34 "parse.hpp.re"
	{ return header::if_modified_since; }
#line 1372 "parse.hpp"
yy219:
	++YYCURSOR;
#line 42 "parse.hpp.re"
	{ return header::transfer_encoding; }
#line 1377 "parse.hpp"
}
#line 47 "parse.hpp.re"

}

}  // namespace detail
}  // namespace http

// vim:ft=cpp

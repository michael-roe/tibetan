/*-
 * Copyright (c) 2021 Michael Roe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * tibetan.c - transliterate text in the Tibetan script into the Latin
 * alphabet. This program does not use the standard Wylie transliteration,
 * but instead transliterates into Devanagri and then from Devanagri to
 * Latin using the IAST transliteration. For Sankrit-language text in
 * the Tibetan script, this will yield a result closer to the usual way
 * Sanskrit is written in the Latin alphabet. It is less suitable for
 * Tibetan-language text.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

int main(int argc, char **argv)
{
wchar_t *cp;
int len;

  wchar_t buff[80];

  setlocale(LC_ALL, getenv("LANG"));

  while (fgetws(buff, 80, stdin))
  {
    cp = buff;
    while (*cp)
    {
      switch (*cp)
      {
	case ' ':
	  wprintf(L" ");
	  break;
	case '\n':
	  wprintf(L"\n");
	  break;
	case 0xf00:
	  wprintf(L"o%lc", 0x1e43);
	  break;
        case 0xf0b: /* tsheg - syllable divider */
          wprintf(L"-");
	  break;
	case 0xf0d: /* shad - section break */
	  wprintf(L"|\n");
	  break;
	case 0xf14: /* gter tsheg - a "comma like delimiter" */
	  wprintf(L";");
	  break;
	case 0xf40: /* KA */
	  wprintf(L"k");
	  break;
	case 0xf41: /* KHA */
	  wprintf(L"kh");
	  break;
	case 0xf42: /* GA */
	  wprintf(L"g");
	  break;
	case 0xf43: /* GHA */
	  wprintf(L"gh");
	  break;
        case 0xf44: /* NGA */
	  wprintf(L"%lc", 0x1e45); /* with dot above */
	  break;
	case 0xf59: /* TSA */
	  wprintf(L"c"); /* Sanskrit CA is transliterated as TSA */
	  break;
	case 0xf5a: /* TSHA */
	  wprintf(L"ch");
	  break;
	case 0xf5b: /* DZA */
	  wprintf(L"j"); /* Sanskrit JA is transliterated as DZA */
	  break;
	case 0xf49: /* NYA */
	  wprintf(L"%lc", 0xf1); /* n with tilde */
	  break;
	case 0xf4a: /* TTA */
	  wprintf(L"%lc", 0x1e6d); /* t with dot below */
	  break;
	case 0xf4b: /* TTHA */
	  wprintf(L"%lch", 0x1e6d); /* t with dot below */
	  break;
	case 0xf4c: /* DDA */
	  wprintf(L"%lc", 0x1e0d); /* d with dot below */
	  break;
	case 0xf4e: /* NNA */
	  wprintf(L"%lc", 0x1e47); /* n with dot below */
	  break;
	case 0xf4f: /* TA */
	  wprintf(L"t");
	  break;
	case 0xf50: /* THA */
	  wprintf(L"th");
	  break;
	case 0xf51: /* DA */
	  wprintf(L"d");
	  break;
	case 0xf52: /* DHA */
	  wprintf(L"dh");
	  break;
	case 0xf53: /* NA */
	  wprintf(L"n");
	  break;
	case 0xf54: /* PA */
	  wprintf(L"p");
	  break;
	case 0xf55: /* PHA */
	  wprintf(L"ph");
	  break;
	case 0xf56: /* BA */
	  wprintf(L"b");
	  break;
	case 0xf57: /* BHA */
	  wprintf(L"bh");
	  break;
	case 0xf58: /* MA */
	  wprintf(L"m");
	  break;
	case 0xf61: /* YA */
	  wprintf(L"y");
	  break;
	case 0xf62: /* RA */
	  if (cp[1] == 0xf80)
          {
	    wprintf(L"%lc", 0x1e5b);
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            wprintf(L"%lc", 0x1e5d);
	    cp += 2;
	  }
	  else
	    wprintf(L"r");
	  break;
	case 0xf63: /* LA */
	  if (cp[1] == 0xf80)
	  {
	    wprintf(L"%lc", 0x1e37);
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            wprintf(L"%lc", 0x1e39);
	    cp += 2;
	  }
	  else
	    wprintf(L"l");
	  break;
	case 0xf5d: /* WA */
	  wprintf(L"v");
	  break;
	case 0xf64: /* SHA */
	  wprintf(L"%lc", 0x15b); /* s with acute */
	  break;
	case 0xf65:
	  wprintf(L"%lc", 0x1e63); /* s with dot below */
	  break;
	case 0xf66: /* SA */
	  wprintf(L"s");
	  break;
	case 0xf67: /* HA */
	  wprintf(L"h");
	  break;
	case 0xf68: /* Vowel with no consonant */
	  break;
	/* Vowels */
	case 0xf71: /* AA */
	  if (cp[1] == 0xf72)
	  {
	    wprintf(L"%lc", 0x12b); /* i with macron */
	    cp++;
	  }
	  else if (cp[1] == 0xf74)
	  {
	    wprintf(L"%lc", 0x16b); /* u with macron */
	    cp++;
	  }
	  else
	    wprintf(L"%lc", 0x101); /* a with macron */
	  break;
	case 0xf72: /* I */
	  wprintf(L"i");
	  break;
	case 0xf73: /* II */
	  /* "discouraged" in the Unicode standard */
	  wprintf(L"%lc", 0x12b); /* i with macron */
	  break;
	case 0xf74: /* U */
	  wprintf(L"u");
	  break;
	case 0xf75: /* UU, "discouraged" */
	  wprintf(L"%lc", 0x16b); /* u with macron */
	  break;
	case 0xf7a: /* E */
	  wprintf(L"e");
	  break;
	case 0xf7b: /* EE */
	  wprintf(L"ai"); /* Apparently, Sanskrit AI is transliterated as EE */
	  break;
	case 0xf7c: /* O */
	  wprintf(L"o");
	  break;
	case 0xf7d: /* OO */
	  wprintf(L"au"); /* Sanskrit AU is transliterated as OO */
	  break;
	case 0xf7e: /* anusvara */
	  wprintf(L"%lc", 0x1e43); /* m with dot below */
	  break;
	case 0xf7f: /* visarga */
	  wprintf(L"%lc", 0x1e25); /* h with dot below */
	  break;
	case 0xf83: /* candrabindu */
	  wprintf(L"~");
	  break;
	/* Subjoined characters */
	case 0xf90: /* subjoined KA */
	  wprintf(L"k");
	  break;
	case 0xf91: /* subjoined KHA */
	  wprintf(L"kh");
	  break;
	case 0xf92: /* subjoined GA */
	  wprintf(L"g");
	  break;
	case 0xf93: /* subjoined GHA */
	  wprintf(L"gh");
	  break;
        case 0xf94: /* subjoined NGA */
	  wprintf(L"%lc", 0x1e45); /* n with dot above */
	  break;
	case 0xfa9: /* subjoined TSA */
	case 0xf95: /* subjoined CA */
	  wprintf(L"c"); /* Sanskrit CA is transliterated as TSA */
	  break;
	case 0xfaa: /* subjoined TSHA */
	case 0xf96: /* subjoined CHA */
	  wprintf(L"ch");
	  break;
	case 0xfab: /* subjoined DZA */
	  wprintf(L"j"); /* Sanskrit JA is transliterated as DZA */
	  break;
	  /* What about DZHA? */
	case 0xf99: /* subjoined NYA */
	  wprintf(L"%lc", 0xf1); /* n with tilde */
	  break;
	case 0xf9a: /* subjoined TTA */
	  wprintf(L"%lc", 0x1e6d); /* t with dot below */
	  break;
	case 0xf9b: /* subjoined TTHA */
	  wprintf(L"%lch", 0x1e6d); /* t with dot below */
	  break;
	case 0xf9c: /* subjoined DDA */
	  wprintf(L"%lc", 0x1e0d); /* d with dot below */
	  break;
	case 0xf9e: /* subjoined NNA */
	  wprintf(L"%lc", 0x1e47); /* n with dot below */
	  break;
	case 0xf9f: /* subjoined TA */
	  wprintf(L"t");
	  break;
	case 0xfa0: /* subjoined THA */
	  wprintf(L"th");
	  break;
	case 0xfa1: /* subjoined DA */
	  wprintf(L"d");
	  break;
	case 0xfa2: /* subjoined DHA */
	  wprintf(L"dh");
	  break;
	case 0xfa3: /* subjoined NA */
	  wprintf(L"n");
	  break;
	case 0xfa4: /* subjoined PA */
	  wprintf(L"p");
	  break;
	case 0xfa5: /* subjoined PHA */
	  wprintf(L"ph");
	  break;
	case 0xfa6: /* subjoined BA */
	  wprintf(L"b");
	  break;
	case 0xfa7: /* subjoined BHA */
	  wprintf(L"bh");
	  break;
	case 0xfa8: /* subjoined MA */
	  wprintf(L"m");
	  break;
	case 0xfb1: /* subjoined YA */
	  wprintf(L"y");
	  break;
	case 0xfb2: /* subjoined RA */
	  if (cp[1] == 0xf80)
          {
            wprintf(L"%lc", 0x1e5b);
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            wprintf(L"%lc", 0x1e5d);
            cp += 2;
          }
	  else
	    wprintf(L"r");
	  break;
	case 0xfb3: /* subjoinmed LA */
	  if (cp[1] == 0xf80)
	  {
	    wprintf(L"%lc", 0x1e37);
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            wprintf(L"%lc", 0x1e39);
	    cp += 2;
	  }
	  else
	    wprintf(L"l");
	  break;
	case 0xfad: /* subjoined WA */
	  wprintf(L"v"); /* Use v rather than w in Sanskrit transliteration */
	  break;
	case 0xfb4: /* subjoined SHA */
	  wprintf(L"%lc", 0x15b); /* s with acute */
	  break;
	case 0xfb5: /* subjoined SSA */
	  wprintf(L"%lc", 0x1e63); /* s with dot below */
	  break;
	case 0xfb7: /* subjoined HA */
	  wprintf(L"h");
	  break;
	default:
          wprintf(L"%x ", *cp);
      }
      cp++;
    }
  }
  wprintf(L"\n");
  return 0;

}


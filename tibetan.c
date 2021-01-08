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

static int vowel_wait;

static void vowel(wchar_t *s)
{
  wprintf(L"%ls", s);
  vowel_wait = 0;
}

static void anusvara(wchar_t *s)
{
  if (vowel_wait)
  {
    wprintf(L"a");
    vowel_wait = 0;
  }
  wprintf(L"%ls", s);
}

static void consonant(wchar_t *s)
{
  if (vowel_wait)
  {
    wprintf(L"a");
  }
  wprintf(L"%ls", s);
  vowel_wait = 1;
}

static void subjoined_consonant(wchar_t *s)
{
  wprintf(L"%ls", s);
}

static void punctuation(wchar_t *s)
{
  if (vowel_wait)
  {
    wprintf(L"a");
    vowel_wait = 0;
  }
  wprintf(L"%s", s);
}

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
	  punctuation(L"\n");
	  break;
	case 0xf00:
	  wprintf(L"o%lc", 0x1e43);
	  break;
        case 0xf0b: /* tsheg - syllable divider */
          punctuation(L"-");
	  break;
	case 0xf0d: /* shad - section break */
	  punctuation(L"|\n");
	  break;
	case 0xf14: /* gter tsheg - a "comma like delimiter" */
	  punctuation(L";");
	  break;
	case 0xf40: /* KA */
	  consonant(L"k");
	  break;
	case 0xf41: /* KHA */
	  consonant(L"kh");
	  break;
	case 0xf42: /* GA */
	  consonant(L"g");
	  break;
	case 0xf43: /* GHA */
	  consonant(L"gh");
	  break;
        case 0xf44: /* NGA */
	  consonant(L"\u1e45"); /* with dot above */
	  break;
	case 0xf59: /* TSA */
	case 0xf45: /* CA */
	  consonant(L"c"); /* Sanskrit CA is transliterated as TSA */
	  break;
	case 0xf5a: /* TSHA */
	case 0xf46: /* CHA */
	  consonant(L"ch");
	  break;
	case 0xf5b: /* DZA */
	  consonant(L"j"); /* Sanskrit JA is transliterated as DZA */
	  break;
	case 0xf5c: /* DZHA */
	  consonant(L"jh");
	  break;
	case 0xf49: /* NYA */
	  consonant(L"\u00f1"); /* n with tilde */
	  break;
	case 0xf4a: /* TTA */
	  consonant(L"\u1e6d"); /* t with dot below */
	  break;
	case 0xf4b: /* TTHA */
	  consonant(L"\u1e6d"); /* t with dot below */
	  break;
	case 0xf4c: /* DDA */
	  consonant(L"\u1e0d"); /* d with dot below */
	  break;
	case 0xf4d: /* DDHA */
	  consonant(L"\u1e0dh");
	  break;
	case 0xf4e: /* NNA */
	  consonant(L"\u1e47"); /* n with dot below */
	  break;
	case 0xf4f: /* TA */
	  consonant(L"t");
	  break;
	case 0xf50: /* THA */
	  consonant(L"th");
	  break;
	case 0xf51: /* DA */
	  consonant(L"d");
	  break;
	case 0xf52: /* DHA */
	  consonant(L"dh");
	  break;
	case 0xf53: /* NA */
	  consonant(L"n");
	  break;
	case 0xf54: /* PA */
	  consonant(L"p");
	  break;
	case 0xf55: /* PHA */
	  consonant(L"ph");
	  break;
	case 0xf56: /* BA */
	  consonant(L"b");
	  break;
	case 0xf57: /* BHA */
	  consonant(L"bh");
	  break;
	case 0xf58: /* MA */
	  consonant(L"m");
	  break;
	case 0xf61: /* YA */
	  consonant(L"y");
	  break;
	case 0xf62: /* RA */
	  if (cp[1] == 0xf80)
          {
	    vowel(L"\u1e5b");
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            vowel(L"\u1e5d");
	    cp += 2;
	  }
	  else
	    consonant(L"r");
	  break;
	case 0xf63: /* LA */
	  if (cp[1] == 0xf80)
	  {
	    vowel(L"\u1e37");
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            vowel(L"\u1e39");
	    cp += 2;
	  }
	  else
	    consonant(L"l");
	  break;
	case 0xf5d: /* WA */
	  consonant(L"v");
	  break;
	case 0xf64: /* SHA */
	  consonant(L"\u015b"); /* s with acute */
	  break;
	case 0xf65:
	  consonant(L"\u1e63"); /* s with dot below */
	  break;
	case 0xf66: /* SA */
	  consonant(L"s");
	  break;
	case 0xf67: /* HA */
	  consonant(L"h");
	  break;
	case 0xf68: /* Vowel with no consonant */
	  vowel_wait = 1;
	  break;
	/* Vowels */
	case 0xf71: /* AA */
	  if (cp[1] == 0xf72)
	  {
	    vowel(L"\u012b"); /* i with macron */
	    cp++;
	  }
	  else if (cp[1] == 0xf74)
	  {
	    vowel(L"\u016b"); /* u with macron */
	    cp++;
	  }
	  else
	    vowel(L"\u0101"); /* a with macron */
	  break;
	case 0xf72: /* I */
	  vowel(L"i");
	  break;
	case 0xf73: /* II */
	  /* "discouraged" in the Unicode standard */
	  vowel(L"\u012b"); /* i with macron */
	  break;
	case 0xf74: /* U */
	  vowel(L"u");
	  break;
	case 0xf75: /* UU, "discouraged" */
	  vowel(L"\u016b"); /* u with macron */
	  break;
	case 0xf7a: /* E */
	  vowel(L"e");
	  break;
	case 0xf7b: /* EE */
	  vowel(L"ai"); /* Apparently, Sanskrit AI is transliterated as EE */
	  break;
	case 0xf7c: /* O */
	  vowel(L"o");
	  break;
	case 0xf7d: /* OO */
	  vowel(L"au"); /* Sanskrit AU is transliterated as OO */
	  break;
	case 0xf7e: /* anusvara */
	  anusvara(L"\u1e43"); /* m with dot below */
	  break;
	case 0xf7f: /* visarga */
	  anusvara(L"\u1e25"); /* h with dot below */
	  break;
	case 0xf83: /* candrabindu */
	  anusvara(L"~");
	  break;
	/* Subjoined characters */
	case 0xf90: /* subjoined KA */
	  subjoined_consonant(L"k");
	  break;
	case 0xf91: /* subjoined KHA */
	  subjoined_consonant(L"kh");
	  break;
	case 0xf92: /* subjoined GA */
	  subjoined_consonant(L"g");
	  break;
	case 0xf93: /* subjoined GHA */
	  subjoined_consonant(L"gh");
	  break;
        case 0xf94: /* subjoined NGA */
	  subjoined_consonant(L"\u1e45"); /* n with dot above */
	  break;
	case 0xfa9: /* subjoined TSA */
	case 0xf95: /* subjoined CA */
	  subjoined_consonant(L"c"); /* Sanskrit CA is transliterated as TSA */
	  break;
	case 0xfaa: /* subjoined TSHA */
	case 0xf96: /* subjoined CHA */
	  subjoined_consonant(L"ch");
	  break;
	case 0xfab: /* subjoined DZA */
	  subjoined_consonant(L"j"); /* Sanskrit JA is transliterated as DZA */
	  break;
	  /* What about DZHA? */
	case 0xf99: /* subjoined NYA */
	  subjoined_consonant(L"\u00f1"); /* n with tilde */
	  break;
	case 0xf9a: /* subjoined TTA */
	  subjoined_consonant(L"\u1e6d"); /* t with dot below */
	  break;
	case 0xf9b: /* subjoined TTHA */
	  subjoined_consonant(L"\u1e6d"); /* t with dot below */
	  break;
	case 0xf9c: /* subjoined DDA */
	  subjoined_consonant(L"\u1e0d"); /* d with dot below */
	  break;
	case 0xf9e: /* subjoined NNA */
	  subjoined_consonant(L"\u1e47"); /* n with dot below */
	  break;
	case 0xf9f: /* subjoined TA */
	  subjoined_consonant(L"t");
	  break;
	case 0xfa0: /* subjoined THA */
	  subjoined_consonant(L"th");
	  break;
	case 0xfa1: /* subjoined DA */
	  subjoined_consonant(L"d");
	  break;
	case 0xfa2: /* subjoined DHA */
	  subjoined_consonant(L"dh");
	  break;
	case 0xfa3: /* subjoined NA */
	  subjoined_consonant(L"n");
	  break;
	case 0xfa4: /* subjoined PA */
	  subjoined_consonant(L"p");
	  break;
	case 0xfa5: /* subjoined PHA */
	  subjoined_consonant(L"ph");
	  break;
	case 0xfa6: /* subjoined BA */
	  subjoined_consonant(L"b");
	  break;
	case 0xfa7: /* subjoined BHA */
	  subjoined_consonant(L"bh");
	  break;
	case 0xfa8: /* subjoined MA */
	  subjoined_consonant(L"m");
	  break;
	case 0xfb1: /* subjoined YA */
	  subjoined_consonant(L"y");
	  break;
	case 0xfb2: /* subjoined RA */
	  if (cp[1] == 0xf80)
          {
            vowel(L"\u1e5b");
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            vowel(L"\u1e5d");
            cp += 2;
          }
	  else
	    subjoined_consonant(L"r");
	  break;
	case 0xfb3: /* subjoined LA */
	  if (cp[1] == 0xf80)
	  {
	    vowel(L"\u1e37");
	    cp++;
	  }
	  else if ((cp[1] == 0xf71) && (cp[2] == 0xf80))
	  {
            vowel(L"\u1e39");
	    cp += 2;
	  }
	  else
	    subjoined_consonant(L"l");
	  break;
	case 0xfad: /* subjoined WA */
	  subjoined_consonant(L"v"); /* Use v rather than w in Sanskrit transliteration */
	  break;
	case 0xfb4: /* subjoined SHA */
	  subjoined_consonant(L"%\u015b"); /* s with acute */
	  break;
	case 0xfb5: /* subjoined SSA */
	  subjoined_consonant(L"\u1e63"); /* s with dot below */
	  break;
	case 0xfb7: /* subjoined HA */
	  subjoined_consonant(L"h");
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


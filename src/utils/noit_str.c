/*
 * Copyright (c) 2005-2007, OmniTI Computer Consulting, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *    * Neither the name OmniTI Computer Consulting, Inc. nor the names
 *      of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "noit_defines.h"

#ifndef HAVE_STRNSTRN

#define KMPPATSIZE 256
static void kmp_precompute(const char *pattern, int pattern_len,
                           int *compile_buf) {
  int i=0, j=-1;

  compile_buf[0] = j;
  while (i < pattern_len) {
    while (j > -1 && pattern[i] != pattern[j])
      j = compile_buf[j];
    i++; j++;
    if (pattern[i] == pattern[j])
      compile_buf[i] = compile_buf[j];
    else
      compile_buf[i] = j;
  }
}

const char *strnstrn(const char *needle, int needle_len,
                     const char *haystack, int haystack_len) {
  int i=0, j=0, compiled[KMPPATSIZE];

  if(needle_len > KMPPATSIZE)
    abort();
  kmp_precompute(needle, needle_len, compiled);
  while (j < haystack_len) {
    while (i > -1 && needle[i] != haystack[j])
      i = compiled[i];
    i++; j++;
    if (i >= needle_len) {
      return haystack + j - i;
    }
  }
  return NULL;
}

char *
noit__strndup(const char *src, int len) {
  int slen;
  char *dst;
  for(slen = 0; slen < len; slen++)
    if(src[slen] == '\0') break;
  dst = malloc(slen + 1);
  memcpy(dst, src, slen);
  dst[slen] = '\0';
  return dst;
}

#endif


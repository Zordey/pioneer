<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
<<<<<<< HEAD
#include <GL/glew.h>
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#include "libs.h"

#ifndef __GNUC__
#define __attribute(x)
#endif /* __GNUC__ */

// GCC warns when a function marked __attribute((noreturn)) actually returns a value
// but other compilers which don't see the noreturn attribute of course require that
// a function with a non-void return type should return something.
#ifndef __GNUC__
#define RETURN_ZERO_NONGNU_ONLY return 0;
#else
#define RETURN_ZERO_NONGNU_ONLY
#endif

void Error(const char *format, ...) __attribute((format(printf,1,2))) __attribute((noreturn));
void Warning(const char *format, ...)  __attribute((format(printf,1,2)));
void Output(const char *format, ...)  __attribute((format(printf,1,2)));

std::string string_join(std::vector<std::string> &v, std::string sep);
std::string format_date(double time);
std::string format_date_only(double time);
std::string format_distance(double dist, int precision = 2);
std::string format_money(Sint64 money);

static inline Sint64 isqrt(Sint64 a)
{
	Sint64 ret=0;
	Sint64 s;
	Sint64 ret_sq=-a-1;
	for(s=62; s>=0; s-=2){
		Sint64 b;
		ret+= ret;
		b=ret_sq + ((2*ret+1)<<s);
		if(b<0){
			ret_sq=b;
			ret++;
		}
	}
	return ret;
}

void Screendump(const char* destFile, const int w, const int h);

// find string in bigger string, ignoring case
const char *pi_strcasestr(const char *haystack, const char *needle);

inline bool starts_with(const char *s, const char *t) {
	assert(s && t);
	while ((*s == *t) && *t) { ++s; ++t; }
	return (*t == '\0');
}

inline bool starts_with(const std::string &s, const char *t) {
	assert(t);
	return starts_with(s.c_str(), t);
}

inline bool starts_with(const std::string &s, const std::string &t) {
	return starts_with(s.c_str(), t.c_str());
}

inline bool ends_with(const char *s, size_t ns, const char *t, size_t nt) {
	return (ns >= nt) && (memcmp(s+(ns-nt), t, nt) == 0);
}

inline bool ends_with(const char *s, const char *t) {
	return ends_with(s, strlen(s), t, strlen(t));
}
<<<<<<< HEAD

inline bool ends_with(const std::string &s, const char *t) {
	return ends_with(s.c_str(), s.size(), t, strlen(t));
}

inline bool ends_with(const std::string &s, const std::string &t) {
	return ends_with(s.c_str(), s.size(), t.c_str(), t.size());
}

// add a few things that MSVC is missing
#ifdef _MSC_VER
=======

inline bool ends_with(const std::string &s, const char *t) {
	return ends_with(s.c_str(), s.size(), t, strlen(t));
}

inline bool ends_with(const std::string &s, const std::string &t) {
	return ends_with(s.c_str(), s.size(), t.c_str(), t.size());
}

inline bool ends_with_ci(const char *s, size_t ns, const char *t, size_t nt) {
	if (ns<nt) return false;
	s += (ns-nt);
	for (size_t i=0; i<nt; i++)
		if(tolower(*s++)!=tolower(*t++)) return false;
	return true;
}

inline bool ends_with_ci(const char *s, const char *t) {
	return ends_with_ci(s, strlen(s), t, strlen(t));
}

inline bool ends_with_ci(const std::string &s, const char *t) {
	return ends_with_ci(s.c_str(), s.size(), t, strlen(t));
}

inline bool ends_with_ci(const std::string &s, const std::string &t) {
	return ends_with_ci(s.c_str(), s.size(), t.c_str(), t.size());
}

// add a few things that MSVC is missing
#if defined(_MSC_VER) && (_MSC_VER < 1800)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

// round & roundf. taken from http://cgit.freedesktop.org/mesa/mesa/tree/src/gallium/auxiliary/util/u_math.h
static inline double round(double x)
{
   return x >= 0.0 ? floor(x + 0.5) : ceil(x - 0.5);
}

static inline float roundf(float x)
{
   return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
}
<<<<<<< HEAD
#endif /* _MSC_VER */
=======
#endif /* _MSC_VER < 1800 */
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

static inline Uint32 ceil_pow2(Uint32 v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

void hexdump(const unsigned char *buf, int bufsz);

#endif /* _UTILS_H */

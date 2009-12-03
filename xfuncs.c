/*
 * Copyright 2003-2007 Gentoo Foundation
 * Distributed under the terms of the GNU General Public License v2
 * $Header: /var/cvsroot/gentoo-projects/pax-utils/xfuncs.c,v 1.7 2009/12/03 04:15:54 vapier Exp $
 *
 * Copyright 2003-2007 Ned Ludd        - <solar@gentoo.org>
 * Copyright 2004-2007 Mike Frysinger  - <vapier@gentoo.org>
 */

#include "paxinc.h"

char *xstrdup(const char *s)
{
	char *ret = strdup(s);
	if (!ret) err("Could not strdup(): %s", strerror(errno));
	return ret;
}

void *xmalloc(size_t size)
{
	void *ret = malloc(size);
	if (!ret) err("Could not malloc() %li bytes", (unsigned long)size);
	return ret;
}

void *xzalloc(size_t size)
{
	return memset(xmalloc(size), 0, size);
}

void *xrealloc(void *ptr, size_t size)
{
	void *ret = realloc(ptr, size);
	if (!ret) err("Could not realloc() %li bytes", (unsigned long)size);
	return ret;
}

void xstrncat(char **dst, const char *src, size_t *curr_len, size_t n)
{
	size_t new_len;

	new_len = (*curr_len ? strlen(*dst) : 0) + strlen(src);
	if (*curr_len <= new_len) {
		*curr_len = new_len + (*curr_len / 2);
		*dst = realloc(*dst, *curr_len);
		if (!*dst)
			err("could not realloc() %li bytes", (unsigned long)*curr_len);
	}

	if (n)
		strncat(*dst, src, n);
	else
		strcat(*dst, src);
}

void xchrcat(char **dst, const char append, size_t *curr_len)
{
	static char my_app[2];
	my_app[0] = append;
	my_app[1] = '\0';
	xstrcat(dst, my_app, curr_len);
}

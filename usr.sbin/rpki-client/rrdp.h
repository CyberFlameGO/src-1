/*	$OpenBSD: rrdp.h,v 1.6 2021/10/29 09:27:36 claudio Exp $ */
/*
 * Copyright (c) 2020 Nils Fisher <nils_fisher@hotmail.com>
 * Copyright (c) 2021 Claudio Jeker <claudio@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef _RRDPH_
#define _RRDPH_

#define MAX_VERSION 1

#define log_debuginfo(format, ...) logx(format, ##__VA_ARGS__)

/* save everyone doing this code over and over */
#define PARSE_FAIL(p, ...) do {		\
	XML_StopParser(p, XML_FALSE);	\
	warnx(__VA_ARGS__);		\
	return;				\
} while (0)

enum rrdp_task {
	NOTIFICATION,
	SNAPSHOT,
	DELTA,
};

/* rrdp generic */
char	*xstrdup(const char *);
int	 hex_decode(const char *, char *, size_t);

/* publish or withdraw element */
struct rrdp;
struct publish_xml;

struct publish_xml	*new_publish_xml(enum publish_type, char *,
			    char *, size_t);
void			 free_publish_xml(struct publish_xml *);
int			 publish_add_content(struct publish_xml *,
			    const char *, int);
int			 publish_done(struct rrdp *, struct publish_xml *);

/* notification */
struct notification_xml;

struct notification_xml	*new_notification_xml(XML_Parser,
			    struct rrdp_session *, struct rrdp_session *,
			    const char *);
void			 free_notification_xml(struct notification_xml *);
enum rrdp_task		 notification_done(struct notification_xml *,
			    char *);
const char		*notification_get_next(struct notification_xml *,
			    char *, size_t, enum rrdp_task);
int			 notification_delta_done(struct notification_xml *);
void			 log_notification_xml(struct notification_xml *);

/* snapshot */
struct snapshot_xml;

struct snapshot_xml	*new_snapshot_xml(XML_Parser, struct rrdp_session *,
			    struct rrdp *);
void			 free_snapshot_xml(struct snapshot_xml *);
void			 log_snapshot_xml(struct snapshot_xml *);

/* delta */
struct delta_xml;

struct delta_xml	*new_delta_xml(XML_Parser, struct rrdp_session *,
			    struct rrdp *);
void			 free_delta_xml(struct delta_xml *);
void			 log_delta_xml(struct delta_xml *);

#endif /* _RRDPH_ */

/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __XFS_MESSAGE_H
#define __XFS_MESSAGE_H 1

#include <linux/once_lite.h>

struct xfs_mount;

#define xfs_printk_index_wrap(_p_func, kern_level, mp, fmt, ...)	\
({									\
	printk_index_subsys_emit(					\
		"%sXFS%s: ", kern_level, fmt, ##__VA_ARGS__);		\
	xfs_printk_level(kern_level, mp, fmt, ##__VA_ARGS__);		\
})
#define xfs_alert_tag(mp, tag, fmt, ...)			\
({								\
	printk_index_subsys_emit(				\
		"%sXFS%s: ", KERN_ALERT, fmt, ##__VA_ARGS__);	\
	_xfs_alert_tag(mp, tag, fmt, ##__VA_ARGS__);		\
})
#define xfs_emerg(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_emerg, KERN_EMERG, mp, fmt, ##__VA_ARGS__)
#define xfs_alert(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_alert, KERN_ALERT, mp, fmt, ##__VA_ARGS__)
#define xfs_crit(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_crit, KERN_CRIT, mp, fmt, ##__VA_ARGS__)
#define xfs_err(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_err, KERN_ERR, mp, fmt, ##__VA_ARGS__)
#define xfs_warn(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_warn, KERN_WARNING, mp, fmt, ##__VA_ARGS__)
#define xfs_notice(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_notice, KERN_NOTICE, mp, fmt, ##__VA_ARGS__)
#define xfs_info(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_info, KERN_INFO, mp, fmt, ##__VA_ARGS__)
#ifdef DEBUG
#define xfs_debug(mp, fmt, ...) \
	xfs_printk_index_wrap(_xfs_debug, KERN_DEBUG, mp, fmt, ##__VA_ARGS__)
#else
#define xfs_debug(mp, fmt, ...) do {} while (0)
#endif


extern __printf(3, 4)
void xfs_printk_level(
	const char *kern_level,
	const struct xfs_mount *mp,
	const char *fmt, ...);

#define xfs_printk_ratelimited(func, dev, fmt, ...)			\
do {									\
	static DEFINE_RATELIMIT_STATE(_rs,				\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);		\
	if (__ratelimit(&_rs))						\
		func(dev, fmt, ##__VA_ARGS__);				\
} while (0)

#define xfs_printk_once(func, dev, fmt, ...)			\
	DO_ONCE_LITE(func, dev, fmt, ##__VA_ARGS__)

#define xfs_emerg_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_emerg, dev, fmt, ##__VA_ARGS__)
#define xfs_alert_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_alert, dev, fmt, ##__VA_ARGS__)
#define xfs_crit_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_crit, dev, fmt, ##__VA_ARGS__)
#define xfs_err_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_err, dev, fmt, ##__VA_ARGS__)
#define xfs_warn_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_warn, dev, fmt, ##__VA_ARGS__)
#define xfs_notice_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_notice, dev, fmt, ##__VA_ARGS__)
#define xfs_info_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_info, dev, fmt, ##__VA_ARGS__)
#define xfs_debug_ratelimited(dev, fmt, ...)				\
	xfs_printk_ratelimited(xfs_debug, dev, fmt, ##__VA_ARGS__)

#define xfs_warn_once(dev, fmt, ...)				\
	xfs_printk_once(xfs_warn, dev, fmt, ##__VA_ARGS__)
#define xfs_notice_once(dev, fmt, ...)				\
	xfs_printk_once(xfs_notice, dev, fmt, ##__VA_ARGS__)
#define xfs_info_once(dev, fmt, ...)				\
	xfs_printk_once(xfs_info, dev, fmt, ##__VA_ARGS__)

void assfail(struct xfs_mount *mp, char *expr, char *f, int l);
void asswarn(struct xfs_mount *mp, char *expr, char *f, int l);

extern void xfs_hex_dump(const void *p, int length);

void xfs_buf_alert_ratelimited(struct xfs_buf *bp, const char *rlmsg,
			       const char *fmt, ...);

#endif	/* __XFS_MESSAGE_H */

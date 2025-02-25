# $OpenBSD: Makefile,v 1.23 2021/10/03 22:01:48 dv Exp $

BTRACE?=		 /usr/sbin/btrace
ALLOWDT!=		sysctl -n kern.allowdt

# scripts that don't need /dev/dt
BT_LANG_SCRIPTS=	arithm beginend boolean comments delete exit \
			histempty if \
			map mapclear mapempty mapsyntax mapzero map-unnamed \
			maxoperand min+max+sum multismts nsecs+var \
			precedence print read-map-after-clear staticv-empty \
			syntaxerror

BT_ARG_LANG_SCRIPTS=	staticv str

# scripts that use kernel probes
BT_KERN_SCRIPTS=	multiprobe

REGRESS_EXPECTED_FAILURES=	run-maxoperand

.for b in ${BT_LANG_SCRIPTS}
REGRESS_TARGETS+=		run-$b
run-$b:
	cd ${.CURDIR} && ${BTRACE} $b.bt 2>&1 | diff -u $b.ok /dev/stdin
.endfor

.for b in ${BT_ARG_LANG_SCRIPTS}
REGRESS_TARGETS+=		run-$b
run-$b:
	cat ${.CURDIR}/$b.args | xargs ${BTRACE} ${.CURDIR}/$b.bt 2>&1 | \
		diff -u ${.CURDIR}/$b.ok /dev/stdin
.endfor

.for b in ${BT_KERN_SCRIPTS}
REGRESS_TARGETS+=		run-$b
REGRESS_ROOT_TARGETS+=		run-$b
run-$b:
.if ${ALLOWDT}
	${SUDO} ${BTRACE} ${.CURDIR}/$b.bt 2>&1 | \
		diff -u ${.CURDIR}/$b.ok /dev/stdin
.else
	@echo SKIPPED
.endif
.endfor

.include <bsd.regress.mk>

/**************************************************************************
 *
 *  Copyright 2013, Roger Brown
 *
 *  This file is part of Roger Brown's Toolkit.
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

#ifdef __cplusplus
#	ifdef HAVE_CONFIG_HPP
#		include <config.hpp>
#	else
#		ifdef HAVE_CONFIG_H
#			include <config.h>
#		endif
#	endif
#else
#	ifdef HAVE_CONFIG_H
#		include <config.h>
#	endif
#endif
#define MAINLINE	 				int main(int argc,char **argv)

#define COMPLETE_PROGRAM 			MAINLINE { return argv && !argc; }

#ifdef LIST_OPTIONS
HAVE_OS2_H							"Looking for <os2.h>"
HAVE_PTHREAD_H						"Looking for <pthread.h>"
HAVE_SYS_TYPES_H					"Looking for <sys/types.h>"
HAVE_LIMITS_H						"Looking for <limits.h>"
HAVE_SIGNAL_H						"Looking for <signal.h>"
HAVE_POSIX_SIGWAIT					"Looking for sigwait()"
_POSIX_PTHREAD_SEMANTICS			"Looking for _POSIX_PTHREAD_SEMANTICS"
HAVE_STDIO_H						"Looking for <stdio.h>"
HAVE_STDARG_H						"Looking for <stdarg.h>"
HAVE_STDINT_H						"Looking for <stdint.h>"
HAVE_INTTYPES_H						"Looking for <inttypes.h>"
HAVE_WCHAR_H						"Looking for <wchar.h>"
HAVE_DLFCN_H						"Looking for <dlfcn.h>"
HAVE_DL_H							"Looking for <dl.h>"
HAVE_SYS_LDR_H						"Looking for <sys/ldr.h>"
HAVE_MACHO_DYLD_H					"Looking for <mach-o/dyld.h>"
HAVE_UNISTD_H						"Looking for <unistd.h>"
HAVE_ERRNO_H						"Looking for <errno.h>"
HAVE_POLL_H							"Looking for <poll.h>"
HAVE_GRP_H							"Looking for <grp.h>"
HAVE_FCNTL_H						"Looking for <fcntl.h>"
HAVE_MEMORY_H						"Looking for <memory.h>"
HAVE_SETJMP_H						"Looking for <setjmp.h>"
HAVE_SETJMPEX_H						"Looking for <setjmpex.h>"
HAVE_STRING_H						"Looking for <string.h>"
HAVE_STRINGS_H						"Looking for <strings.h>"
HAVE_MATH_H							"Looking for <math.h>"
HAVE_SIGINFO_H						"Looking for <siginfo.h>"
HAVE_SYS_POLL_H						"Looking for <sys/poll.h>"
HAVE_SYS_SELECT_H					"Looking for <sys/select.h>"
HAVE_SYS_TIME_H						"Looking for <sys/time.h>"
HAVE_SYS_IOCTL_H					"Looking for <sys/ioctl.h>"
HAVE_SYS_FILE_H						"Looking for <sys/file.h>"
HAVE_SYS_FCNTL_H					"Looking for <sys/fcntl.h>"
HAVE_SYS_UIO_H						"Looking for <sys/uio.h>"
HAVE_SYS_RANDOM_H					"Looking for <sys/random.h>"
HAVE_NL_TYPES_H						"Looking for <nl_types.h>"
HAVE_LANGINFO_H						"Looking for <langinfo.h>"
HAVE_LANGINFO_CODESET				"Looking for CODESET"
HAVE_IOSTREAM_H						"Looking for <iostream.h>"
HAVE_IOSTREAM						"Looking for <iostream>"
HAVE_SEH_TRY_EXCEPT					"Looking for __try/__except"
HAVE_SEH_TRY_FINALLY				"Looking for __try/__finally"
HAVE_DECLSPEC_DLLEXPORT				"Looking for __declspec(dllexport)"
HAVE_DECLSPEC_DLLIMPORT				"Looking for __declspec(dllimport)"
HAVE_DOUBLE_T						"Looking for double_t"
HAVE_LONG_DOUBLE					"Looking for long double"
HAVE_HOSTENT_DATA					"Looking for hostent_data"
HAVE_FPOS_T_SCALAR					"Looking for (long)fpos_t"
HAVE_VA_COPY						"Looking for va_copy()"
HAVE_VA_COPY_VOLATILE				"Looking for va_copy(volatile)"
HAVE_VA_LIST_ASSIGN					"Looking for va_list assign"
HAVE_VA_LIST_SCALAR					"Looking for va_list scalar"
HAVE_VA_LIST_OVERFLOW_ARG_AREA		"Looking for va_list.overflow_arg_area"
HAVE_VA_LIST_REG_SAVE_AREA			"Looking for va_list.reg_save_area"
HAVE_VA_LIST_GPR					"Looking for va_list.gpr"
HAVE_VA_LIST_FPR					"Looking for va_list.fpr"
HAVE_VA_LIST_GP_OFFSET				"Looking for va_list.gp_offset"
HAVE_VA_LIST_FP_OFFSET				"Looking for va_list.fp_offset"
HAVE_VA_LIST__OFFSET				"Looking for va_list._offset"
HAVE_VA_LIST__A0					"Looking for va_list._a0"
HAVE_VA_LIST___AP					"Looking for va_list.__ap"
HAVE_VA_LIST___VA_GP_OFFSET			"Looking for va_list.__va_gp_offset"
HAVE_VA_LIST___VA_FP_OFFSET			"Looking for va_list.__va_fp_offset"
HAVE_VA_LIST___VA_OVERFLOW_ARG_AREA	"Looking for va_list.__va_overflow_arg_area"
HAVE_VA_LIST___VA_REG_SVE_AREA		"Looking for va_list.__va_reg_sve_area"
HAVE_VA_LIST___STACK				"Looking for va_list.__stack"
HAVE_VA_LIST___GR_TOP				"Looking for va_list.__gr_top"
HAVE_VA_LIST___VR_TOP				"Looking for va_list.__vr_top"
HAVE_VA_LIST___GR_OFFS				"Looking for va_list.__gr_offs"
HAVE_VA_LIST___VR_OFFS				"Looking for va_list.__vr_offs"
HAVE___VA_REGSAVE_T					"Looking for typedef struct __va_regsave_t"
HAVE_VA_END_EMPTY					"Looking for va_end(ignored)"
HAVE_VA_ARG_ASSIGN					"Looking for va_arg assign"
HAVE_VA_ARG_VOLATILE				"Looking for va_arg volatile"
HAVE_MEMMOVE						"Looking for memmove()"
HAVE_STRCASECMP						"Looking for strcasecmp()"
HAVE_STRICMP						"Looking for stricmp()"
HAVE__STRICMP						"Looking for _stricmp()"
HAVE_SNPRINTF						"Looking for snprintf()"
HAVE__SNPRINTF						"Looking for _snprintf()"
HAVE_VSNPRINTF						"Looking for vsnprintf()"
HAVE__VSNPRINTF						"Looking for _vsnprintf()"
HAVE_INT_SPRINTF					"Looking for int sprintf()"
HAVE_INT_VSPRINTF					"Looking for int vsprintf()"
HAVE_PTR_SPRINTF					"Looking for char *sprintf()"
HAVE_PTR_VSPRINTF					"Looking for char *vsprintf()"
HAVE_SWPRINTF_ISO					"Looking for ISO style swprintf()"
HAVE_SWPRINTF						"Looking for swprintf()"
HAVE_STRTOIMAX						"Looking for strtoimax()"
HAVE_TMPFILE						"Looking for tmpfile()"
HAVE_RAISE							"Looking for raise()"
HAVE_SIGINTERRUPT					"Looking for siginterrupt()"
HAVE_PSIGNAL						"Looking for psignal()"
HAVE_SA_HANDLER_DEFAULT_EMPTY		"Looking for (*sa_handler)()"
HAVE_SA_HANDLER_DEFAULT_INT			"Looking for (*sa_handler)(int)"
HAVE_SA_HANDLER_DEFAULT_KANDR		"Looking for (*sa_handler)(int) K&R"
HAVE_SA_HANDLER_INT_INT				"Looking for int (*sa_handler)(int)"
HAVE_SA_HANDLER_VOID_EMPTY			"Looking for void (*sa_handler)()"
HAVE_SA_HANDLER_VOID_VOID			"Looking for void (*sa_handler)(void)"
HAVE_SA_HANDLER_VOID_INT			"Looking for void (*sa_handler)(int)"
HAVE_SA_HANDLER_VOID_KANDR			"Looking for void (*sa_handler)(int) K&R"
HAVE_ATEXIT_VOID					"Looking for atexit(void (*)(void))"
HAVE_ATEXIT_INT						"Looking for atexit((*)())"
HAVE_ATEXIT							"Looking for atexit()"
HAVE_STRERROR						"Looking for strerror()"
HAVE_PERROR							"Looking for perror()"
HAVE_IOCTL_FIONBIO					"Looking for ioctl(FIONBIO)"
HAVE_FCNTL_F_SETFL_FNDELAY			"Looking for fcntl(F_SETFL,FNDELAY)"
HAVE_FCNTL_F_SETFL_O_NDELAY			"Looking for fcntl(F_SETFL,O_NDELAY)"
HAVE_DLOPEN							"Looking for dlopen()"
HAVE_PTHREAD_ATFORK					"Looking for pthread_atfork()"
HAVE_PTHREAD_CANCEL					"Looking for pthread_cancel()"
HAVE_PTHREAD_KILL					"Looking for pthread_kill()"
HAVE_PTHREAD_T_SCALAR				"Looking for scalar pthread_t"
HAVE_PTHREAD_ADDR_T					"Looking for pthread_addr_t"
HAVE_PTHREAD_KEY_CREATE				"Looking for pthread_key_create()"
HAVE_PTHREAD_KEY_DELETE				"Looking for pthread_key_delete()"
HAVE_PTHREAD_KEYCREATE				"Looking for pthread_keycreate()"
HAVE_PTHREAD_GETSPECIFIC_STD		"Looking for pthread_getspecific() - Standard"
HAVE_PTHREAD_GETSPECIFIC_D4			"Looking for pthread_getspecific() - Draft4"
HAVE_PTHREAD_ATTR_DEFAULT			"Looking for pthread_attr_default"
HAVE_PTHREAD_CONDATTR_DEFAULT		"Looking for pthread_condattr_default"
HAVE_PTHREAD_MUTEXATTR_DEFAULT		"Looking for pthread_mutexattr_default"
HAVE_WAITFORSINGLEOBJECTEX			"Looking for WaitForSingleObjectEx()"
USE_PTHREAD_ONCE_INIT_BRACES0		"Looking for PTHREAD_ONCE_INIT"
USE_PTHREAD_ONCE_INIT_BRACES1		"Looking for {PTHREAD_ONCE_INIT}"
USE_PTHREAD_ONCE_INIT_BRACES2		"Looking for {{PTHREAD_ONCE_INIT}}"
USE_PTHREAD_MUTEX_INITIALIZER_BRACES0		"Looking for PTHREAD_MUTEX_INITIALIZER"
USE_PTHREAD_MUTEX_INITIALIZER_BRACES1		"Looking for {PTHREAD_MUTEX_INITIALIZER}"
USE_PTHREAD_MUTEX_INITIALIZER_BRACES2		"Looking for {{PTHREAD_MUTEX_INITIALIZER}}"
USE_PTHREAD_COND_INITIALIZER_BRACES0		"Looking for PTHREAD_COND_INITIALIZER"
USE_PTHREAD_COND_INITIALIZER_BRACES1		"Looking for {PTHREAD_COND_INITIALIZER}"
USE_PTHREAD_COND_INITIALIZER_BRACES2		"Looking for {{PTHREAD_COND_INITIALIZER}}"
#elif defined(TRY_HAVE_SYS_TIME_H)
#	include <sys/time.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_RANDOM_H)
#	include <sys/random.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_UIO_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/uio.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_NL_TYPES_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <nl_types.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_LANGINFO_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_NL_TYPES_H
#		include <nl_types.h>
#	endif
#	include <langinfo.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_LANGINFO_CODESET)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_NL_TYPES_H
#		include <nl_types.h>
#	endif
#	ifdef HAVE_LANGINFO_H
#		include <langinfo.h>
#	endif
	MAINLINE
	{ nl_langinfo(CODESET); return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_GRP_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <grp.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_DLFCN_H)
#	ifdef BUILD_STATIC
		#error BUILD_STATIC
#	else
#		ifdef HAVE_SYS_TYPES_H
#			include <sys/types.h>
#		endif
#		include <dlfcn.h>
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_HAVE_MACHO_DYLD_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <mach-o/dyld.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_DL_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <dl.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_LDR_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/ldr.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_POLL_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <poll.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_MEMORY_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <memory.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SETJMP_H)
#	include <setjmp.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SETJMPEX_H)
#	include <setjmpex.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_FCNTL_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <fcntl.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_TYPES_H)
#	include <sys/types.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SIGNAL_H)
#	include <signal.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SIGINFO_H)
#	ifdef HAVE_SIGNAL_H
#		include <signal.h>
#	endif
#	include <siginfo.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_STDARG_H)
#	include <stdarg.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_STDINT_H)
#	include <stdint.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_INTTYPES_H)
#	include <inttypes.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_LIMITS_H)
#	include <limits.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_STDIO_H)
#	include <stdio.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_WCHAR_H)
#	include <wchar.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_ERRNO_H)
#	include <errno.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_UNISTD_H)
#	include <unistd.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_STRING_H)
#	include <string.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_STRINGS_H)
#	include <strings.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_MATH_H)
#	include <math.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_POLL_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/poll.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_SELECT_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/select.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_IOCTL_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/ioctl.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_FILE_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/file.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_SYS_FCNTL_H)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/fcntl.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_PTHREAD_H)
#	include <pthread.h>
	MAINLINE
	{ void *pv;	pthread_t t=pthread_self(); 
		return argc && argv && pthread_join(t,&pv);	}
#elif defined(TRY_HAVE_IOSTREAM_H)
#	include <iostream.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_IOSTREAM)
#	include <iostream>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_STRERROR)
#	ifdef HAVE_STRING_H
#		include <string.h>
#	endif
#	include <errno.h>
	MAINLINE
	{   const char *p=strerror(errno);
		return argc && argv && p; }
#elif defined(TRY_HAVE_PERROR)
#	include <stdio.h>
	MAINLINE
	{   perror(argv[0]);
		return argc; }
#elif defined(TRY_HAVE_IOCTL_FIONBIO)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_SYS_IOCTL_H
#		include <sys/ioctl.h>
#	endif
#	ifdef HAVE_UNISTD_H
#		include <unistd.h>
#	endif
	MAINLINE
	{ int ul=argc; return argv && ioctl(ul,FIONBIO,(char *)&ul); }
#elif defined(TRY_HAVE_FCNTL_F_SETFL_FNDELAY)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_UNISTD_H
#		include <unistd.h>
#	endif
#	ifdef HAVE_FCNTL_H
#		include <fcntl.h>
#	endif
	MAINLINE
	{ return argc && argv && fcntl(0,F_SETFL,FNDELAY); }
#elif defined(TRY_HAVE_FCNTL_F_SETFL_O_NDELAY)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_UNISTD_H
#		include <unistd.h>
#	endif
#	ifdef HAVE_FCNTL_H
#		include <fcntl.h>
#	endif
	MAINLINE
	{ return argc && argv && fcntl(0,F_SETFL,O_NDELAY); }
#elif defined(TRY_HAVE_ATEXIT_VOID)
#	include <stdlib.h>
	static void myexit(void) {}
	MAINLINE
	{ atexit(myexit); return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_ATEXIT_INT)
#	include <stdlib.h>
	static myexit() {}
	MAINLINE
	{ atexit(myexit); return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_ATEXIT)
#	if defined(HAVE_ATEXIT_INT)||defined(HAVE_ATEXIT_VOID)
		COMPLETE_PROGRAM
#	else
		#error no recognized atexit
#	endif
#elif defined(TRY_HAVE_SEH_TRY_EXCEPT)
	MAINLINE
	{ __try {} __except(1) {} return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SEH_TRY_FINALLY)
	MAINLINE
	{ __try {} __finally {} return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_DECLSPEC_DLLEXPORT)
#	ifdef BUILD_STATIC
		#error BUILD_STATIC
#	endif
	__declspec(dllexport) int myfunc(int x) { return x; }
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_DECLSPEC_DLLIMPORT)
#	ifdef BUILD_STATIC
		#error BUILD_STATIC
#	endif
	__declspec(dllimport) int myfunc(int);
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_LONG_DOUBLE)
	long double my_ld=1.2;
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_DOUBLE_T)
#	ifdef HAVE_MATH_H
#		include <math.h>
#	endif
	double_t my_ld=1.2;
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_WAITFORSINGLEOBJECTEX)
#	include <windows.h>
	MAINLINE
	{ return WaitForSingleObjectEx((HANDLE)0,INFINITE,TRUE); }
#elif defined(TRY_HAVE_TMPFILE)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <stdio.h>
	MAINLINE
	{ FILE *fp=tmpfile(); return (argc && argv && fp) ? 0 : 1; }
#elif defined(TRY_HAVE_RAISE)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	MAINLINE
	{ return (argc && argv) ? raise(SIGINT) : 1; }
#elif defined(TRY_HAVE_PSIGNAL)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_SIGNAL_H
#		include <signal.h>
#	endif
#	ifdef HAVE_SIGINFO_H
#		include <siginfo.h>
#	endif
	MAINLINE
	{ 	psignal(argc,argv[0]);
		return (argc && argv); }
#elif defined(TRY_HAVE_SIGINTERRUPT)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	ifdef HAVE_SIGNAL_H
#		include <signal.h>
#	endif
	MAINLINE
	{ 	siginterrupt(argc,SIGINT);
		return (argc && argv); }
#elif defined(TRY_HAVE_SA_HANDLER_DEFAULT_EMPTY)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static handler() {}
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (sa.sa_handler && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_DEFAULT_INT)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static handler(int num) { if (num) { } }
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (sa.sa_handler && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_DEFAULT_KANDR)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static handler(num) int num; { if (num) { } }
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (sa.sa_handler && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_VOID_KANDR)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static void handler(num) int num; { if (num) { } }
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (sa.sa_handler && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_INT_INT)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static int handler(int num) { return num; }
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (sa.sa_handler && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_VOID_EMPTY)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static void handler() {}
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (sa.sa_handler && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_VOID_VOID)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static void handler(void) {}
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (argc && argv && sa.sa_handler) ? 0 : 1; }
#elif defined(TRY_HAVE_SA_HANDLER_VOID_INT)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	static void handler(int num) { if (num) {} }
	MAINLINE
	{ struct sigaction sa; sa.sa_handler=handler;
	return (argc && argv && sa.sa_handler) ? 0 : 1; }
#elif defined(TRY_HAVE_MEMMOVE)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <stdlib.h>
#	include <string.h>
	MAINLINE
	{ static const char src[]={'A'}; char dst[sizeof(src)]; 
	memmove(dst,src,sizeof(dst)); return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_STRCASECMP)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <stdlib.h>
#	ifdef HAVE_STRING_H
#		include <string.h>
#	endif
#	ifdef HAVE_STRINGS_H
#		include <strings.h>
#	endif
	MAINLINE
	{ return (argc && argv) ? strcasecmp("A","a") : 1; }
#elif defined(TRY_HAVE_STRICMP)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <stdlib.h>
#	ifdef HAVE_STRING_H
#		include <string.h>
#	endif
	MAINLINE
	{ return (argc && argv) ? stricmp("A","a") : 1; }
#elif defined(TRY_HAVE__STRICMP)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <stdlib.h>
#	ifdef HAVE_STRING_H
#		include <string.h>
#	endif
	MAINLINE
	{ return (argc && argv) ? _stricmp("A","a") : 1; }
#elif defined(TRY_HAVE_INT_SPRINTF)
#	include <stdio.h>
	MAINLINE
	{ char buf[256]; int i=sprintf(buf,"%d,%p",argc,argv); return !i; }
#elif defined(TRY_HAVE_INT_VSPRINTF)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
#	include <stdio.h>
	static int func(char *buf,char *f,...)
	{ int rc; va_list ap; va_start(ap,f); 
	  rc=vsprintf(buf,f,ap); va_end(ap); return rc; }
	MAINLINE
	{ char buf[256]; int i=func(buf,"%d,%p",argc,argv); return !i; }
#elif defined(TRY_HAVE_PTR_SPRINTF)
#	include <stdio.h>
	MAINLINE
	{ char buf[256]; char *p=sprintf(buf,"%d,%p",argc,argv); return p ? 0 : 1; }
#elif defined(TRY_HAVE_PTR_VSPRINTF)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
#	include <stdio.h>
	static char * func(char *buf,char *f,...)
	{ char *rc; va_list ap; va_start(ap,f); 
	  rc=vsprintf(buf,f,ap); va_end(ap); return rc; }
	MAINLINE
	{ char buf[256]; char *p=func(buf,"%d,%p",argc,argv); return p ? 0 : 1; }
#elif defined(TRY_HAVE_HOSTENT_DATA)
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <netdb.h>
	MAINLINE
	{ static struct hostent_data data;
	  return (sizeof(data) && argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_DLOPEN)
#	ifdef BUILD_STATIC
		#error BUILD_STATIC
#	else
#		ifdef HAVE_SYS_TYPES_H
#			include <sys/types.h>
#		endif
#		include <dlfcn.h>
		MAINLINE
		{ return dlopen(argv[0],argc) ? 0 : 1; }
#	endif
#elif defined(TRY_HAVE_OS2_H)
#	include <os2.h>
	COMPLETE_PROGRAM
#elif defined(TRY_HAVE_FPOS_T_SCALAR)
#	include <stdio.h>
	MAINLINE
	{ static fpos_t fpt; long val=(long)fpt; return val; }
#elif defined(TRY_HAVE_STRTOIMAX)
#	include <stdio.h>
#	ifdef HAVE_INTTYPES_H
#		include <inttypes.h>
#	endif
#	ifdef HAVE_STDINT_H
#		include <stdint.h>
#	endif
	MAINLINE
	{ intmax_t i=strtoimax(argv[0],argv,argc);
	  return i ? 0 : 1;	}
#elif defined(TRY_HAVE_SNPRINTF)
#	include <stdio.h>
	MAINLINE
	{ char buf[256];
	  int i=snprintf(buf,sizeof(buf),"%d,%p",argc,argv);
	  return i ? 0 : 1;	}
#elif defined(TRY_HAVE_SWPRINTF_ISO)
#	include <stdio.h>
#	ifdef HAVE_WCHAR_H
#		include <wchar.h>
#	endif
	MAINLINE
	{ wchar_t buf[256];
	  static const wchar_t fmt[]={0};
	  int i=swprintf(buf,(sizeof(buf)/sizeof(buf[0])),fmt,argc,argv);
	  return i ? 0 : 1;	}
#elif defined(TRY_HAVE_SWPRINTF)
#	include <stdio.h>
#	ifdef HAVE_WCHAR_H
#		include <wchar.h>
#	endif
	MAINLINE
	{ wchar_t buf[256];
	  static const wchar_t fmt[]={0};
#ifdef HAVE_SWPRINTF_ISO
	  int i=swprintf(buf,(sizeof(buf)/sizeof(buf[0])),fmt,argc,argv);
#else
	  int i=swprintf(buf,fmt,argc,argv);
#endif
	  return i ? 0 : 1;	}
#elif defined(TRY_HAVE__SNPRINTF)
#	include <stdio.h>
	MAINLINE
	{ char buf[256];
	  int i=_snprintf(buf,sizeof(buf),"%d,%p",argc,argv);
	  return i ? 0 : 1;	}
#elif defined(TRY_HAVE_VSNPRINTF)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
#	include <stdio.h>
	static int func(va_list ap)
	{
		char buf[256];
		int i=vsnprintf(buf,sizeof(buf),"%d",ap);
		return i;
	}
	static int func2(int argc,...)
	{
	  int i;
	  va_list ap;
	  va_start(ap,argc);
	  i=func(ap);
	  va_end(ap);
	  return i;
	}
	MAINLINE
	{ func2(argc,argv);
	  return 0; }
#elif defined(TRY_HAVE__VSNPRINTF)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
#	include <stdio.h>
	static int func(va_list ap)
	{
		char buf[256];
		int i=_vsnprintf(buf,sizeof(buf),"%d",ap);
		return i;
	}
	static int func2(int argc,...)
	{
	  int i;
	  va_list ap;
	  va_start(ap,argc);
	  i=func(ap);
	  va_end(ap);
	  return i;
	}
	MAINLINE
	{ func2(argc,argv);
	  return 0; }
#elif defined(TRY_HAVE_VA_END_EMPTY)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ va_end(ignored-argument); return (argc && argv) ? 0 : 1; }
#elif defined(TRY_HAVE_VA_COPY)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	static int func1(int f,va_list ap1)
	{ va_list ap2; int i;
	va_copy(ap2,ap1);
	i=va_arg(ap2,int);
	va_end(ap2);
	return i+f; }
	static int func2(int f,...)
	{ va_list ap1;int i;
	va_start(ap1,f);
	i=func1(f,ap1);
	va_end(ap1);
	return i; }
	MAINLINE
	{ return func2(argc,argv); }
#elif defined(TRY_HAVE_VA_COPY_VOLATILE)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	static int func1(int f,va_list ap1)
	{ va_list volatile ap2; int i;
	va_copy(ap2,ap1);
	i=va_arg(ap2,int);
	va_end(ap2);
	return i+f; }
	static int func2(int f,...)
	{ va_list ap1;int i;
	va_start(ap1,f);
	i=func1(f,ap1);
	va_end(ap1);
	return i; }
	MAINLINE
	{ return func2(argc,argv); }
#elif defined(TRY_HAVE_VA_LIST_ASSIGN)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	static int func1(int f,va_list ap)
	{ va_list ap1=ap; return (f+va_arg(ap1,int)) ? 0: 1; }
	static int func2(int f,...)
	{ va_list ap1;int i;
	va_start(ap1,f);
	i=func1(f,ap1);
	va_end(ap1);
	return i; }
	MAINLINE
	{ return func2(argc,argv); }
#elif defined(TRY_HAVE_VA_ARG_ASSIGN)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	static int func2(int f,...)
	{ 	va_list ap;
		int i=0;
		char *p=(char *)0;
		double d=0.0;
		va_start(ap,f);
		va_arg(ap,int)=i;
		va_arg(ap,char *)=p;
		va_arg(ap,double)=d;
		va_end(ap);
	return 0; }
	MAINLINE
	{ return func2(argc,argv); }
#elif defined(TRY_HAVE_VA_ARG_VOLATILE)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	static int func2(va_list ap)
	{
#ifdef HAVE_VA_COPY_VOLATILE
		va_list volatile ap2;
		va_copy(ap2,ap);
#else
		va_list volatile ap2=ap;
#endif
		return va_arg(ap2,int);
	}
	static int func(int x,...)
	{
		va_list ap;
		va_start(ap,x);
		x=func2(ap);
		va_end(ap);
		return x;
	}

	MAINLINE
	{ return func(argc,argv); }
#elif defined(TRY_HAVE_VA_LIST_SCALAR)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ va_list ap=(va_list)0; return ap ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_VA_LIST_OVERFLOW_ARG_AREA)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].overflow_arg_area) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST_REG_SAVE_AREA)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].reg_save_area) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST_GPR)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].gpr) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST_FPR)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].fpr) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST_GP_OFFSET)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].gp_offset) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST_FP_OFFSET)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].fp_offset) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST__OFFSET)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap._offset) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST__A0)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap._a0) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___AP)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap.__ap) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___VA_GP_OFFSET)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].__va_gp_offset) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___VA_FP_OFFSET)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].__va_fp_offset) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___VA_OVERFLOW_ARG_AREA)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].__va_overflow_arg_area) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___VA_REG_SVE_AREA)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap[0].__va_reg_sve_area) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___STACK)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap.__stack) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___GR_TOP)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap.__gr_top) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___VR_TOP)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap.__vr_top) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___GR_OFFS)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap.__gr_offs) ? 1 : 0;}
#elif defined(TRY_HAVE_VA_LIST___VR_OFFS)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static va_list ap; return (argc && argv && ap.__vr_offs) ? 1 : 0;}
#elif defined(TRY_HAVE___VA_REGSAVE_T)
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	else
#		include <varargs.h>
#	endif
	MAINLINE
	{ static __va_regsave_t s; return (argc && argv && sizeof(s)) ? 1 : 0;}
#elif defined(TRY_HAVE_PTHREAD_ATFORK)
#	include <pthread.h>
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <unistd.h>
	static void wibble(void) {  }
	MAINLINE
	{ pthread_atfork(wibble,wibble,wibble); return 0; }
#elif defined(TRY_HAVE_PTHREAD_CANCEL)
#	include <pthread.h>
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
	MAINLINE
	{ pthread_cancel(pthread_self());
	pthread_testcancel(); return 0; }
#elif defined(TRY_HAVE_PTHREAD_KILL)
#	include <pthread.h>
#	ifdef HAVE_SYS_TYPES_H
#		include <sys/types.h>
#	endif
#	include <signal.h>
	MAINLINE
	{ pthread_kill(pthread_self(),SIGINT); return 0; }
#elif defined(TRY_HAVE_PTHREAD_T_SCALAR)
#	include <pthread.h>
	MAINLINE
	{ pthread_t tid=(pthread_t)0; return tid ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_ADDR_T)
#	include <pthread.h>
	static struct wibble { int x; } value;
	MAINLINE
	{ pthread_addr_t tid=(pthread_addr_t)(void *)&value; return tid ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_KEY_CREATE)
#	include <pthread.h>
	static void destr(void *pv) { if (pv) {} }
	static pthread_key_t key;
	MAINLINE
	{ return pthread_key_create(&key,destr) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_KEY_DELETE)
#	include <pthread.h>
	static pthread_key_t key;
	MAINLINE
	{ return pthread_key_delete(key) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_KEYCREATE)
#	include <pthread.h>
	static void destr(void *pv) { if (pv) {} }
	static pthread_key_t key;
	MAINLINE
	{ return pthread_keycreate(&key,destr) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_GETSPECIFIC_STD)
#	include <pthread.h>
	MAINLINE
	{	static pthread_key_t key;
		return pthread_getspecific(key) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_GETSPECIFIC_D4)
#	include <pthread.h>
	MAINLINE 
	{   static pthread_addr_t v;
		static pthread_key_t key;
		return pthread_getspecific(key,&v) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_ATTR_DEFAULT)
#	include <pthread.h>
	static void * mythread(void *pv) { return pv; }
	static pthread_t tid;
	MAINLINE
	{ return pthread_create(&tid,pthread_attr_default,mythread,argv) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_MUTEXATTR_DEFAULT)
#	include <pthread.h>
	static pthread_mutex_t mutex;
	MAINLINE
	{ return pthread_mutex_init(&mutex,pthread_mutexattr_default) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_HAVE_PTHREAD_CONDATTR_DEFAULT)
#	include <pthread.h>
	static pthread_cond_t cond;
	MAINLINE
	{ return pthread_cond_init(&cond,pthread_condattr_default) ? 1 : ((argc&&argv)?0:1);}
#elif defined(TRY_USE_PTHREAD_ONCE_INIT_BRACES0)
#	include <pthread.h>
	pthread_once_t x=PTHREAD_ONCE_INIT;
	COMPLETE_PROGRAM
#elif defined(TRY_USE_PTHREAD_ONCE_INIT_BRACES1)
#	ifdef USE_PTHREAD_ONCE_INIT_BRACES0
		#error USE_PTHREAD_ONCE_INIT_BRACES0 already defined
#	else
#		include <pthread.h>
		pthread_once_t x={PTHREAD_ONCE_INIT};
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_USE_PTHREAD_ONCE_INIT_BRACES2)
#	ifdef USE_PTHREAD_ONCE_INIT_BRACES0
		#error USE_PTHREAD_ONCE_INIT_BRACES0 already defined
#	elif defined(USE_PTHREAD_ONCE_INIT_BRACES1)
		#error USE_PTHREAD_ONCE_INIT_BRACES1 already defined
#	else
#		include <pthread.h>
		pthread_once_t x={{PTHREAD_ONCE_INIT}};
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_USE_PTHREAD_MUTEX_INITIALIZER_BRACES0)
#	include <pthread.h>
	pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER;
	COMPLETE_PROGRAM
#elif defined(TRY_USE_PTHREAD_MUTEX_INITIALIZER_BRACES1)
#	ifdef USE_PTHREAD_MUTEX_INITIALIZER_BRACES0
		#error USE_PTHREAD_MUTEX_INITIALIZER_BRACES0 already defined
#	else
#		include <pthread.h>
		pthread_mutex_t x={PTHREAD_MUTEX_INITIALIZER};
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_USE_PTHREAD_MUTEX_INITIALIZER_BRACES2)
#	ifdef USE_PTHREAD_MUTEX_INITIALIZER_BRACES0
		#error USE_PTHREAD_MUTEX_INITIALIZER_BRACES0 already defined
#	elif defined(USE_PTHREAD_MUTEX_INITIALIZER_BRACES1)
		#error USE_PTHREAD_MUTEX_INITIALIZER_BRACES1 already defined
#	else
#		include <pthread.h>
		pthread_mutex_t x={{PTHREAD_MUTEX_INITIALIZER}};
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_USE_PTHREAD_COND_INITIALIZER_BRACES0)
#	include <pthread.h>
	pthread_cond_t x=PTHREAD_COND_INITIALIZER;
	COMPLETE_PROGRAM
#elif defined(TRY_USE_PTHREAD_COND_INITIALIZER_BRACES1)
#	ifdef USE_PTHREAD_COND_INITIALIZER_BRACES0
		#error USE_PTHREAD_COND_INITIALIZER_BRACES0 already defined
#	else
#		include <pthread.h>
		pthread_cond_t x={PTHREAD_COND_INITIALIZER};
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_USE_PTHREAD_COND_INITIALIZER_BRACES2)
#	ifdef USE_PTHREAD_COND_INITIALIZER_BRACES0
		#error USE_PTHREAD_COND_INITIALIZER_BRACES0 already defined
#	elif defined(USE_PTHREAD_COND_INITIALIZER_BRACES1)
		#error USE_PTHREAD_COND_INITIALIZER_BRACES1 already defined
#	else
#		include <pthread.h>
		pthread_cond_t x={{PTHREAD_COND_INITIALIZER}};
		COMPLETE_PROGRAM
#	endif
#elif defined(TRY_HAVE_POSIX_SIGWAIT)
#	include <signal.h>
	MAINLINE
	{ sigset_t s; int i; sigemptyset(&s); argc=sigwait(&s,&i);
	return (argc && argv) ? 0 : 1;}
#elif defined(TRY__POSIX_PTHREAD_SEMANTICS)
#	ifdef HAVE_POSIX_SIGWAIT
		#error HAVE_POSIX_SIGWAIT already defined
#	else
#		define _POSIX_PTHREAD_SEMANTICS
#		include <signal.h>
		MAINLINE
		{ sigset_t s; int i; sigemptyset(&s); argc=sigwait(&s,&i);
		return (argc && argv) ? 0 : 1;}
#	endif
#elif defined(BUILD_CONFIG)
	static int xyz_config;
#else
	#error INVALID_OPTION
#endif

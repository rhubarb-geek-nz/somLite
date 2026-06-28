/**************************************************************************
 *
 *  Copyright 2008, Roger Brown
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

#include <rhbopt.h>
#ifdef HAVE_SYS_TYPES_H
#	include <sys/types.h>
#endif
#include <time.h>
#include <rhbsomex.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <winsock.h>
#else
	#include <signal.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/wait.h>
#endif

#if defined(USE_PTHREADS) && defined(HAVE_PTHREAD_CANCEL)
static int thread_waiting;
static pthread_cond_t thread_waiting_cond
#ifdef RHBOPT_PTHREAD_COND_INITIALIZER
	=RHBOPT_PTHREAD_COND_INITIALIZER
#endif
	;
#endif

#ifdef _WIN32
	int gethostid(void);
/*	int getdomainname(char *,int);*/
	#define sleep(x)    Sleep(x * 1000)
#endif


#if defined(USE_PTHREADS)
static pthread_cond_t cond_1,cond_2,cond_3,cond_4;
static pthread_mutex_t mutex;

#if defined( HAVE_PTHREAD_CANCEL)
static pthread_key_t thread_tls;
static int was_TLS_cleanup,was_local_cleanup;
static void cleanup_tls(void *x)
{
	somPrintf("Cleanup TLS\n");
	pthread_mutex_lock(&mutex);
	somPrintf("Cleanup TLS locked\n");
	was_TLS_cleanup++;
	pthread_cond_signal(&cond_4);
	somPrintf("Cleanup TLS signalled\n");
	pthread_mutex_unlock(&mutex);
	somPrintf("Cleanup TLS unlocked\n");
}
static void * somtest0_thread_wait(void *);
#endif
static void * thread_run(void *);

int test_threads(Environment *ev)
{
	pthread_t thr;
	void *pv;
	int i;

	somPrintf("thread testing\n");

	pthread_cond_init(&cond_1,RHBOPT_pthread_condattr_default);
	pthread_cond_init(&cond_2,RHBOPT_pthread_condattr_default);
	pthread_cond_init(&cond_3,RHBOPT_pthread_condattr_default);
	pthread_cond_init(&cond_4,RHBOPT_pthread_condattr_default);
	pthread_mutex_init(&mutex,RHBOPT_pthread_mutexattr_default);

	pthread_mutex_lock(&mutex);

	pthread_create(&thr,RHBOPT_pthread_attr_default,thread_run,0);

	somPrintf("waiting for 1\n");
	pthread_cond_wait(&cond_1,&mutex);

	pthread_cond_signal(&cond_2);

	pthread_mutex_unlock(&mutex);

	somPrintf("calling 'pthread_join()'\n");

	i=pthread_join(thr,&pv);

	somPrintf("pthread_join() returned %d\n",i);

	if (i != 0)
	{
		fprintf(stderr,"pthread_join not working correctly\n");
		fflush(stderr);
#ifdef __AIX__
		/* we know that the AIX fails on this,
			let's catch other architectures with same problem */
#else
		return 1;
#endif
	}

	somPrintf("testing pthread_equal\n");

	i=pthread_equal(pthread_self(),thr);

	somPrintf("pthread_equal returned %d (should be zero)\n",i);

	somPrintf("clearing up bits\n");

#ifdef HAVE_PTHREAD_CANCEL
	#ifdef HAVE_PTHREAD_KEY_CREATE
		pthread_key_create(&thread_tls,cleanup_tls);
	#else
		pthread_keycreate(&thread_tls,cleanup_tls);
	#endif


	#if !defined(RHBOPT_PTHREAD_COND_INITIALIZER)
	pthread_cond_init(&thread_waiting_cond,RHBOPT_pthread_condattr_default);
	#endif

	somPrintf("Trying to get mutex\n");

	pthread_mutex_lock(&mutex);

	pthread_create(&thr,RHBOPT_pthread_attr_default,somtest0_thread_wait,0);

	while (!thread_waiting)
	{
		somPrintf("thread is not waiting...\n");

		pthread_cond_wait(&thread_waiting_cond,&mutex);
	}

	pthread_mutex_unlock(&mutex);

	somPrintf("canceling thread....\n");

	pthread_cancel(thr);

	somPrintf("Have cancelled thread....\n");

	pthread_mutex_lock(&mutex);

	somPrintf("Relocked for reaping....\n");

	while (!was_local_cleanup)
	{
		time_t now;
		struct timespec ts;
		time(&now);
		ts.tv_sec=now+5;
		ts.tv_nsec=0;

		somPrintf("waiting for local cleanup\n");

		pthread_cond_timedwait(&cond_3,&mutex,&ts);
	}

	while (!was_TLS_cleanup)
	{
		time_t now;
		struct timespec ts;
		time(&now);
		ts.tv_sec=now+5;
		ts.tv_nsec=0;

		somPrintf("waiting for TLS cleanup\n");

		pthread_cond_timedwait(&cond_4,&mutex,&ts);
	}

	somPrintf("thread is cancelled\n");

	pthread_mutex_unlock(&mutex);

	somPrintf("Waiting for thread....\n");

	i=pthread_join(thr,&pv);

	somPrintf("pthread_join() returned %d\n",i);

	#if !defined(RHBOPT_PTHREAD_COND_INITIALIZER)
	pthread_cond_destroy(&thread_waiting_cond);
	#endif
#endif

	pthread_mutex_lock(&mutex);
	pthread_cond_destroy(&cond_1);
	pthread_cond_destroy(&cond_2);
	pthread_cond_destroy(&cond_3);
	pthread_cond_destroy(&cond_4);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	somPrintf("thread test done\n");

	return i;
}

static void * thread_run(void *pv)
{
	Environment ev;

	SOM_InitEnvironment(&ev);

	somPrintf("thread started\n");
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&cond_1);
	somPrintf("waiting for 2\n");
	pthread_cond_wait(&cond_2,&mutex);
	pthread_mutex_unlock(&mutex);

	somPrintf("setting SOM exception\n");
	somSetException(&ev,SYSTEM_EXCEPTION,"::Hello::World",0);
	somPrintf("thread ending\n");

	SOM_UninitEnvironment(&ev);

	return 0;
}
#endif

#if defined(USE_PTHREADS)
#ifdef HAVE_PTHREAD_CANCEL
static void thread_cleanup(void *pv)
{
	somPrintf("thread cleanup called\n");
	was_local_cleanup++;
	pthread_cond_signal(&cond_3);
	pthread_mutex_unlock(&mutex);
	somPrintf("mutex unlocked in cleanup\n");
}
static void *somtest0_thread_wait(void *pv)
{
#ifdef HAVE_PTHREAD_ADDR_T
	pthread_setspecific(thread_tls,(pthread_addr_t)(void *)"Hello World");
#else
	pthread_setspecific(thread_tls,"Hello World");
#endif
	somPrintf("thread started\n");

	pthread_cleanup_push(thread_cleanup,&mutex);
	pthread_mutex_lock(&mutex);
	somPrintf("telling parent...\n");
	thread_waiting=1;
	pthread_cond_signal(&thread_waiting_cond);
	somPrintf("thread going to sleep....\n");
	while (1)
	{
		time_t now;
		struct timespec ts;
		time(&now);
		ts.tv_sec=now+5;
		ts.tv_nsec=0;
		if (!pthread_cond_timedwait(&cond_1,&mutex,&ts))
		{
			break;
		}
		somPrintf("now calling test cancel(1)....\n");
		pthread_testcancel();
	}
	somPrintf("now calling test cancel(2)....\n");
	pthread_testcancel();
	pthread_cleanup_pop(1);
	somPrintf("thread returned normally after cleanup\n");
	return 0;
}
#endif
#endif

void test_callstyle(SOMClassMgr SOMSTAR mgr)
{
somTD_SOMClassMgr_somFindClass td;
int i;
SOMClass SOMSTAR f;

	i=10;

	while (i--)
	{
		td=(somTD_SOMClassMgr_somFindClass)somResolve(mgr,SOMClassMgrClassData.somFindClass);

		if (td)
		{
			f=td(mgr,0,1,2);

			RHBOPT_unused(f);
		}
	}

#ifdef SOM_METHOD_THUNKS
	{
		somId id;

		somPrintf("_WIN32 is %d\n",(int)_WIN32);
		somPrintf("_M_IX86 is %d\n",(int)_M_IX86);
		somPrintf("_MSC_VER is %d\n",(int)_MSC_VER);

		id=somIdFromString("SOMObject");
		td=(somTD_SOMClassMgr_somFindClass)SOMClassMgrClassData.somFindClass;
		f=td(mgr,id,1,2);
		if (f) 
		{
			SOMObject SOMSTAR o;
			somTD_SOMClass_somNew td;
			char *p;
			somTD_SOMObject_somGetClassName td2;

			td=(somTD_SOMClass_somNew)SOMClassClassData.somNew;
			o=td(f);
			td2=(somTD_SOMObject_somGetClassName)SOMObjectClassData.somGetClassName;
			p=td2(o);

			SOM_Resolve(o,SOMObject,somFree)(o);
			}
		SOMFree(id);
	}
#endif
}

int test_lookup(SOMClassMgr SOMSTAR mgr)
{
char *p;
char *id="somGetClassName";
somTD_SOMObject_somGetClassName td;

	td=(somTD_SOMObject_somGetClassName)SOMClass_somLookupMethod(mgr->mtab->classObject,&id);

	p=td(mgr);	

	RHBOPT_unused(p);

	return 0;
}


int test_types(void)
{
	Environment ev;

	SOM_InitEnvironment(&ev);

#ifdef _WIN32
	{
		__int64 l;
		l=0;
		somPrintf("length of __int64 is %d\n",sizeof(l));
	}

	{
		long double x;
		x=0;
		somPrintf("length of long double is %d\n",sizeof(x));
	}
#endif

	SOM_UninitEnvironment(&ev);

	return 0;
}

static int main_somtest0(SOMClassMgr SOMSTAR clsMgr,int argc,char **argv)
{
	Environment ev;

	if (!clsMgr) return 1;

#ifdef _WIN32	
	somPrintf("_WIN32 is %d\n",(int)_WIN32);
#endif
#ifdef _WIN64	
	somPrintf("_WIN64 is %d\n",(int)_WIN64);
#endif
#ifdef _M_IX86
	somPrintf("_M_IX86 is %d\n",(int)_M_IX86);
#endif
#ifdef _MSC_VER
	somPrintf("_MSC_VER is %d\n",(int)_MSC_VER);
#endif
#ifdef __AIX__
	somPrintf("#define __AIX__\n");
#endif
#ifdef __DEC__
	somPrintf("#define __DEC__\n");
#endif
#ifdef __GNUC__
	somPrintf("#define __GNUC__ %d\n",(int)__GNUC__);
#endif
#ifdef __IBMC__
	somPrintf("#define __IBMC__\n");
#endif
#ifdef _DEBUG
	somPrintf("#define _DEBUG\n");
#endif
#ifdef _REENTRANT
	somPrintf("#define _REENTRANT\n");
#endif
/*#ifdef unix
	somPrintf("unix==%d\n",(int)unix);
#endif*/
#ifdef BSD
	somPrintf("#define BSD %d\n",(int)BSD);
#endif
#ifdef power
	somPrintf("#define power %d\n",(int)power);
#endif
#ifdef __power
	somPrintf("#define __power %d\n",(int)__power);
#endif
#ifdef __mips__
	somPrintf("#define __mips__ %d\n",(int)__mips__);
#endif
#ifdef __VA_REGBYTES
	somPrintf("#define __VA_REGBYTES %d\n",(int)__VA_REGBYTES);
#endif

	somPrintf("sizeof(TCKind)=%ld\n",(long)sizeof(TCKind));
	somPrintf("sizeof(completion_status)=%ld\n",(long)sizeof(completion_status));

	if (sizeof(TCKind)!=sizeof(completion_status))
	{
		somPrintf("TCKind!=completion_status,%ld,%ld\n",
				sizeof(TCKind),sizeof(completion_status));

		return 1;
	}

	SOMClassMgr_somDumpSelf(clsMgr,0);

	test_callstyle(clsMgr);

	test_lookup(clsMgr); 

	test_types();

	SOM_InitEnvironment(&ev);
		
	{
		long i;
		char *p;
		i=1;
		p=(char *)(void *)&i;
		if (*p) 
		{
			somPrintf("little-endian\n");
		}
		else
		{
			somPrintf("big-endian\n");
		}
	}


#ifdef USE_PTHREADS
	test_threads(&ev);
#endif

	if (argc > 0)
	{
		somPrintf("%s tests completed\n",argv[0]);
	}
	else
	{
		somPrintf("tests completed\n");
	}
	
	SOM_UninitEnvironment(&ev);

	return 0;
}

int main(int argc,char **argv)
{
	int i=-1;
	SOMClassMgr SOMSTAR mgr=somEnvironmentNew();

	if (mgr)
	{
		i=main_somtest0(mgr,argc,argv);

		somEnvironmentEnd();
	}

	return i;
}


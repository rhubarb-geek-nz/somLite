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

#include <rhbsomex.h>
#include <stdio.h>

#ifdef SOMDLLEXPORT
	#define SOM_IMPORTEXPORT_somir SOMDLLEXPORT
#else
	#define SOM_IMPORTEXPORT_somir 
#endif

#include <somstubs.h>
#include <somir.h>
#include <rhbsomex.h>

char * SOMLINK irGetFileNames(void) { return NULL; }
char * SOMLINK irGetLastFileName(void) { return NULL; }

SOMInitModule_begin(somir)

    char *envn="DLLPATHENV";
    char *env=getenv(envn);
    char *p;

    if (!env) 
	{
		env="LD_LIBRARY_PATH";
	}

    p=getenv(env);

    fprintf(stderr,"SOMSTUBS::%s,%d\n",__FILE__,__LINE__);

    if (p) 
	{
		fprintf(stderr,"%s=%s\n",env,p);
	}

SOMInitModule_end

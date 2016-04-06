/*=======================================================
	Code written by Jacob Hughes

	jacob.solomon.hughes@gmail.com
	https://github.com/JacobHughes/
=======================================================*/

#pragma once

#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif //_CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <memory>

using namespace std;

/*==================================================
	DEBUG TIME!
==================================================*/
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

/*==================================================
	Function  Prototypes 
==================================================*/

//Initial function to set up the debug environment
int setUpDebugEnvironment();

//Function to set a breakpoint on allocation of a specific memory location
int debugMemoryLocation(int memoryLocation);
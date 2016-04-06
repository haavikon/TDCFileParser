/*=======================================================
	Code written by Jacob Hughes

	jacob.solomon.hughes@gmail.com
	https://github.com/JacobHughes/
=======================================================*/

#include "CppDebug.h"

int setUpDebugEnvironment()
{
	/*==================================================
		Function to set up the debug environment. This 
		function should force logging of memory leaks
		when _DEBUG is defined.

		Returns: 
		0 => total failure,
		1 => total success,
		2 => Memory leaks success, BUT flags not set
	==================================================*/

	enum results
	{
		fail,
		success,
		partial
	};

	try
	{
		//Log memory leaks
		_CrtDumpMemoryLeaks();
	} 
	catch (exception e)
	{
		//Catch any exception and see what it is
		std::cerr << "Error starting _CrtDumpMemoryLeaks(). WHAT: " << e.what() << endl;

		//Return failure, memory leaks not logged
		return static_cast<int>(fail);
	}
	
	try
	{
		//Set Debug Flags so that we ALWAYS dump memory leaks
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}
	catch (exception e)
	{
		//Catch any exception and see what it is
		std::cerr << "Error setting debug flags _CrtSetDbgFlag(). WHAT: " << e.what() << endl;

		//Return partial success, memory leaks logged but flags not set
		return static_cast<int>(partial);
	}
	

	//Return total success
	return static_cast<int>(success);
}

int debugMemoryLocation(int memoryLocation)
{
	/*==================================================
		Wrapper function to set a break point on alloc-
		ation of a specific memory location.

		Return:
		0 => total failure
		1 => total success
		==================================================*/

	enum results
	{
		fail,
		success
	};

	try
	{
		//Set a break point on the memory location specified
		_CrtSetBreakAlloc(memoryLocation);
	}
	catch (exception e)
	{

		//Catch any exception and see what it is
	std:cerr << "Error setting break point _CrtSetBreakAlloc(). WHAT: " << e.what() << endl;

		//Return partial success, memory leaks logged but flags not set
		return static_cast<int>(fail);
	}

	//Return total success
	return static_cast<int>(success);

}
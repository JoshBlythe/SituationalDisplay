#ifndef _ENVIROMENT_H
#define _ENVIROMENT_H

#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>
#include <filesystem>

/**
* Check if Windows is OS, if it is include library.
*/
#ifdef _WIN32
    #include <Windows.h>
#endif // _WIN32


/**
* Enviroment Class includes.
*/
#include "Exception.h"

/**
* Contructor of Enviroment.
*/
class Enviroment
{
public:
    /**
    * This Class is used to get the current enviroment (the local path to load resources from).
    * It also initalises Delta time to be then called by other classes/function in the engine.
    */
    Enviroment(int argc, char** argv);
    ~Enviroment();

    /**
    * This function returns the file location.
    @return A string of the full local path to the resource folder.
    */
    std::string fileLocations();

private:

    std::string m_fullpath; /*!< Variable used to store the full path. */
    std::string m_baseName; /*!< Variable used to store the base path. */
    std::string m_dirName; /*!< Variable used to store the dir path. */

};
#endif

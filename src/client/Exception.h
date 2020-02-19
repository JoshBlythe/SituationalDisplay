#ifndef _Exception_
#define _Exception_

#include <string>

/**
* Initalisation of the class.
*/
class Exception
{
public:
    /**
    * This function is used to if a error occurs, to output a Exception inside of crashing the Engine,
    * this gives a level of error handling to the engine, by preventing it from just crashing and giving a more tailored message.
    */
    Exception(const std::string &exp);
    virtual ~Exception() throw();

    /**
    * Used to throw the execption.
    */
    virtual const char* Error() const throw();

    /**
    * Function used to return for OpenGL Error.
    */
    void pollForError();

private:

    std::string m_exp; /*!< Variable used to store exeption. */

};

#endif

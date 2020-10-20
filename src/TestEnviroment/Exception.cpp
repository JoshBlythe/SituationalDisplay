#include "Exception.h"

#include <GL/glew.h>

#include <iostream>

Exception::Exception(const std::string & exp)
{
    this->m_exp = exp;
}

Exception::~Exception() throw() {}

const char * Exception::Error() const throw()
{
    return m_exp.c_str();
}

void Exception::pollForError()
{
    GLenum err = glGetError();

    if (err == GL_NO_ERROR)
    {
        //break;
        return;
    }

    throw Exception("OpenGL emitted an error");
}

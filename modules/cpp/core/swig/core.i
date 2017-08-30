%module core

%{
    #include "nyra/core/Archive.h"
%}

%include "typemaps.i"
%include "exception.i"

%exception
{
    try
    {
        $action
    }
    catch (const std::exception& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

%include "nyra/core/Archive.h"
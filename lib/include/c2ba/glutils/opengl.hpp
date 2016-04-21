#pragma once

#ifndef C2BA_GLUTILS_GL3_HEADER_PATH

#define C2BA_GLUTILS_GL3_HEADER_PATH <GL/glew.h>

#include C2BA_GLUTILS_GL3_HEADER_PATH

inline bool initOpenGL() {
    glewExperimental = GL_TRUE;
    auto glewResult = glewInit();
    if (glewResult == GLEW_OK) {
        return true;
    }
    // #todo Must log glewGetErrorString(glewResult);
    return false;
}

#else

#include C2BA_GLUTILS_GL3_HEADER_PATH

#endif
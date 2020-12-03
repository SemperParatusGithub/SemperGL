#pragma once

namespace SemperGL
{

    enum WindowFlags
    {
        WindowFlags_None            = 0,            // None
        WindowFlags_NoTitleBar      = 1 << 0,       // Disable title-bar
        WindowFlags_NoResize        = 1 << 1,       // Disable user resizing window
        WindowFlags_NoMove          = 1 << 2,       // Disable user moving window
        WindowFlags_Maximized       = 1 << 3,       // Start window maximized
        WindowFlags_CursorCentered  = 1 << 4        //Start window with cursor centered
	};

}

inline bool operator  |  (SemperGL::WindowFlags a, SemperGL::WindowFlags b)     { return (bool)((int)a | (int)b);       }
inline bool operator  &  (SemperGL::WindowFlags a, SemperGL::WindowFlags b)     { return (bool)((int)a & (int)b);       }
inline bool &operator |= (SemperGL::WindowFlags &a, SemperGL::WindowFlags b)    { return (bool &)((int &)a |= (int)b);  }
inline bool &operator &= (SemperGL::WindowFlags &a, SemperGL::WindowFlags b)    { return (bool &)((int &)a &= (int)b);  }
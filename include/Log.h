//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        Log.h                                     //
//            █ █        █ █        CoreGame                                  //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __CoreGame_include_CoreGame_Log_h__
#define __CoreGame_include_CoreGame_Log_h__

//std
#include <cstdarg>
#include <string>
#include <fstream>
//CoreGame
#include "CoreGame_Utils.h"
#include "CoreGame_Macros.h"

//COWTODO: Add documentation.
//COWTODO: Discover a way to add* and remove* methods accepts
//         any number of args like addOutput(stdout, stderr, file);

NS_COREGAME_BEGIN

class Log
{
    // Enums //
public:
    enum class Type
    {
        Fatal   = 1 << 0,
        Error   = 1 << 1,
        Warning = 1 << 2,
        Verbose = 1 << 3,
        Debug1  = 1 << 4,
        Debug2  = 1 << 5,
        Debug3  = 1 << 5,
        Debug4  = 1 << 6,
    };

    enum class Output
    {
        stdout = 1 << 0,
        stderr = 1 << 1,
        file   = 1 << 2,
    };

    // Static Methods //
public:
    static Log& GetDefaultLogger();

    // CTOR / DTOR //
public:
    Log();
    ~Log();


    // Public Methods //
public:
    void addLogType(Type type);
    void removeLogType(Type type);
    bool isLogTypeActive(Type type) const;

    void addLogOutput(Output output);
    void removeLogOutput(Output output);
    bool isLogOutputActive(Output output) const;

    void setLogFileFilename(const std::string &filename, bool append);

    void log(Type type, const char *fmt, ...);


    // Private Methods //
private:
    void closeFileStream();
    void logAt(Type type, std::ostream &os, const char *msg);

    // iVars //
private:
    int m_type;
    int m_output;

    std::string  m_filename;
    std::fstream m_filestream;
};

NS_COREGAME_END

#ifdef NDEBUG
    #define COREGAME_DLOG(_type_, _fmt_, ...) do {} while(0)
#else
    #define COREGAME_DLOG(_type_, _fmt_, ...) {             \
        CoreGame::Log::GetDefaultLogger().log(_type_,         \
                                    _fmt_,          \
                                    ##__VA_ARGS__); \
    }
#endif //NDEBUG

#endif // defined(__CoreGame_include_CoreGame_Log_h__) //
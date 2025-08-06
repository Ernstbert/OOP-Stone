cmake_minimum_required(VERSION 3.15)
project(assignment_6216)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(rapidjson)
include_directories(rapidjson/error)
include_directories(rapidjson/internal)
include_directories(rapidjson/msinttypes)

add_executable(assignment_6216
    rapidjson/error/en.h
    rapidjson/error/error.h
    rapidjson/internal/biginteger.h
    rapidjson/internal/clzll.h
    rapidjson/internal/diyfp.h
    rapidjson/internal/dtoa.h
    rapidjson/internal/ieee754.h
    rapidjson/internal/itoa.h
    rapidjson/internal/meta.h
    rapidjson/internal/pow10.h
    rapidjson/internal/regex.h
    rapidjson/internal/stack.h
    rapidjson/internal/strfunc.h
    rapidjson/internal/strtod.h
    rapidjson/internal/swap.h
    rapidjson/msinttypes/inttypes.h
    rapidjson/msinttypes/stdint.h
    rapidjson/allocators.h
    rapidjson/cursorstreamwrapper.h
    rapidjson/document.h
    rapidjson/encodedstream.h
    rapidjson/encodings.h
    rapidjson/filereadstream.h
    rapidjson/filewritestream.h
    rapidjson/fwd.h
    rapidjson/istreamwrapper.h
    rapidjson/memorybuffer.h
    rapidjson/memorystream.h
    rapidjson/ostreamwrapper.h
    rapidjson/pointer.h
    rapidjson/prettywriter.h
    rapidjson/rapidjson.h
    rapidjson/reader.h
    rapidjson/schema.h
    rapidjson/stream.h
    rapidjson/stringbuffer.h
    rapidjson/writer.h
    Card.cpp
    Card.hpp
    CreatureCard.cpp
    CreatureCard.hpp
    Game.cpp
    Game.hpp
    Interface.cpp
    Interface.hpp
    JsonParser.cpp
    JsonParser.hpp
    main.cpp
    Player.cpp
    Player.hpp
    Random.cpp
    Random.hpp
    SpellCard.cpp
    SpellCard.hpp Command.cpp Command.hpp Quit.cpp Quit.hpp Finish.cpp Finish.hpp SetCard.cpp SetCard.hpp State.cpp State.hpp Help.cpp Help.hpp Attack.cpp Attack.hpp Cast.cpp Cast.hpp Sacrifice.cpp Sacrifice.hpp)

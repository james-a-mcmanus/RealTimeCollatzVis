include_directories(../include)
set(SOURCE_FILES messageParser.cpp SequenceHolder.cpp DataUpdater.cpp serverReceiverParse.cpp)
add_executable(serverReceiverParse ${SOURCE_FILES})

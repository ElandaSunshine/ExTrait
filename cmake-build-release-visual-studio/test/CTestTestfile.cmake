# CMake generated Testfile for 
# Source directory: D:/Development/Coding/cpp/ExTrait/test
# Build directory: D:/Development/Coding/cpp/ExTrait/cmake-build-release-visual-studio/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[TestTYPELIST]=] "D:/Development/Coding/cpp/ExTrait/cmake-build-release-visual-studio/test/TestTYPELIST.exe")
set_tests_properties([=[TestTYPELIST]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;54;add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;62;extrait_add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;0;")
add_test([=[TestCOMMON]=] "D:/Development/Coding/cpp/ExTrait/cmake-build-release-visual-studio/test/TestCOMMON.exe")
set_tests_properties([=[TestCOMMON]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;54;add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;63;extrait_add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;0;")
add_test([=[TestREFLECTION]=] "D:/Development/Coding/cpp/ExTrait/cmake-build-release-visual-studio/test/TestREFLECTION.exe")
set_tests_properties([=[TestREFLECTION]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;54;add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;64;extrait_add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;0;")
add_test([=[TestSTRINGABLE]=] "D:/Development/Coding/cpp/ExTrait/cmake-build-release-visual-studio/test/TestSTRINGABLE.exe")
set_tests_properties([=[TestSTRINGABLE]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;54;add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;65;extrait_add_test;D:/Development/Coding/cpp/ExTrait/test/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")

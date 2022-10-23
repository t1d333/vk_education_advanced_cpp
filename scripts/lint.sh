cpplint --extensions=cpp,hpp project/include/* project/src/* 
cppcheck project --enable=all --inconclusive --error-exitcode=1 -I project/include --suppress=missingIncludeSystem 



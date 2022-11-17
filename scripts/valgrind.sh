cd build/project/tests/ && valgrind --tool=memcheck --leak-check=summary --leak-check=full --track-origins=yes --error-exitcode=1 ./tests ../../../project/tests/data 

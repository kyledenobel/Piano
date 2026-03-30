

.PHONY: test
test: compiled_test
	./compiled_test
	python test.py

compiled_test:
	g++ test.cpp key.cpp keyboard.cpp -o compiled_test


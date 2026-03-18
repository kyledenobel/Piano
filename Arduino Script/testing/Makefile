

.PHONY: test
test: compiled_test
	./compiled_test
	python test.py

compiled_test:
	g++ test.cpp ../piano/key.cpp -o compiled_test


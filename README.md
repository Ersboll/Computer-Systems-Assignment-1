# Computer-Systems-Assignment-1

## Runing the test
1. In `./src/main.h` change the following flags to
    - `DEBUGGING 0`
    - `TESTING 1`
    - `PRODUCTION 0`
2. Change `THRESHOLDING_METHOD` to the algorithm (`BINARY_THRESHOLD` or `OTSU`) you want to test
3. Run `make`
4. Run the test `python3 test_runner.py`

import os
import sys
import json

DIR = "samples"
SAMPLE_SIZE = int(sys.argv[1]) if(len(sys.argv) == 2) else int(input("Enter sample size: "))

def run():
    timedict = {
        "easy": [],
        "medium": [],
        "hard": [],
        "impossible": []
    }

    dirs = os.listdir(DIR)
    times = 0

    for dir in dirs:
        files = os.listdir(f"{DIR}/{dir}")

        for f in files:
            file_path = f"./{DIR}/{dir}/{f}"
            
            sample = {
                "times": [],
                "average": 0
            }
            sum = 0

            for n in range(SAMPLE_SIZE):
                time = os.popen("./build/final_program example.bmp ./out.bmp").read()
                
                sum += float(time)

                sample["times"].append(time)
                times += 1
                print(f"time: {times} of {35*SAMPLE_SIZE}", end = "\r")

            sample["average"] = sum / SAMPLE_SIZE

            timedict[dir].append(sample)
            
    print(json.dumps(timedict, sort_keys=True, indent=4))


def analyse(timedict):
    print("")
    print(timedict["easy"])

    sum = 0
    for i in timedict["easy"]:
        for j in timedict["easy"][i]:
            sum = sum + timedict["easy"][i][j]

    print(sum)




if __name__ == '__main__':
    run()
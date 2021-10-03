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
                "image_name": f,
                "times": [],
                "average_time": 0,
                "detection_count": [],
                "average_detection_count": 0,
            }

            time_sum = 0
            detection_count_sum = 0

            for n in range(SAMPLE_SIZE):
                time, detection_count = os.popen(f"./build/final_program {file_path} ./out.bmp").read().split()
                
                time_sum += float(time)
                detection_count_sum += float(detection_count)

                sample["times"].append(time)
                sample["detection_count"].append(detection_count)

                times += 1

                print(f"time: {times} of {35*SAMPLE_SIZE} with detection count: {detection_count}", end = "\r")


            sample["average_time"] = time_sum / SAMPLE_SIZE
            sample["average_detection_count"] = detection_count_sum / SAMPLE_SIZE

            timedict[dir].append(sample)
            
    print(json.dumps(timedict, sort_keys=True, indent=4))

    f = open("test.json", "w")
    f.write(json.dumps(timedict, sort_keys=True, indent=4))
    f.close()


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
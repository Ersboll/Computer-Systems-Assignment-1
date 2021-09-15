import os

DIR = "samples"
SAMPLE_SIZE = 1

def run():
    timedict = {
        "easy": [],
        "medium": [],
        "hard": [],
        "impossible": []
    }

    dirs = os.listdir(DIR)

    for dir in dirs:
        files = os.listdir(f"{DIR}/{dir}")

        for f in files:
            file_path = f"./{DIR}/{dir}/{f}"
            
            sample = []

            for n in range(SAMPLE_SIZE):
                time = os.popen("./build/final_program example.bmp ./out.bmp").read()
                
                sample.append(time)

            timedict[dir].append(sample)
            
    print(timedict)






if __name__ == '__main__':
    run()
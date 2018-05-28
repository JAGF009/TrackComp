import os
import csv
from collections import defaultdict
import pprint
import copy
import pickle

class DBHolder:
    def __init__(self, *args):
        adir, _, files = args[0]
        self.name = adir
        splitted = adir.strip().split("-")
        self.id = int(splitted[-1]) if splitted[-1].isdigit() else splitted[-1]
        self.db = splitted[-3] + "-" + splitted[-2]

        self.bSTRUCK = "STRUCK.csv" in files
        self.STRUCK = os.path.join(self.name, "STRUCK.csv") if self.bSTRUCK else None
        self.dSTRUCK = defaultdict(dict) if self.bSTRUCK else None

        self.bRe3 = "Re3.csv" in files
        self.Re3 = os.path.join(self.name, "Re3.csv") if self.bRe3 else None
        self.dRe3 = defaultdict(dict) if self.bRe3 else None

        self.bMIL = "MIL.csv" in files
        self.MIL = os.path.join(self.name, "MIL.csv") if self.bMIL else None
        self.dMIL = defaultdict(dict) if self.bMIL else None

        self.bBoosting = "Boosting.csv" in files
        self.Boosting = os.path.join(self.name, "Boosting.csv") if self.bBoosting else None
        self.dBoosting = defaultdict(dict) if self.bBoosting else None

        self.bMedianFlow = "MedianFlow.csv" in files
        self.MedianFlow = os.path.join(self.name, "MedianFlow.csv") if self.bMedianFlow else None
        self.dMedianFlow = defaultdict(dict) if self.bMedianFlow else None

        self.bKCF = "KCF.csv" in files
        self.KCF = os.path.join(self.name, "KCF.csv") if self.bKCF else None
        self.dKCF = defaultdict(dict) if self.bKCF else None

        self.bTLD = "KCF.csv" in files
        self.TLD = os.path.join(self.name, "TLD.csv") if self.bTLD else None
        self.dTLD = defaultdict(dict) if self.bTLD else None

    def __repr__(self):
        return "Directory for results of id: " + str(self.id) + " of DB: " + self.db

    def read(self):
        for tName in ["STRUCK", "Re3", "MIL", "Boosting", "MedianFlow", "KCF", "TLD"]:
            if getattr(self, "b" + tName):
                with open(getattr(self, tName)) as f:
                    try:
                        reader = csv.reader(f)
                        next(reader) #HEADERS
                        the_dict = getattr(self, "d" + tName)
                        row = next(reader)
                    
                        while row[0] != "METRIC":
                            the_dict[int(row[0])][self.id] = (row[1:5], row[5:])
                            row = next(reader)
                    except StopIteration:
                        pass
            #print(tName, "done")
        print(self.db, "done")

        return self

    def update_major_being(self, major_dict):
        for tName in ["STRUCK", "Re3", "MIL", "Boosting", "MedianFlow", "KCF", "TLD"]:
            if getattr(self, "b" + tName):
                if tName not in major_dict:
                    major_dict[tName] = defaultdict(dict)
                update_dir = major_dict[tName]
                if self.db not in update_dir:
                     update_dir[self.db] = defaultdict(dict)
                update_dir[self.db].update(getattr(self, "d"+tName))

class Agregation:
    def __init__(self):
        self.dict = defaultdict(dict)
    def update(self, db):
        db.update_major_being(self.dict)



def _sorting_key(d):
    return (d.db, d.id)
    


dirs = os.walk("build/results")
next(dirs) # Skip "." directory
DB = list(map(DBHolder, dirs))
DB.sort(key=_sorting_key)
agr = Agregation()
for db in DB:
    agr.update(db.read())
pprint.pprint(agr.dict.keys())
#with open("saved_bbox.bin", "wb") as f:
#    pickle.dump(agr.dict, f)
for frame in agr.dict["STRUCK"]["ceil-6"]:
    print(frame, agr.dict["STRUCK"]["ceil-6"][frame].keys())
input("FINISHED")

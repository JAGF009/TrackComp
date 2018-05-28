class Formats:
    MOT_NAME = "MOT17-{}"
    MOT_FILE_KEYS = MOT_NAME + ".txt"
    FRCNN = "./tcomp -a --id {} --DB MOT /home/dino/Downloads/MOT17/train/{}-FRCNN/\n"
    DPM = "./tcomp -a --id {} --DB MOT /home/dino/Downloads/MOT17/train/{}-DPM/\n"
    SDP = "./tcomp -a --id {} --DB MOT /home/dino/Downloads/MOT17/train/{}-SDP/\n"

with open("build/one_script_to_run_them_all.sh", "w") as f:
    f.write(r"""make -j12
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-0/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-2/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-3/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-5/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-6/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-9/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-10/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-11/
./tcomp -a --id Jose /home/dino/TrackingResearch/DB/final/ceil-12/
""")

    for s in ["02", "04", "05", "09", "10", "11", "13"]:
        file_keys = Formats.MOT_FILE_KEYS.format(s)
        with open(file_keys, "r") as keys:
            for key in keys:
                if len(key.strip()) > 0:
                    f.write(Formats.FRCNN.format(key.strip(), Formats.MOT_NAME.format(s)))
                    f.write(Formats.DPM.format(key.strip(), Formats.MOT_NAME.format(s)))
                    f.write(Formats.SDP.format(key.strip(), Formats.MOT_NAME.format(s)))

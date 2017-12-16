import os
current_folder = os.path.dirname(os.path.realpath(__file__))
def create_directories():
    tree = ["bin", "build", "doc", "include", "lib", "src", "test"]
    for item in tree:
        path = current_folder + "/" + item
        print("Creating: %s" % path)
        os.mkdir(path)

def main():
    create_directories()

main()

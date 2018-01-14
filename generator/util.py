import os


def check_dir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)


def filename_in_directory(directory, filename):
    return directory + "/" + filename


def open_file_in_directory(directory, filename):
    check_dir(directory)
    new_filename = filename_in_directory(directory, filename)
    file = open(new_filename, 'w')
    return file

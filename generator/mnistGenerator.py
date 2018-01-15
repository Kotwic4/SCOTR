import random

from sklearn.datasets import fetch_mldata

from util import open_file_in_directory

MNIST_DIR = './tmp/mnist'
MNIST_TRAIN_DIR = './mnist/train'
MNIST_TEST_DIR = './mnist/test'
MNIST_SAMPLE_DIR = './mnist/sample'
TEST_CASES = 60000


def mnist_img_to_file(mnist_img, file):
    for x in range(28):
        for y in range(28):
            file.write(str(mnist_img[x * 28 + y]) + " ")
        file.write('\n')


def generate_samples(data, labels, directory='.', filename='results.txt', sampleNumber=100):
    result = open_file_in_directory(directory, filename)
    for i in range(sampleNumber):
        index = random.randrange(data.shape[0])
        label = labels[index]
        img = data[index]
        img_filename = str(index) + ".txt"
        line = img_filename + ' ' + str(label) + '\n'
        result.write(line)
        file = open_file_in_directory(directory, img_filename)
        mnist_img_to_file(img, file)
        file.close()
    result.close()


def generate_test_file(data, labels, directory='.', filename='results.txt'):
    result = open_file_in_directory(directory, filename)
    result.write(str(data.shape[0]) + '\n')
    indexes = [i for i in range(data.shape[0])]
    random.shuffle(indexes)
    for i in indexes:
        label = labels[i]
        img = data[i]
        line = str(label) + '\n'
        result.write(line)
        mnist_img_to_file(img, result)
    result.close()


def generate_test_data(data, labels):
    test_data = data[TEST_CASES:]
    test_labels = labels[TEST_CASES:]
    generate_test_file(test_data, test_labels, MNIST_TEST_DIR)


def generate_train_data(data, labels):
    train_data = data[:TEST_CASES]
    train_labels = labels[:TEST_CASES]
    generate_test_file(train_data, train_labels, MNIST_TRAIN_DIR)


def main():
    mnist = fetch_mldata('MNIST original', data_home=MNIST_DIR)
    labels = mnist.target.astype(int)
    data = mnist.data
    generate_train_data(data, labels)
    generate_test_data(data, labels)
    generate_samples(data, labels, MNIST_SAMPLE_DIR)


if __name__ == "__main__":
    main()

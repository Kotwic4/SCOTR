from captcha.image import ImageCaptcha
from claptcha import Claptcha
import string
import random
WIDTH = 200
HEIGHT = 100
MAX = 10
CASES = 100
RESULT_FILE = "results.txt"
FONT = "./orange.ttf"


def generate_image_claptcha(text, filename):
    c = Claptcha(text, FONT, (WIDTH, HEIGHT))
    c.write(filename)


def generate_image_captcha(text, filename):
    image = ImageCaptcha(WIDTH, HEIGHT, fonts=[FONT])
    image.write(text, filename)


def generate_test(how_match):
    f = open(RESULT_FILE, 'w')
    for x in range(how_match):
        s = ''.join(random.choices(string.ascii_letters + string.digits, k=random.randint(1, MAX)))
        fun = random.choice([generate_image_captcha, generate_image_claptcha])
        filename = str(x)+'.png'
        fun(s, filename)
        f.write(filename + " " + s + '\n')
    f.close()


generate_test(CASES)

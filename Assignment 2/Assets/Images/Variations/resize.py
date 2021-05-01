from PIL import Image

i = 0

def bal(i):
    out = str(i)

    while (len(out) < 4):
        out = "0" +out

    return out

while (i<=70) :
    inIm = bal(i) + ".png"
    image = Image.open(inIm)
    image = image.resize(image.size)
    image.save(inIm)
    i += 1

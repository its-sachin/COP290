from PIL import Image
import cv2



mode = int(input("Resize(0) | Mirror(1) | Merge(2): "))

if (mode == 0 or mode ==1) :

    inIm = input("Enter image name: ")
    # image = cv2.imread(inIm)
    image = Image.open(inIm)    

    if (mode == 0):
        width = int(input("Enter width: "))
        height = int(input("Enter height: "))
        image = image.resize((width, height))

    else:
        image = cv2.flip(image, 1)
        


    outIm = input("Enter output name: ")
    image.save(outIm)
    # cv2.imwrite(outIm, image)


elif (mode ==2):

    imglf = cv2.imread('lmid.bmp')
    imgld = cv2.imread('ldown.bmp')
    imglu = cv2.imread("lup.bmp")

    imgrf = cv2.imread('rmid.bmp')
    imgrd = cv2.imread('rdown.bmp')
    imgru = cv2.imread("rup.bmp")

    iml = cv2.vconcat([imglf, imgld,imglu])
    imr = cv2.vconcat([imgrf, imgrd,imgru])

    imfinal = cv2.hconcat([iml,imr])

    cv2.imshow('final image', imfinal)

    outIm = input("Enter output name: ")
    cv2.imwrite(outIm, imfinal)

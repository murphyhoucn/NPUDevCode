import cv2

img = cv2.imread("./Resources/lambo.PNG")
print(img.shape)
imgResize = cv2.resize(img, (3000, 2000))
imgCrop = img[0:200, 200:500]

cv2.imshow("Image", imgCrop)
cv2.waitKey(0)

import cv2 

first = cv2.imread("first.png")
second = cv2.imread("second.png")

third = abs(second + first)

cv2.imwrite("sum.png",third)
cv2.destroyAllWindows()
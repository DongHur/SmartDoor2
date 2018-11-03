from imutils.video import VideoStream
from imutils.video import FPS
from collections import Counter
import face_recognition
import argparse
import pickle
import imutils
import time
import cv2

import serial

# setup arduino
arduinoSerialData = serial.Serial('/dev/ttyACM0', 9600)

# Argument Parser
ap = argparse.ArgumentParser()
ap.add_argument("-c", "--cascade", required=True, help="path to where the face cascade resides")
ap.add_argument("-e", "--encodings", required=True, help="path to db for facial encodings")
args = vars(ap.parse_args())

print("[INFO] loading encodings + face detector ...")
data = pickle.loads(open(args["encodings"], "rb").read())
detector = cv2.CascadeClassifier(args["cascade"])

# start and warm up camera
print("[INFO] starting video stream ...")
vs = VideoStream(src=0).start()
# vs = VideoStream(usePiCamera=True).start()
time.sleep(2.0)

# Frame Per Second Counter
fps = FPS().start()

name_count = Counter(data["names"])

# Loop over frames from video file
while True:
	frame = vs.read()
	frame = imutils.resize(frame, width=500)

	# Use Gray image for Face Detection. Use RGB for Face Recognition
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

	# detect face
	rects = detector.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30,30), flags=cv2.CASCADE_SCALE_IMAGE)

	# OpenCV returns bounding box coordinates in (x, y, w, h) order
	# but we need them in (top, right, bottom, left) order, so we
	# need to do a bit of reordering
	boxes = [(y, x + w, y + h, x) for (x, y, w, h) in rects]

	# compute facial embeddings
	encodings = face_recognition.face_encodings(rgb, boxes)
	names = []

	# loop over the possible faces in db
	for encoding in encodings:
		# match each face to the known face
		matches = face_recognition.compare_faces(data["encodings"], encoding)
		name = "Unknown"
		# if match was found
		if True in matches:
			matchedIdxs = [i for (i,b) in enumerate(matches) if b]
			counts = {}

			for i in matchedIdxs:
				name = data["names"][i]
				counts[name] = counts.get(name, 0) + 1
			
			# get the largest number of votes and return the largest number
			name = max(counts, key=counts.get)
			perc = 100.0*counts[name]/name_count[name]
			if (perc > 80):
				arduinoSerialData.write(str.encode('Y'))
		names.append(name + ": " + format(int(perc)) + "%" )

	# AS LONG AS 80% IS MET THAN OPEN DOOR!

	# **** don't need any of this part for real application****
	# loop over the recognized faces
	for ((top, right, bottom, left), name) in zip(boxes, names):
		# draw the predicted face name on the image
		cv2.rectangle(frame, (left, top), (right, bottom),
			(0, 255, 0), 2)
		y = top - 15 if top - 15 > 15 else top + 15
		cv2.putText(frame, name, (left, y), cv2.FONT_HERSHEY_SIMPLEX,
			0.75, (0, 255, 0), 2)

	# display the image to our screen
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF

	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break

	# update the FPS counter
	fps.update()

# stop the timer and display FPS information
fps.stop()
print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()

























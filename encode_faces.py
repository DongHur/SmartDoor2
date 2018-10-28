from imutils import paths
import face_recognition
import argparse
import pickle
import cv2
import os

# Create argument parser
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--dataset", required=True, help="path to input directory of faces + images")
ap.add_argument("-e", "--encodings", required=True, help="path to serialized db of facial encodings")
ap.add_argument("-d", "--detection-method", type=str, default="cnn", help="face detection model to use: either 'hog' or 'cnn'")
args = vars(ap.parse_args())

# grab images
print("[INFO] Compiling Images to Latent Space ...")
imagePaths = list(paths.list_images(args["dataset"]))

# initalize and compile known encodings and known names
knownEncodings = []
knownNames = []

# loop over images and compile faces into encoding dataset
N = len(imagePaths)
for (i, imagePath) in enumerate(imagePaths):
	# Grab person name from file name
	print("[INFO] Processing image {}/{}".format(i+1,N))
	name = imagePath.split(os.path.sep)[-2]

	# cv2 abstract image to RGB format that dlib understands
	image = cv2.imread(imagePath)
	rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

	# recognize x, y coordinates for bounding boxes
	boxes = face_recognition.face_locations(rgb, model=args["detection-method"])

	# compute facial embedding for the face
	encodings = face_recognition.face_encodings(rgb, boxes)

	# add recognized faces with corresponding name to list
	for encoding in encodings:
		knownEncodings.append(encoding)
		knownNames.append(name)

# Store knownEncodings and KnownNames in Encoding Dataset
print("[INFO] Storing Enfoding as Pickle ...")
data = {"encodings": knownEncodings, "names": knownNames}
f = open(args["encodings"], "wb")
f.write(pickle.dumps(data))
f.close()








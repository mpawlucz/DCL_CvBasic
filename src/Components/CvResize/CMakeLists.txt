# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

# Find required packages


# Create an executable file from sources:
ADD_LIBRARY(CvResize SHARED ${files})

# Link external libraries
TARGET_LINK_LIBRARIES(CvResize ${OpenCV_LIBS} ${DisCODe_LIBRARIES} )

INSTALL_COMPONENT(CvResize)

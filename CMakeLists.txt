CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_REQUIRED_STANDARD ON)
SET(CMAKE_DEBUG_POSTFIX "-d")

SET(PROJECT_NAME "kenville")
PROJECT(${PROJECT_NAME} LANGUAGES CXX)

SET(HEADERS ./AppEngine.hpp ./AppState.hpp ./MainMenuState.hpp ./GameCreationState.hpp ./GamePlayState.hpp ./PlayerCharacter.hpp ./EntityManager.hpp ./BaseEntity.hpp ./Object.hpp ./Door.hpp ./HouseExteriorEntity.hpp)
SET(SOURCES ./AppEngine.cpp ./main.cpp MainMenuState.cpp ./GameCreationState.cpp ./GamePlayState.cpp ./PlayerCharacter.cpp ./EntityManager.cpp ./BaseEntity.cpp ./Object.cpp ./Door.cpp ./HouseExteriorEntity.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${HEADERS} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ../SFML/include)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-window sfml-system -L"../SFML/lib")

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ../SFUI/include)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} SFUI -L"../SFUI/lib")

TARGET_LINK_LIBRARIES(${PROJECT_NAME} stdc++fs)

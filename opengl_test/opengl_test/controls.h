#pragma once
#include "includes.h"



//naplni view a project matici
int computeMatrices();

glm::mat4 getProject();
glm::mat4 getView();
glm::vec3 getDir();
glm::vec3 getUp();
glm::mat4 getMyPosition();
void setMyPosition(glm::vec3 pos);
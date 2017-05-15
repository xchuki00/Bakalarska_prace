#pragma once
#include "includes.h"



//naplni view a project matici
int computeMatrices();

glm::mat4 getProject();
glm::mat4 getOrthoProject(glm::vec3 dir);
glm::mat4 getView();
glm::mat4 getOrthoView(glm::vec3 dir);
glm::vec3 getDir();
glm::vec3 getUp();
glm::mat4 getMyPosition();
glm::vec3 getVectorOfPosition();
glm::vec3 getChange();
glm::vec3 getRight();
float getVAngle();
float getHAngle();
void setMyPosition(glm::vec3 pos);